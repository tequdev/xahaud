# HookAPICost benchmark — how to build and run

See `DESIGN.md` for the methodology. This is the mechanical how-to.

`HookAPICost_test.cpp` is descriptor-driven: most rows are one `ApiSpec{...}`
entry (wasm section name, API name, loop N range, an optional `augment`
callback that shapes the invoking transaction — Blob, extra HookParameters,
Memos, Payment — and an optional `preSetup`). APIs that need cross-account
setup (`state_foreign_*`, `emit_*`), a dedicated Env (`xpop_slot` on Import
fixtures, `util_keylet` AMM/DID amendments) or a single-call measurement
(`accept`, `rollback`, `etxn_reserve`, `hook_again`) have their own code
paths. `RESULTS.md` ends with the proposed `HOOK_API_COST` block in
`hook_api.macro` order; the only APIs it cannot measure are the
`util_keylet` types that `util_keylet` rejects unconditionally on this branch
(listed under "Deferred").

## 1. Build

The benchmark timers only compile in when the `hook_cost_bench` CMake option
is on, and the suite itself refuses to run outside a Release
(`NDEBUG`) build (a Debug build's unoptimized host functions would inflate
every `t_api / t_instr` ratio).

```sh
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release -Dtests=ON -Dhook_cost_bench=ON
cmake --build build-release --target rippled
```

If `build-release` is already configured (e.g. from a normal dev build),
just add the flag and reconfigure in place, then build:

```sh
cmake -Dhook_cost_bench=ON build-release
cmake --build build-release --target rippled
```

`hook_cost_bench` is `OFF` by default and never affects a normal build: every
symbol it adds (`include/xrpl/hook/Bench.h`, the timers in
`include/xrpl/hook/Macro.h`, `src/xrpld/app/hook/applyHook.h`, and
`src/xrpld/app/hook/detail/applyHook.cpp`) is compiled out behind
`#ifdef HOOK_COST_BENCH`.

## 2. Run

```sh
./build-release/rippled --unittest=HookAPICost --unittest-jobs=1 \
    --unittest-arg=docs/hook-api-cost
```

* `HookAPICost` is a *manual* suite (`BEAST_DEFINE_TESTSUITE_MANUAL`): it does
  not run as part of `--unittest=app` or a full `--unittest` pass, only when
  named explicitly.
* `--unittest-jobs=1` is required — the benchmark measures wall-clock time
  and other jobs on the same machine would add noise.
* `--unittest-arg=<dir>` sets the output directory for `RESULTS.md` and
  `hookcost.csv` (default `docs/hook-api-cost` if omitted).
* Run on an otherwise idle machine. The suite does its own warm-up per hook
  and takes the min over repetitions, but OS scheduling noise still shows up
  in the outliers.

Outside a Release build configured with `-Dhook_cost_bench=ON`, the suite
logs a message and passes trivially instead of measuring anything.

## 3. Regenerating the benchmark wasm

The benchmark hooks live in `src/test/app/hookcost/hookcost.c` — one
`#if defined(B_<name>)` section per row of the results table, selected at
compile time by `-DB_<name>`. `src/test/app/HookAPICost_wasm.h` is the
generated, committed header the test includes; regenerate it after editing
`hookcost.c`:

```sh
src/test/app/hookcost/build.sh
```

Prerequisites (same toolchain as `src/test/app/build_test_hooks.sh`):

* `wasmcc` (https://github.com/wasienv/wasienv)
* `hook-cleaner` (https://github.com/RichardAH/hook-cleaner-c)
* `shasum` or `sha256sum`
* `clang-format` (optional — formats the generated header if present)

The script prints the `wasmcc` and `hook-cleaner` versions into the header as
comments, and records a SHA-256 of every wasm blob in `hookcost_sha256` in
the same header, so a rebuild can be checked byte-for-byte.

### Sizing a new benchmark hook's `MAXITER`

Every loopable hook in `hookcost.c` uses the shared `BENCH_BEGIN(MAXITER)` /
`BENCH_END` scaffold, which reads the iteration count `N` from a HookParameter
at runtime and loops up to `MAXITER` times (guarded by `GUARD(MAXITER)`). The
guard checker (`include/xrpl/hook/Guard.h`) rejects a hook whose *static*
worst-case instruction count reaches 65535, so `MAXITER` has to be sized per
hook body — a cheap body (a handful of instructions) tolerates a large
`MAXITER`; an expensive one (many unrolled units, or a host API call with
multiple pushed arguments) needs a much smaller one. There is no formula that
gets this right in one guess; the reliable way is to compile the hook, ask
the guard checker directly what its worst-case count is, and adjust:

```cpp
auto const whitelist = hook_api::getImportWhitelist(rules);
auto const guardVer = hook_api::getGuardRulesVersion(rules);
auto const res = validateGuards(
    wasmBytes, std::nullopt, "", /*returnCost=*/false, whitelist, guardVer);
// res is nullopt if rejected, else {worst-case instruction count, ...}
```

This runs instantly (no ledger, no RPC) and was used to calibrate every
`MAXITER` value currently in `hookcost.c`. Target a worst-case count around
55,000–60,000 (safety margin under the 65535 cap).

One nested-loop pitfall found while calibrating `base64`: the *runtime* guard
counter (`hookCtx.guard_map[id]` in `_g`'s implementation,
`src/xrpld/app/hook/detail/applyHook.cpp`) is **cumulative across the whole
hook execution**, not reset per outer-loop iteration. A `GUARDM` inside an
outer loop must therefore declare a bound covering the *total* number of
times it can be called across all outer iterations (`outer_bound *
inner_bound`), not just one outer iteration's worth — otherwise the hook
passes the static guard check at SetHook time but rolls back with
`GUARD_VIOLATION` the first time it actually runs past the first couple of
outer iterations. `base64` in this file avoids the whole class of bug by
using a single flat, fully-unrolled loop instead of a nested one.

## 4. Output

* `RESULTS.md` — the full report (header, baseline fit, per-API table,
  terminal APIs, notes). Also printed to the test log.
* `hookcost.csv` — the same per-API/terminal rows in CSV form.

Both are overwritten on every run; commit them only once the numbers are
final (see `DESIGN.md` §5 — the Linux x86-64 run is canonical).

## 5. What to expect from a run

A full run takes about 15 s. Four consecutive runs on an Apple M3 Ultra
(apple-clang 16, Release, other desktop applications running) gave
`t_instr` 3.56-4.11 ns, `G` 224-339 ns, `t_call` 194-222 ns. Of the 74
proposed costs, 64 moved by less than 1.2x between runs after the
2-significant-digit rounding; the widest spreads were `float_sto`
(70-110), `float_mulratio` (72-110), `xpop_slot` (7900-12000), `float_log`
(64-85) and `etxn_reserve` (55-73). Repeat the run a few times, keep the run whose baseline fit has the smallest
`SE(G)` (it must be below about 15 % of `G`), and compare the proposed blocks
across runs before adopting a value; a single run is a draft. The committed
`RESULTS.md` is the best-fit run out of five consecutive runs.

The table is not final until the Linux x86-64 run required by
`DESIGN.md` §5 exists: the interpreter-vs-native ratio is platform
dependent, and the `util_sha512h` / `util_verify` rows in particular use
ARM SHA-512 hardware acceleration that x86-64 validators do not have.
