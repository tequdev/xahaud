# Hook API Cost Benchmark

This report records Hook API costs measured with the opt-in
`hook_api_benchmark` instrumentation. The primary cost values below use only
successful API results (`return_code >= 0`, `RC_ACCEPT`, or `RC_ROLLBACK`).
Other negative error returns are counted separately so failure-heavy tests do
not pull the cost estimate toward early-return paths. Terminal `accept` /
`rollback` returns are included in the cost columns and also reported in the
`terminal` column.

The cost unit is relative to one Wasm instruction, so `relative cost = 1.0`
means the measured API call cost is approximately equal to one Wasm instruction.
The Wasm instruction baseline is derived from WasmEdge statistics:

```text
ns_per_wasm_instruction = 1,000,000,000 / WasmEdge_StatisticsGetInstrPerSecond(statsCtx)
```

The wall-clock `WasmEdge_VMRunWasmFromBuffer` time is still emitted as a
diagnostic, but it is not used as the denominator for Hook API relative costs
because it includes Wasm loading, validation, instantiation, and VM overhead.

## Measurement

- Date: 2026-06-09
- Branch: `benchmark`
- Build option: `-DHOOK_BENCHMARK=ON`
- Build type observed in CMake output: `Debug`
- Compiler observed in CMake output: AppleClang 16.0.0
- Table command:

```sh
node hook_api_cost_table.js build/hook_api_benchmark.csv
```

- Test command:

```sh
build/rippled --unittest=SetHook0,SetHook1,SetHook2,SetHook3,SetHook4,SetHook5,SetHook6,SetHook7 --unittest-jobs $(nproc) --quiet
```

The run completed successfully:

```text
24.4s, 8 suites, 736 cases, 97600 tests total, 0 failures
```

Coverage and sample size:

- Hook executions measured: 19,739
- Hook API observation rows: 151,272
- Total Hook API calls observed: 274,152
- Successful Hook API calls used for costs: 255,700
- Error Hook API calls excluded from costs: 18,452
- Terminal `accept` / `rollback` calls included in costs: 19,739
- Hook APIs measured: 75 / 75 definitions in `include/xrpl/hook/hook_api.macro`
- Missing Hook API definitions in this run: none
- `ns_per_wasm_instruction`: mean 20.31 ns, median 18.60 ns, p10 12.26 ns, p90 29.95 ns
- Wall-clock non-API time / statistics Wasm instruction time: mean 32.69x, median 26.87x, p90 41.52x

## Aggregation

- `success calls`: number of API calls whose result was `>= 0`, `RC_ACCEPT`, or
  `RC_ROLLBACK`; these are the only calls used for the cost columns.
- `avg ns/success`: total successful API nanoseconds divided by successful calls.
- `mean`: call-weighted mean of per-execution successful relative costs.
- `p50`, `p80`, `p95`: call-weighted percentiles of per-execution successful
  relative costs.
- `errors`: negative API results other than `RC_ACCEPT` and `RC_ROLLBACK`;
  these are excluded because they often early-return.
- `terminal`: `accept` and `rollback`; these end hook execution and are also
  included in success costs.
- `confidence`: rough sample-quality flag from successful sample count and
  p95/p50 spread. Low confidence means the value should be remeasured before use
  as a final constant.

For APIs with cache behavior, especially state and slot accessors, p80 or p95
is a better candidate than mean or p50 because repeated successful calls can hit
warmed caches and understate the first-access cost.

## Results

