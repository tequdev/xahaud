# Hook API cost benchmark (HookFeeV2) — design (v2, post-review)

## 1. Goal

HookFeeV2 prices a hook by a static worst-case *cost* computed by the guard
checker (`include/xrpl/hook/Guard.h`, `compute_wce`):

    cost = (#wasm instructions on the worst-case path) * 1
         + sum over API `call`s on that path of HOOK_API_COST(api)

and charges `cost * HookGasPrice` (`hook::hookCostToFee`). The unit is "one
WebAssembly instruction". This document defines how to derive a defensible
`HOOK_API_COST(api)` for every API in `include/xrpl/hook/hook_api.macro`:

    HOOK_API_COST(api) := ceil( t_api / t_instr ), rounded up to 2 significant digits, floor 10

* `t_instr` — mean wall time of one WebAssembly instruction of *typical
  compiled hook code* executed by the production interpreter (WasmEdge 0.11.2,
  interpreter mode, instruction counting on — exactly
  `HookExecutor::WasmEdgeVM`). Not the cheapest opcode: the fee model charges
  every opcode 1, so the mean of the same mix is the only self-consistent unit.
* `t_api` — wall time attributable to one call of the API: host function body
  + host-call boundary (argument marshalling in and out of WasmEdge) + the
  call's share of synchronous side effects performed later in the same
  transaction apply (hook-state flush in `finalizeHookState`, emitted-txn
  object creation in `finalizeHookResult`). Excludes the wasm `call`
  instruction and argument pushes (already counted as instructions).

Only the ratio is used. Absolute machine speed cancels; the interpreter-vs-
native ratio does not (see §5), which is why a Linux x86-64 run is the
canonical table and any single-machine result is a draft.

Facts established during review that shape everything below:

* The guard checker rejects a hook whose static worst-case instruction count
  reaches 65535 (`Guard.h:835`). The count is `loop bound x body`, so a loop
  calling one API (~10-14 static instr/iteration) can run at most ~5000
  iterations; a 64x-unrolled body only ~100. Loops cannot be made long.
* Loop-head guards are consumed by the checker without being counted
  (`Guard.h:398-440`), so `HOOK_API_COST(_g, ...)` is currently dead; we still
  measure `_g` and report it, stating this.
* `HOOK_API_COST` is consumed in *static* instruction units, `t_instr` is
  measured per *runtime* instruction. Static >= runtime, so the table is
  conservative in the safe direction; the static/runtime ratio is reported per
  benchmark hook (read `sfHookCost` off the HookDefinition).
* Every API call constructs a journal in `HOOK_SETUP`
  (`include/xrpl/hook/Macro.h`), a per-call constant that dominates cheap APIs.
  It is real validator work and stays in `t_api`.
* Several APIs are capped per execution: `state_set`/`state_foreign_set` 256
  calls (same-key rewrites count too), `emit` 255, `etxn_nonce`/`ledger_nonce`/
  `etxn_details` 255, `hook_param_set` 16, slots 255; `etxn_reserve` and
  `hook_again` are one-shot; `accept`/`rollback` terminate.

## 2. Measurement

### 2.1 Instrumentation (primary measurement, build flag)

CMake option `hook_cost_bench` (default OFF) defines `HOOK_COST_BENCH`. It
never ships in a validator binary. Under the flag:

* `DEFINE_HOOK_FUNCTION` (Macro.h) wraps the call to `hook_api::F` in a
  `steady_clock` scope and accumulates `{calls, ns}` into a per-API counter.
* `HookExecutor::executeWasm` times `WasmEdge_VMRunWasmFromBuffer` and records
  `{execNs, instructionCount}` for the last execution.
* `hook::finalizeHookState` records `{ns, modifiedEntries}`;
  `hook::finalizeHookResult` records `{ns, emittedTxns}`.
* `include/xrpl/hook/Bench.h` (header-only) holds the counters and exposes
  `snapshot()` / `reset()` to the test.

The clock overhead `t_clk` (empty timed scope, 1e6 samples) is measured at
start-up and subtracted from every per-call reading.

### 2.2 Baseline: `t_instr` and the host-call boundary `t_call`

Baseline hooks: the loop scaffold (`GUARD`, N read from a 4-byte big-endian
HookParameter "N", one `accept`) with a pure-wasm body unrolled 1x, 4x, 16x,
64x (byte-wise buffer walk compiled at -O2: local.get/set, i32 load/store,
add/xor/and, compare, br_if). Each hook runs at two N values that fit its own
static-count budget (N2 <= 65534 / static-instr-per-iteration, N1 = N2/10).

Per iteration, with `Tw` the timed wasm execution and `Tg` the `_g` wrapper
time (both from 2.1), `I` the runtime instruction count from metadata:

    dTw = (Tw(N2) - Tg(N2) - Tw(N1) + Tg(N1)) / (N2 - N1)
    dI  = (I(N2) - I(N1)) / (N2 - N1)
    dTw = t_instr * dI + t_call            (least squares over the 4 hooks)

`t_call` is the part of a host call that lives outside the wrapper timer
(WasmEdge's host-call dispatch); it is added to every API. Gates: R^2 > 0.99,
`dI` must equal the per-iteration instruction count the guard checker
reports for that loop body (catches compiler unrolling), and `t_instr` from
two extra bodies (pure i64 arithmetic; memory-copy heavy) is reported as a
sensitivity range. If the buffer-walk and i64 baselines differ by more than
2x, the geometric mean is used and stated.

### 2.3 Per-API

    t_api = (ns_wrapper / calls - t_clk) + t_call  [+ side-effect share]

Each API hook calls the API K times per execution (K = min(cap, ~200) for
capped APIs, otherwise a loop of N <= ~4000 iterations), and is executed R = 10
times; the statistic is the minimum over executions of the per-call mean.
Side-effect shares: `state_set`/`state_foreign_set` add
`finalizeHookState.ns / modifiedEntries`; `emit` adds
`finalizeHookResult.ns / emittedTxns`.

Scenario rules from the review:

| API | scenario |
|---|---|
| `accept`, `rollback` | timed directly by the wrapper (one call per execution, R = 50) |
| `etxn_reserve`, `hook_again` | first call timed directly; loop not needed |
| `emit` | `etxn_reserve(K)`, K = 200 emits, each with its own `etxn_nonce`/`etxn_details` (timed separately by their own counters) |
| `state`, `state_foreign` | reads are cached per key in `stateMap`: loop over 200 *distinct* pre-created keys per execution |
| `state_set` | 200 distinct keys per execution (same-key rewrites also count toward the 256 cap) |
| `state_foreign_set` | needs a HookGrant; grant scan happens on the first call then is cached: report K = 1 (first call) and K = 200 (mean); table uses the first-call value |
| `slot_set` | 34-byte keylet form only (the 32-byte txid form hits the master transaction cache, not reproducible) |
| `slot_*`, `otxn_slot`, `meta_slot`, `xpop_slot` | always pass explicit slot numbers (slot 0 allocates and exhausts 255) |
| `slot_clear` | paired with `slot_set` in the loop; each has its own counter |
| `hook_skip` | alternate flags 1/0 so the scan path runs every iteration |
| `hook_param_set` | K = 16 (cap) |
| `meta_slot` | strong pass calls `hook_again()`, weak (AAW) pass loops `meta_slot` |
| `xpop_slot` | on a `ttIMPORT` transaction with a valid XPOP (as in `SetHook_test` `test_xpop_slot`) |
| `util_verify` | one *passing* verification each for ed25519 and secp256k1; table = max |
| `float_sto` | XRP, IOU and short-form paths; table = max |
| `util_keylet`, `slot_type`, `otxn_id` | all modes; table = max |
| `trace*` | early-return at production journal level; measured as such and stated |
| `ledger_keylet` | stated as a lower bound: JTX ledger is near-empty |
| `etxn_fee_base` | on an emitted Payment whose destination has no hooks (stated) |

### 2.4 Size dependence

Sizes measured and the value used for the table:

| API family | sizes | table value |
|---|---|---|
| `util_sha512h` | 32 B, 1 KiB, 16 KiB | 1 KiB (see rule) |
| `sto_validate/subfield/subarray/emplace/erase` | ~100 B, ~500 B, 4 KiB | 500 B (see rule) |
| `state/state_foreign/state_set/state_foreign_set` | 32 B, 256 B, 4096 B (ExtendedHookState) | 256 B |
| `otxn_field`, `otxn_slot`, `slot` | 20 B field / 1 KiB Blob / 16 KiB Blob (Invoke) | 1 KiB (see rule) |
| `otxn_param`, `hook_param`, `hook_param_set` | 32 B, 256 B | 256 B (hard cap) |
| `prepare`, `emit`, `etxn_fee_base` | minimal Payment, Payment + 1 KiB Memo | + 1 KiB Memo |

Rule (from review): the table uses the reference value; if
`cost(largest) / cost(reference) > 10` the geometric mean of the two is used
instead, so that repeated worst-case calls cannot buy native CPU at the
reference price while everyone else is not charged the worst case. The report
always shows the fitted `a + b*size` line and the largest-size value so the
other policy can be applied without re-measuring. Justification for not using
the worst case for `util_sha512h`/`sto_*`/`prepare`: the hook must first write
those bytes into linear memory at one instruction each, which the instruction
term already charges. That defence does not hold for `otxn_field`, `otxn_slot`,
`slot`, `xpop_slot` (the object is materialised by the host), hence the >10x
rule.

### 2.5 Cross-check column (secondary)

The test also times `env(tx)` for every run. For loopable APIs the v1
differencing estimate `((T(N2) - T(N1))/(N2 - N1) - dI*t_instr - t_g) / K`
is printed next to the primary value; a disagreement > 20 % is flagged.
This is what a third party without the build flag can reproduce, and it bounds
the systematic error of the instrumented path.

### 2.6 Environment controls

* Release build only (`#ifndef NDEBUG` -> the suite prints a message and
  skips), `hook_cost_bench=ON`, `--unittest-jobs 1`, idle machine, warm-up
  execution per hook before timing.
* `hook_gas_price = 1000` in the benchmark config (a pure multiplier after the
  fact; touches nothing measured), explicit `fee(...)` on every transaction
  (JTX does not autofill hook fees), accounts funded with 1,000,000 XRP
  (200 distinct state keys need 200 reserve increments).
* Journal at the default test level (production-like `trace` behaviour).
* Report header: CPU, OS, compiler, build type, WasmEdge version, git SHA,
  wasmcc/clang and hook-cleaner versions, SHA-256 of every wasm blob, `t_clk`,
  `t_instr`, `t_call`, baseline fit R^2.

### 2.7 Rounding

`ceil(t_api / t_instr)`, round **up** to 2 significant digits, floor 10.
Three digits would present platform variance (tens of %) as precision; values
below 10 invite "free API" arguments although every host call crosses the
wasm/native boundary.

## 3. Deliverables

```
docs/hook-api-cost/DESIGN.md              this document
docs/hook-api-cost/README.md              how to build and run
docs/hook-api-cost/RESULTS.md             generated report
docs/hook-api-cost/hookcost.csv           raw rows (committed)
include/xrpl/hook/Bench.h                 counters (HOOK_COST_BENCH only)
include/xrpl/hook/Macro.h                 wrapper timer (HOOK_COST_BENCH only)
src/xrpld/app/hook/applyHook.h / .cpp     exec + finalize timers (HOOK_COST_BENCH only)
cmake/RippledSettings.cmake, RippledCore.cmake   option hook_cost_bench
src/test/app/hookcost/hookcost.c          benchmark hooks, one section per API/variant
src/test/app/hookcost/build.sh            wasmcc -O2 -I hook + hook-cleaner -> HookAPICost_wasm.h
src/test/app/HookAPICost_wasm.h           generated, committed
src/test/app/HookAPICost_test.cpp         BEAST_DEFINE_TESTSUITE_MANUAL(HookAPICost, app, ripple)
include/xrpl/hook/hook_api.macro          HOOK_API_COST values from RESULTS.md (separate commit)
```

## 4. Review decisions (recorded)

1. Normaliser: mean instruction time of typical compiled hook code. Both
   reviewers concur; cheapest-opcode rejected (inflates every API 2-3x for no
   CPU reason), deployed-hook mix rejected (not reproducible).
2. Size policy: reference size + linear model in the report, geometric-mean
   rule above 10x (methodology review), hard caps used where they exist
   (design review).
3. Synchronous side effects are in the window, attributed per call. Owner
   reserve prices storage, not apply-time CPU.
4. Primary measurement: in-process timers under a build flag (design review)
   because the 65535 static cap and the per-execution API caps make
   `env(tx)` differencing too coarse for capped and one-shot APIs. The
   methodology review preferred a single measurement path; resolved by keeping
   `env(tx)` differencing as a reported cross-check for every loopable API.
5. Floor 10, 2 significant digits, round up.

## 5. Platform requirement

The M3 Ultra / apple-clang run is the harness-validation draft. Before
`HOOK_API_COST` is finalised: one run on a Linux x86-64 Release build (gcc, the
Conan WasmEdge validators get, server hardware, turbo state recorded) at the
same git SHA. Gate: every API within 1.5x of the draft; outliers take the
larger value and a note. The Linux numbers are the canonical table.
