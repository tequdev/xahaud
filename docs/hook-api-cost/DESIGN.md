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

### 2.1 Two estimators

**E2E (end-to-end differencing)** — the table value wherever it can be
measured. Each benchmark hook loops N times (N read at runtime from a 4-byte
big-endian HookParameter, so the wasm is byte-identical across N) calling the
API K times per iteration. The same transaction is measured at N1 and N2
(10 repetitions each, minimum) on the closed-ledger apply (§2.5a):

    dT  = (T(N2) - T(N1)) / (N2 - N1)     ns per iteration (env.close wall time)
    dI  = (I(N2) - I(N1)) / (N2 - N1)     runtime wasm instructions per iteration
    E2E(api) = (dT - dI * t_instr - G) / K

`t_instr` (slope) and `G` (intercept: the total per-iteration cost of the
mandatory loop-head `_g` call) come from a least-squares fit of `dT` against
`dI` over pure-wasm baseline hooks whose body is unrolled 1/2/4/8/16/64 times.
E2E contains everything the call causes inside the apply: host-call boundary,
host function body, hook-state flush, invariant checks, ledger/SHAMap writes.
It needs no build flag and is what a third party reproduces from a Release
build. A multi-API loop body is decomposed by subtracting the other APIs' own
E2E values; rows that cannot be decomposed fall back to HF.

**HF (host-function timer)** — needed for APIs that cannot be looped enough
for differencing (capped per execution or one-shot). CMake option
`hook_cost_bench` (default OFF, never in a validator binary) defines
`HOOK_COST_BENCH`; `DEFINE_HOOK_FUNCTION` then times each host function body
into a per-API counter, `executeWasm` times the wasm run, and
`finalizeHookState`, `finalizeHookResult` and the invariant visit in
`ApplyContext::checkInvariantsHelper` (hook-state entries only) are timed and
attributed per modified entry / emitted transaction:

    HF(api) = (M_api - 2 * t_clk) + t_call [+ side-effect shares]

`t_clk` is the clock-read overhead (two reads per wrapper) and `t_call` the
0-argument host-call boundary, measured on purpose by differencing two hooks
that call `hook_pos` 16 and 1 times per iteration (the loop-head `_g` cancels):
`t_call = (excess_k16 - excess_k1) / 15 - (M_pos - 2 t_clk)`, gated at 5 %
propagated uncertainty before any HF row is emitted.
The boundary grows with the number of wasm arguments (about +25 ns per
argument on the draft platform: the 2-argument `_g` costs ~55 ns more than
`hook_pos`), which is why HF is the fallback, not the primary. Every row
prints both estimators; a difference above 30 % is annotated.

Table rule: E2E when it exists and is resolvable — propagated per-call
uncertainty `(median(T) - min(T)) / ((N2 - N1) K)` below `max(20 ns, 10 % of E2E)`
and E2E not below the physical floor `t_call + (M - 2 t_clk)` — otherwise HF,
with the reason printed. No value is ever substituted by the other estimator.

`state_set` / `state_foreign_set` are HF by construction. Their E2E is far larger
(about 24 us per *created* and 7 us per *modified* hook-state entry on the draft
platform) and that excess is genuine closed-apply work (SHAMap leaf and path
rehash, node-store write, CreatedNode metadata, owner-directory insert), but it
is a cost per ledger *entry* rather than per API call, it depends on the
node-store backend, and ledger growth is what the owner reserve prices. The
report lists it separately as "apply-time ledger cost, not charged by
HOOK_API_COST" so HookFeeV2 can decide on a per-created-entry charge
explicitly rather than by where the cost happens to land.

### 2.2 Baselines

Body: byte-wise buffer walk compiled from C at -O2 (local.get/set, i32
load/store, add/xor/and, compare, br_if) unrolled 1/2/4/8/16/64 times, each
with its own N1/N2 fitting its static budget (N2 <= 65534 / static
instructions per iteration). Gates: R^2 > 0.99 and the standard error of the
intercept `G` printed; `dI` must match the guard checker's own per-iteration
count for that body within 40 % (catches compiler unrolling, which is a
multiplicative 2x+ effect; the slack absorbs the guard prologue's
static-vs-runtime accounting gap at low `dI`). Two extra
bodies (pure i64 arithmetic; memory-copy heavy) give a sensitivity range for
`t_instr`; if they differ from the buffer walk by more than 2x the geometric
mean is used and stated.

### 2.3 Per-API scenarios

K = calls per iteration (4 for APIs cheaper than ~100 ns so the signal
dominates `G`, else 1); capped APIs use K = min(cap, 200) calls per execution
and a single N point; one-shot APIs are timed by HF as the mean over 200
executions (see §2.5b). Every hook checks the return value of every call and
rolls back with the code on error, so an error path can never be recorded as
a measurement; the harness additionally flags any ledger-touching API whose
HF time sits at the trivial-API floor.