| API | success calls | avg ns/success | mean | p50 | p80 | p95 | errors | terminal | confidence |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---|
| `xpop_slot` | 16 | 547020.94 | 28877.26 | 28261.53 | 31417.48 | 34768.05 | 80 | 0 | low |
| `prepare` | 4,104 | 508795.21 | 26011.18 | 26682.12 | 29600.17 | 32287.97 | 64 | 0 | high |
| `util_verify` | 32 | 371578.09 | 16058.29 | 13781.77 | 20777.75 | 21564.38 | 72 | 0 | low |
| `emit` | 8,470 | 103028.13 | 6153.54 | 6100.98 | 7344.50 | 8086.01 | 4,244 | 0 | high |
| `etxn_fee_base` | 4,498 | 49773.64 | 3525.01 | 3554.54 | 3892.52 | 4250.32 | 128 | 0 | high |
| `state_foreign_set` | 5,898 | 15833.75 | 1011.97 | 527.24 | 1116.82 | 3243.35 | 1,338 | 0 | high |
| `sto_erase` | 32 | 8300.72 | 1028.42 | 833.00 | 1469.06 | 1822.17 | 72 | 0 | low |
| `state` | 8,254 | 25437.51 | 1126.37 | 1006.03 | 1415.36 | 1815.83 | 144 | 0 | high |
| `state_foreign` | 48 | 8170.98 | 794.08 | 485.47 | 1515.87 | 1805.02 | 72 | 0 | low |
| `slot` | 130 | 7602.55 | 409.73 | 187.39 | 717.06 | 1407.71 | 54 | 0 | medium |
| `sto_emplace` | 88 | 7555.91 | 637.53 | 477.95 | 965.01 | 1086.16 | 128 | 0 | low |
| `util_raddr` | 160 | 4859.89 | 956.36 | 945.99 | 970.78 | 982.48 | 24 | 0 | low |
| `state_set` | 23,846 | 8204.96 | 546.90 | 497.84 | 789.53 | 904.66 | 490 | 0 | high |
| `otxn_param` | 1,040 | 6199.15 | 441.85 | 302.25 | 812.35 | 885.86 | 112 | 0 | high |
| `util_accid` | 160 | 4296.12 | 686.59 | 689.25 | 701.93 | 710.20 | 24 | 0 | low |
| `hook_param` | 416 | 3745.08 | 460.94 | 498.52 | 514.52 | 537.65 | 128 | 0 | medium |
| `otxn_field` | 8,796 | 5804.03 | 347.44 | 329.16 | 398.51 | 468.69 | 48 | 0 | high |
| `etxn_details` | 8,554 | 5497.00 | 359.63 | 374.02 | 407.95 | 438.08 | 32 | 0 | high |
| `otxn_id` | 424 | 3982.02 | 278.99 | 266.57 | 331.20 | 422.71 | 32 | 0 | medium |
| `sto_subfield` | 40 | 4754.07 | 232.16 | 205.70 | 258.13 | 362.60 | 32 | 0 | low |
| `hook_param_set` | 96 | 3893.68 | 316.16 | 316.85 | 333.89 | 358.25 | 192 | 0 | low |
| `float_sum` | 384 | 3336.28 | 317.77 | 330.30 | 338.23 | 342.91 | 0 | 0 | medium |
| `sto_validate` | 752 | 4220.50 | 201.35 | 188.38 | 231.28 | 332.07 | 24 | 0 | medium |
| `slot_set` | 2,184 | 5048.39 | 336.02 | 314.27 | 318.44 | 331.67 | 80 | 0 | high |
| `float_mulratio` | 400 | 3197.47 | 306.03 | 305.90 | 315.18 | 329.29 | 64 | 0 | medium |
| `util_sha512h` | 176 | 1724.15 | 266.95 | 269.68 | 274.89 | 326.44 | 24 | 0 | medium |
| `slot_size` | 2,240 | 4221.79 | 292.33 | 299.62 | 315.38 | 317.18 | 24 | 0 | high |
| `hook_hash` | 88 | 3304.39 | 187.52 | 169.45 | 238.68 | 308.25 | 96 | 0 | low |
| `otxn_slot` | 6,192 | 4732.36 | 273.72 | 282.87 | 302.12 | 307.15 | 16 | 0 | high |
| `trace` | 4,214 | 4160.72 | 224.08 | 222.29 | 252.77 | 298.70 | 32 | 0 | high |
| `sto_subarray` | 48 | 4592.92 | 195.12 | 184.88 | 234.78 | 280.59 | 64 | 0 | low |
| `ledger_keylet` | 16 | 5088.63 | 247.82 | 250.71 | 258.63 | 274.38 | 240 | 0 | low |
| `float_divide` | 480 | 2823.45 | 244.95 | 250.10 | 258.95 | 272.52 | 48 | 0 | medium |
| `otxn_generation` | 8,192 | 3201.84 | 196.11 | 192.85 | 235.06 | 263.41 | 0 | 0 | high |
| `float_invert` | 80 | 3266.69 | 196.98 | 189.36 | 211.07 | 261.81 | 32 | 0 | low |
| `hook_again` | 72 | 2389.97 | 103.85 | 74.00 | 208.24 | 247.56 | 64 | 0 | low |
| `float_multiply` | 768 | 2189.08 | 219.65 | 218.67 | 225.13 | 243.66 | 80 | 0 | medium |
| `trace_num` | 1,864 | 3174.49 | 224.13 | 230.36 | 239.19 | 243.18 | 16 | 0 | high |
| `otxn_burden` | 16,352 | 2711.45 | 168.51 | 167.42 | 205.92 | 235.03 | 0 | 0 | high |
| `etxn_burden` | 8,176 | 2676.08 | 166.51 | 165.83 | 203.64 | 234.29 | 8,176 | 0 | high |
| `slot_clear` | 8 | 5875.00 | 186.65 | 175.50 | 204.11 | 229.03 | 16 | 0 | low |
| `meta_slot` | 16 | 3539.06 | 173.29 | 166.37 | 187.05 | 225.25 | 16 | 0 | low |
| `util_keylet` | 336 | 2145.18 | 193.42 | 209.26 | 218.54 | 223.89 | 120 | 0 | medium |
| `etxn_nonce` | 2,048 | 2173.59 | 215.88 | 216.58 | 218.88 | 221.68 | 40 | 0 | low |
| `_g` | 54,275 | 2104.82 | 147.88 | 153.98 | 178.53 | 219.88 | 0 | 0 | high |
| `slot_subfield` | 2,298 | 2856.13 | 186.84 | 199.67 | 204.36 | 204.67 | 62 | 0 | high |
| `slot_subarray` | 2,032 | 2612.58 | 197.58 | 197.43 | 202.33 | 202.61 | 24 | 0 | low |
| `float_sto` | 144 | 2427.34 | 152.65 | 149.90 | 160.66 | 186.72 | 224 | 0 | medium |
| `float_log` | 80 | 2181.22 | 165.88 | 164.96 | 173.87 | 183.93 | 32 | 0 | low |
| `ledger_last_hash` | 48 | 3455.77 | 151.62 | 131.33 | 161.42 | 183.26 | 96 | 0 | low |
| `ledger_nonce` | 32 | 3403.75 | 137.53 | 136.03 | 144.43 | 177.86 | 32 | 0 | low |
| `hook_skip` | 96 | 2593.78 | 140.07 | 139.25 | 151.47 | 173.15 | 384 | 0 | low |
| `float_root` | 64 | 2615.83 | 147.30 | 148.06 | 149.70 | 169.70 | 16 | 0 | low |
| `float_negate` | 384 | 1607.76 | 113.15 | 125.99 | 149.52 | 164.17 | 32 | 0 | medium |
| `slot_count` | 16 | 2018.31 | 119.83 | 95.28 | 158.86 | 163.86 | 16 | 0 | low |
| `float_mantissa` | 4,272 | 1486.26 | 131.65 | 140.18 | 150.74 | 157.60 | 32 | 0 | high |
| `float_sto_set` | 272 | 2041.50 | 121.83 | 122.94 | 130.76 | 140.86 | 80 | 0 | medium |
| `slot_float` | 8 | 4494.88 | 120.93 | 121.48 | 132.19 | 133.57 | 16 | 0 | low |
| `float_compare` | 544 | 2232.98 | 124.17 | 124.23 | 128.90 | 132.62 | 128 | 0 | medium |
| `etxn_reserve` | 8,386 | 1626.78 | 99.42 | 96.85 | 118.50 | 132.54 | 32 | 0 | high |
| `ledger_seq` | 4,514 | 1531.66 | 108.44 | 107.63 | 120.53 | 132.09 | 0 | 0 | high |
| `hook_account` | 16,272 | 1666.92 | 85.08 | 83.75 | 106.51 | 125.56 | 288 | 0 | high |
| `etxn_generation` | 8,176 | 1379.99 | 85.63 | 85.39 | 104.41 | 119.84 | 0 | 0 | high |
| `otxn_type` | 48 | 1888.92 | 70.16 | 54.78 | 105.07 | 118.10 | 0 | 0 | low |
| `slot_type` | 40 | 2458.30 | 107.35 | 105.57 | 114.89 | 117.48 | 16 | 0 | low |
| `ledger_last_time` | 48 | 1952.27 | 83.28 | 81.98 | 88.14 | 108.11 | 0 | 0 | low |
| `fee_base` | 8 | 1989.50 | 54.58 | 47.66 | 51.03 | 105.97 | 0 | 0 | low |
| `float_int` | 1,080 | 1563.37 | 91.01 | 91.24 | 92.58 | 101.25 | 80 | 0 | medium |
| `float_set` | 384 | 1580.94 | 86.01 | 85.06 | 89.58 | 99.41 | 32 | 0 | medium |
| `float_sign` | 368 | 1484.47 | 62.50 | 63.21 | 66.36 | 70.33 | 32 | 0 | medium |
| `hook_pos` | 620 | 197.54 | 13.53 | 11.21 | 17.27 | 29.12 | 0 | 0 | medium |
| `float_one` | 1,264 | 111.26 | 8.03 | 7.94 | 10.17 | 14.31 | 0 | 0 | high |
| `accept` | 15,271 | 1605.20 | 87.49 | 82.52 | 106.25 | 129.73 | 0 | 15,271 | high |
| `rollback` | 4,468 | 1857.93 | 120.15 | 119.32 | 139.97 | 160.81 | 0 | 4,468 | high |
| `trace_float` | 0 | n/a | n/a | n/a | n/a | n/a | 16 | 0 | n/a |

## Validation

The result is suitable as a benchmark-output report for this branch. It is more
reliable than the previous mixed aggregate because failure-heavy tests no longer
contribute early-return timings to the cost columns. It is also a better Hook
API versus Wasm instruction comparison than the earlier wall-clock denominator:
the wall-clock non-API time is roughly 27x the WasmEdge statistics instruction
time at the median, showing that VM setup/overhead was materially inflating the
old denominator.

Evidence that the measurement is internally valid:

- The opt-in benchmark build linked successfully.
- The measured `SetHook0` through `SetHook7` run passed all tests.
- Every Hook API definition in `include/xrpl/hook/hook_api.macro` appeared in
  the measurement output.
- Successful and error call counts add up to the total observed API calls.
  Terminal calls are a subset of successful calls.
- `accept` and `rollback` have terminal calls that are also included in success
  costs, and `trace_float` has only error calls in this test set, so only
  `trace_float` has no success cost value.
- High-error APIs such as `etxn_burden`, `emit`, `state_foreign_set`, and
  `state_set` are no longer averaged with their failure paths.
- Cache-sensitive APIs still show skew after switching to the statistics
  denominator. For example `state_set` has p50 497.84 and p95 904.66, while
  `state_foreign_set` has p50 527.24 and p95 3243.35. That supports using
  p80/p95 rather than simple median or mean for conservative calibration.

Important limitations:

- The run used a Debug build. Absolute timings and some relative timings can
  differ materially in Release.
- The tests were run with `--unittest-jobs $(nproc)`, so wall-clock timings for
  host functions can include scheduler and CPU contention noise.
- Some APIs still have low successful sample counts, including `xpop_slot`,
  `util_verify`, `sto_erase`, `state_foreign`, `ledger_keylet`, `fee_base`, and
  `ledger_last_time`. These are marked low confidence.
- The numerator still uses elapsed host time around each Wasm import wrapper.
  The denominator uses WasmEdge statistics, so it is closer to an instruction
  baseline but should still be validated in repeated controlled Release runs.

Recommended next validation before assigning production constants:

1. Run the same benchmark in Release with controlled CPU load.
2. Repeat the run several times and compare p80/p95 stability for each API.
3. Add dedicated success-path benchmark hooks for low-confidence APIs and for
   APIs whose current tests mostly exercise errors.
4. For cache-sensitive APIs, add separate cold-cache and warm-cache scenarios
   instead of relying on one mixed distribution.