| API | scenario |
|---|---|
| `accept`, `rollback` | HF, one call per execution, mean over 200 |
| `etxn_reserve`, `hook_again` | HF, first call; later calls are `ALREADY_SET` |
| `emit` | `etxn_reserve(200)`, 200 emits each with its own `etxn_nonce`/`etxn_details`, decomposed by their single-API E2E values; the window includes emitted-txn object creation and the TxQ injection at close |
| `state`, `state_foreign` | reads are cached per key: 200 *distinct* pre-created keys per execution, disjoint key ranges per size |
| `state_set` | `_create` (fresh keys every rep via a salt parameter) and `_modify` (fixed keys); table = max, stated |
| `state_foreign_set` | HookGrant on the foreign account; K = 1 (first call, grant scan) and K = 200; table = first call |
| `slot_set` | 34-byte keylet form only |
| `slot_*`, `otxn_slot`, `meta_slot`, `xpop_slot` | explicit slot numbers |
| `slot_clear` | paired with `slot_set`, decomposed |
| `hook_skip` | two hooks installed; flags alternate 1/0 |
| `hook_param_set` | K = 16 (cap) |
| `meta_slot` | the hook calls `hook_again()` in the strong pass and loops `meta_slot` in the weak pass; both inside the same close |
| `xpop_slot` | on a `ttIMPORT` transaction with the `ImportTCAccountSet` fixtures |
| `util_verify` | passing ed25519 and secp256k1 verifications; table = max |
| `float_sto` | XRP / IOU / short-form; table = max |
| `util_keylet`, `slot_type`, `otxn_id` | all implemented modes; table = max (types that return INVALID_ARGUMENT unconditionally on this branch are listed as not measurable) |
| `trace*` | early-return at production journal level; measured as such and stated |
| `ledger_keylet` | lower bound on a near-empty JTX ledger, stated |

### 2.4 Size dependence

| API family | sizes | table value |
|---|---|---|
| `util_sha512h` | 32 B, 1 KiB, 16 KiB | 1 KiB (see rule) |
| `sto_*` | ~30 B, ~250 B (real tx), ~4 KiB | 250 B (see rule) |
| `state*` | 32 B, 256 B, 4096 B (ExtendedHookState) | 256 B |
| `otxn_field`, `otxn_slot`, `slot` | 20 B field / 1 KiB Blob / 16 KiB Blob | 1 KiB (see rule) |
| `otxn_param`, `hook_param`, `hook_param_set` | 32 B, 256 B | 256 B (hard cap) |
| `prepare`, `emit`, `etxn_fee_base` | minimal Payment, Invoke + 1 KiB Blob | + 1 KiB |

Rule: the table uses the reference value; if `cost(largest)/cost(reference) > 10`
the geometric mean of the two is used instead. The report always prints the
fitted `a + b*size` line and the largest-size value.

### 2.5 Crypto caveat

`util_sha512h` and `util_verify` run on ARMv8 SHA-512 hardware on the draft
platform; x86-64 validators without that acceleration are several times slower
*relative to the interpreter*. Those rows are marked and must be taken from
the Linux x86-64 run (§5) before adoption.

### 2.5a Closed-ledger apply

JTX `env(tx)` applies to the *open* ledger: no metadata is generated and
`finalizeHookResult` returns early, so emitted-transaction objects are never
created in that window. Validators run the canonical apply on the *closed*
ledger during consensus. All timing therefore happens around `env.close()`:
submit untimed, reset counters, time the close, snapshot, read the metadata,
then one extra untimed close to drain emitted transactions. The harness
asserts the hook executed exactly once inside the timed close.

### 2.5b Clock resolution and one-shot APIs

`steady_clock` on Apple Silicon ticks every 41.67 ns; the tick is measured and
printed in the header. Loop APIs average thousands of samples so quantisation
is harmless; one-shot APIs use the *mean* over 200 executions (a minimum would
always select the low tick).

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
   rule above 10x, hard caps used where they exist.
3. Synchronous side effects are in the window, attributed per call. Owner
   reserve prices storage, not apply-time CPU.
4. Estimators: E2E differencing is the table value (reproducible without a
   build flag, contains all apply-time work); the host-function timer is the
   fallback for capped and one-shot APIs. Two code-review rounds established
   that the host-call boundary depends on argument count, so a timer-based
   primary with a single `t_call` constant is not self-consistent; the earlier
   `max(primary, cross-check)` rule was withdrawn for the same reason.
5. Floor 10, 2 significant digits, round up.

## 5. Platform requirement

The M3 Ultra / apple-clang run is the harness-validation draft. Before
`HOOK_API_COST` is finalised: one run on a Linux x86-64 Release build (gcc, the
Conan WasmEdge validators get, server hardware, turbo state recorded) at the
same git SHA. Gate: every API within 1.5x of the draft; outliers take the
larger value and a note. The Linux numbers are the canonical table.

Status: done on 2026-09-07 (`COMPARISON.md`, `RESULTS-linux-x86_64.md`). The
Linux host was a QEMU VM with gcc 13. Decision taken afterwards: the Linux
median is adopted for every API (the 1.5x gate is reported for information
only), rounded up to two significant digits, or one for two-digit values.
A bare-metal x86-64 run would tighten the VM's ~1.3x run-to-run spread.
