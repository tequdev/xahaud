# Cross-platform comparison (DESIGN §5)

Canonical platform: Linux x86-64. Draft platform: Apple M3 Ultra (`RESULTS.md`).

## Linux x86-64 run

* Host: Ubuntu 26.04 VM, `QEMU Virtual CPU version 2.5+` (10 vCPU, 2.1 GHz, no
  SSE4/AVX/SHA extensions exposed), kvm-clock, clock resolution 17 ns.
* Toolchain: nix (nixpkgs weekly rev `56c02bc00adcf003215cc4bd996d6efaf4cff188`),
  gcc 13.4.0, libstdc++, cmake 4 with `CMAKE_POLICY_VERSION_MINIMUM=3.5`,
  conan 2.32, WasmEdge 0.11.2 (manylinux2014 binary), git SHA 5c942671dd
  (every API call checked for its documented success value; `_g` reported).
* Procedure: `README.md` §6. 30 runs pinned to one vCPU with `taskset -c 7`.
  Six met the fit-quality gate (`SE(G)/G < 15 %`, `R^2 > 0.998`): pin2, pin6,
  pin12, pin19, pin25, pin26; three of those also passed the 15 % `t_call`
  calibration gate (the others read 16-19 %, which only moves the HF fallback
  rows by a few %). `RESULTS-linux-x86_64.md` is pin19 (`t_instr` 5.87 ns,
  `G` 326 ns, SE 24 ns, `t_call` 289 ns). The comparison uses the per-API
  **median over the six runs**; their spread is at most 1.33x
  (39 of 75 APIs within 1.2x).
* Fit constants across the six runs: `t_instr` 5.2-6.7 ns, `G` 295-455 ns,
  `t_call` 262-298 ns. The interpreter is about 1.6x slower per instruction
  than on the M3 while the host functions are not, which is why most Linux
  costs come out lower.

## Adopted table (common-baseline method)

Decision (2026-09-07): **the Linux measurement is adopted for every API,
including `_g`**. Method (DESIGN §2.6a): per API, the median over all
quality Linux runs of (per-run table value x that run's `t_instr`) — the
API's wall time in ns at the DESIGN §2.4 table rule — divided by the pooled
`t_instr`, the median over the same runs. Quality runs: 14 across three
batches (`SE(G)/G < 15 %`, `R^2 > 0.998`): first batch pin1/3/6/8/9/10,
second pin2/6/12/19/25/26, third pin6/10; `sto_validate` and `prepare` use
the second and third batches only because their hooks were corrected after
the first. The API times reproduce to well under 1 % between batches while
the per-run interpreter baseline drifts by about 10 % on this VM, so pairing
them per run only adds noise. Pooled `t_instr` = 5.81 ns; `_g` is the pooled
median of the baseline fit intercept `G` (381 ns) over the same `t_instr`.
The guard checker does not charge loop-head guards today, so applying the
`_g` value needs a checker change. `RESULTS-linux-x86_64.md` is the third
batch's pin6 (`SE(G)` 8 ns, `R^2` 1.0000), which also prints the `_g` row.

Rounding: three or more digits round up to two significant digits, two-digit
values round up to one significant digit (1234 -> 1300, 123 -> 130, 39 -> 40).

| API | current | API time ns | ratio | adopted |
|---|---:|---:|---:|---:|
| _g | 220 | 381 | 65.6 | 70 |
| accept | 150 | 442 | 76.1 | 80 |
| rollback | 180 | 416 | 71.7 | 80 |
| util_raddr | 980 | 672 | 115.7 | 120 |
| util_accid | 690 | 635 | 109.3 | 110 |
| util_verify | 24000 | 24494 | 4217.8 | 4300 |
| util_sha512h | 340 | 5514 | 949.6 | 950 |
| util_keylet | 230 | 566 | 97.5 | 100 |
| sto_validate | 350 | 682 | 117.5 | 120 |
| sto_subfield | 340 | 520 | 89.5 | 90 |
| sto_subarray | 290 | 411 | 70.7 | 80 |
| sto_emplace | 980 | 555 | 95.6 | 100 |
| sto_erase | 970 | 442 | 76.1 | 80 |
| etxn_burden | 260 | 354 | 61.0 | 70 |
| etxn_details | 470 | 769 | 132.4 | 140 |
| etxn_fee_base | 4600 | 4598 | 791.8 | 800 |
| etxn_reserve | 150 | 482 | 83.0 | 90 |
| etxn_generation | 130 | 311 | 53.6 | 60 |
| etxn_nonce | 230 | 617 | 106.2 | 110 |
| emit | 8700 | 10086 | 1736.8 | 1800 |
| float_set | 110 | 414 | 71.3 | 80 |
| float_multiply | 240 | 446 | 76.8 | 80 |
| float_mulratio | 390 | 359 | 61.8 | 70 |
| float_negate | 160 | 315 | 54.3 | 60 |
| float_compare | 140 | 350 | 60.3 | 70 |
| float_sum | 350 | 367 | 63.2 | 70 |
| float_sto | 230 | 341 | 58.7 | 60 |
| float_sto_set | 140 | 319 | 55.0 | 60 |
| float_invert | 230 | 313 | 54.0 | 60 |
| float_divide | 280 | 337 | 58.0 | 60 |
| float_one | 20 | 267 | 46.0 | 50 |
| float_mantissa | 170 | 316 | 54.4 | 60 |
| float_sign | 80 | 313 | 54.0 | 60 |
| float_int | 100 | 317 | 54.5 | 60 |
| float_log | 100 | 328 | 56.4 | 60 |
| float_root | 190 | 371 | 63.9 | 70 |
| fee_base | 70 | 316 | 54.4 | 60 |
| ledger_seq | 140 | 317 | 54.6 | 60 |
| ledger_last_time | 110 | 316 | 54.4 | 60 |
| ledger_last_hash | 210 | 322 | 55.4 | 60 |
| ledger_nonce | 170 | 516 | 88.9 | 90 |
| ledger_keylet | 300 | 758 | 130.5 | 140 |
| hook_account | 140 | 322 | 55.4 | 60 |
| hook_hash | 340 | 360 | 62.0 | 70 |
| hook_param_set | 370 | 494 | 85.1 | 90 |
| hook_param | 510 | 351 | 60.5 | 70 |
| hook_again | 260 | 433 | 74.5 | 80 |
| hook_skip | 170 | 362 | 62.4 | 70 |
| hook_pos | 40 | 266 | 45.8 | 50 |
| slot | 1400 | 686 | 118.2 | 120 |
| slot_clear | 230 | 455 | 78.3 | 80 |
| slot_count | 230 | 322 | 55.4 | 60 |
| slot_set | 350 | 1831 | 315.3 | 320 |
| slot_size | 330 | 503 | 86.6 | 90 |
| slot_subarray | 330 | 335 | 57.6 | 60 |
| slot_subfield | 220 | 337 | 58.1 | 60 |
| slot_type | 210 | 343 | 59.0 | 60 |
| slot_float | 150 | 387 | 66.6 | 70 |
| state_set | 900 | 3757 | 647.0 | 650 |
| state_foreign_set | 3400 | 34466 | 5935.2 | 6000 |
| state | 1700 | 2337 | 402.5 | 410 |
| state_foreign | 1700 | 2443 | 420.8 | 430 |
| trace | 100 | 1390 | 239.4 | 240 |
| trace_num | 100 | 516 | 88.9 | 90 |
| trace_float | 100 | 566 | 97.5 | 100 |
| otxn_burden | 260 | 350 | 60.3 | 70 |
| otxn_field | 460 | 381 | 65.6 | 70 |
| otxn_generation | 280 | 349 | 60.1 | 70 |
| otxn_id | 450 | 321 | 55.3 | 60 |
| otxn_type | 130 | 319 | 55.0 | 60 |
| otxn_slot | 310 | 663 | 114.2 | 120 |
| otxn_param | 830 | 411 | 70.8 | 80 |
| meta_slot | 220 | 328 | 56.5 | 60 |
| xpop_slot | 37000 | 28578 | 4921.2 | 5000 |
| prepare | 36000 | 32518 | 5599.6 | 5600 |

```
HOOK_API_COST(_g, 70, uint256{})  // loop-head guard; not charged by the guard checker today
HOOK_API_COST(accept, 80, uint256{})
HOOK_API_COST(rollback, 80, uint256{})
HOOK_API_COST(util_raddr, 120, uint256{})
HOOK_API_COST(util_accid, 110, uint256{})
HOOK_API_COST(util_verify, 4300, uint256{})
HOOK_API_COST(util_sha512h, 950, uint256{})
HOOK_API_COST(util_keylet, 100, uint256{})
HOOK_API_COST(sto_validate, 120, uint256{})
HOOK_API_COST(sto_subfield, 90, uint256{})
HOOK_API_COST(sto_subarray, 80, uint256{})
HOOK_API_COST(sto_emplace, 100, uint256{})
HOOK_API_COST(sto_erase, 80, uint256{})
HOOK_API_COST(etxn_burden, 70, uint256{})
HOOK_API_COST(etxn_details, 140, uint256{})
HOOK_API_COST(etxn_fee_base, 800, uint256{})
HOOK_API_COST(etxn_reserve, 90, uint256{})
HOOK_API_COST(etxn_generation, 60, uint256{})
HOOK_API_COST(etxn_nonce, 110, uint256{})
HOOK_API_COST(emit, 1800, uint256{})
HOOK_API_COST(float_set, 80, uint256{})
HOOK_API_COST(float_multiply, 80, uint256{})
HOOK_API_COST(float_mulratio, 70, uint256{})
HOOK_API_COST(float_negate, 60, uint256{})
HOOK_API_COST(float_compare, 70, uint256{})
HOOK_API_COST(float_sum, 70, uint256{})
HOOK_API_COST(float_sto, 60, uint256{})
HOOK_API_COST(float_sto_set, 60, uint256{})
HOOK_API_COST(float_invert, 60, uint256{})
HOOK_API_COST(float_divide, 60, uint256{})
HOOK_API_COST(float_one, 50, uint256{})
HOOK_API_COST(float_mantissa, 60, uint256{})
HOOK_API_COST(float_sign, 60, uint256{})
HOOK_API_COST(float_int, 60, uint256{})
HOOK_API_COST(float_log, 60, uint256{})
HOOK_API_COST(float_root, 70, uint256{})
HOOK_API_COST(fee_base, 60, uint256{})
HOOK_API_COST(ledger_seq, 60, uint256{})
HOOK_API_COST(ledger_last_time, 60, uint256{})
HOOK_API_COST(ledger_last_hash, 60, uint256{})
HOOK_API_COST(ledger_nonce, 90, uint256{})
HOOK_API_COST(ledger_keylet, 140, uint256{})
HOOK_API_COST(hook_account, 60, uint256{})
HOOK_API_COST(hook_hash, 70, uint256{})
HOOK_API_COST(hook_param_set, 90, uint256{})
HOOK_API_COST(hook_param, 70, uint256{})
HOOK_API_COST(hook_again, 80, uint256{})
HOOK_API_COST(hook_skip, 70, uint256{})
HOOK_API_COST(hook_pos, 50, uint256{})
HOOK_API_COST(slot, 120, uint256{})
HOOK_API_COST(slot_clear, 80, uint256{})
HOOK_API_COST(slot_count, 60, uint256{})
HOOK_API_COST(slot_set, 320, uint256{})
HOOK_API_COST(slot_size, 90, uint256{})
HOOK_API_COST(slot_subarray, 60, uint256{})
HOOK_API_COST(slot_subfield, 60, uint256{})
HOOK_API_COST(slot_type, 60, uint256{})
HOOK_API_COST(slot_float, 70, uint256{})
HOOK_API_COST(state_set, 650, uint256{})
HOOK_API_COST(state_foreign_set, 6000, uint256{})
HOOK_API_COST(state, 410, uint256{})
HOOK_API_COST(state_foreign, 430, uint256{})
HOOK_API_COST(trace, 240, uint256{})
HOOK_API_COST(trace_num, 90, uint256{})
HOOK_API_COST(trace_float, 100, uint256{})
HOOK_API_COST(otxn_burden, 70, uint256{})
HOOK_API_COST(otxn_field, 70, uint256{})
HOOK_API_COST(otxn_generation, 70, uint256{})
HOOK_API_COST(otxn_id, 60, uint256{})
HOOK_API_COST(otxn_type, 60, uint256{})
HOOK_API_COST(otxn_slot, 120, uint256{})
HOOK_API_COST(otxn_param, 80, uint256{})
HOOK_API_COST(meta_slot, 60, uint256{})
HOOK_API_COST(xpop_slot, 5000, uint256{})
HOOK_API_COST(prepare, 5600, uint256{})
```

## Per-API comparison against the M3 draft (1.5x gate, informational)

| API | Linux x86-64 (median) | Apple M3 Ultra | ratio | verdict |
|---|---:|---:|---:|---|
| _g | 220 | 220 | - | unmeasured |
| accept | 73 | 79 | 1.08 | ok |
| rollback | 69 | 76 | 1.10 | ok |
| util_raddr | 110 | 180 | 1.64 | outside 1.5x gate -> max 180 |
| util_accid | 103 | 140 | 1.36 | ok |
| util_verify | 4000 | 8300 | 2.08 | outside 1.5x gate -> max 8300 |
| util_sha512h | 899 | 930 | 1.03 | ok |
| util_keylet | 92 | 170 | 1.85 | outside 1.5x gate -> max 170 |
| sto_validate | 110 | 220 | 2.00 | outside 1.5x gate -> max 220 |
| sto_subfield | 84 | 180 | 2.14 | outside 1.5x gate -> max 180 |
| sto_subarray | 67 | 130 | 1.94 | outside 1.5x gate -> max 130 |
| sto_emplace | 91 | 190 | 2.09 | outside 1.5x gate -> max 190 |
| sto_erase | 72 | 140 | 1.94 | outside 1.5x gate -> max 140 |
| etxn_burden | 58 | 86 | 1.48 | ok |
| etxn_details | 130 | 170 | 1.31 | ok |
| etxn_fee_base | 755 | 1300 | 1.72 | outside 1.5x gate -> max 1300 |
| etxn_reserve | 80 | 73 | 0.91 | ok |
| etxn_generation | 50 | 66 | 1.32 | ok |
| etxn_nonce | 103 | 130 | 1.26 | ok |
| emit | 1650 | 2500 | 1.52 | outside 1.5x gate -> max 2500 |
| float_set | 68 | 78 | 1.15 | ok |
| float_multiply | 72 | 89 | 1.24 | ok |
| float_mulratio | 58 | 79 | 1.36 | ok |
| float_negate | 51 | 70 | 1.37 | ok |
| float_compare | 57 | 78 | 1.37 | ok |
| float_sum | 60 | 79 | 1.32 | ok |
| float_sto | 55 | 81 | 1.47 | ok |
| float_sto_set | 51 | 75 | 1.47 | ok |
| float_invert | 50 | 69 | 1.38 | ok |
| float_divide | 54 | 85 | 1.57 | outside 1.5x gate -> max 85 |
| float_one | 43 | 52 | 1.21 | ok |
| float_mantissa | 51 | 110 | 2.16 | outside 1.5x gate -> max 110 |
| float_sign | 50 | 69 | 1.38 | ok |
| float_int | 51 | 70 | 1.37 | ok |
| float_log | 52 | 73 | 1.40 | ok |
| float_root | 60 | 81 | 1.35 | ok |
| fee_base | 51 | 69 | 1.35 | ok |
| ledger_seq | 51 | 70 | 1.37 | ok |
| ledger_last_time | 51 | 70 | 1.37 | ok |
| ledger_last_hash | 52 | 71 | 1.37 | ok |
| ledger_nonce | 84 | 110 | 1.31 | ok |
| ledger_keylet | 125 | 140 | 1.12 | ok |
| hook_account | 52 | 72 | 1.38 | ok |
| hook_hash | 58 | 80 | 1.38 | ok |
| hook_param_set | 82 | 110 | 1.34 | ok |
| hook_param | 57 | 85 | 1.49 | ok |
| hook_again | 71 | 67 | 0.94 | ok |
| hook_skip | 58 | 84 | 1.45 | ok |
| hook_pos | 43 | 52 | 1.21 | ok |
| slot | 115 | 180 | 1.57 | outside 1.5x gate -> max 180 |
| slot_clear | 74 | 110 | 1.49 | ok |
| slot_count | 52 | 72 | 1.38 | ok |
| slot_set | 300 | 500 | 1.67 | outside 1.5x gate -> max 500 |
| slot_size | 81 | 140 | 1.73 | outside 1.5x gate -> max 140 |
| slot_subarray | 54 | 73 | 1.35 | ok |
| slot_subfield | 55 | 81 | 1.47 | ok |
| slot_type | 55 | 76 | 1.38 | ok |
| slot_float | 63 | 81 | 1.29 | ok |
| state_set | 635 | 990 | 1.56 | outside 1.5x gate -> max 990 |
| state_foreign_set | 5650 | 5700 | 1.01 | ok |
| state | 385 | 830 | 2.16 | outside 1.5x gate -> max 830 |
| state_foreign | 405 | 620 | 1.53 | outside 1.5x gate -> max 620 |
| trace | 225 | 270 | 1.20 | ok |
| trace_num | 83 | 220 | 2.65 | outside 1.5x gate -> max 220 |
| trace_float | 91 | 270 | 2.97 | outside 1.5x gate -> max 270 |
| otxn_burden | 56 | 86 | 1.54 | outside 1.5x gate -> max 86 |
| otxn_field | 62 | 95 | 1.53 | outside 1.5x gate -> max 95 |
| otxn_generation | 56 | 87 | 1.55 | outside 1.5x gate -> max 87 |
| otxn_id | 51 | 72 | 1.41 | ok |
| otxn_type | 51 | 70 | 1.37 | ok |
| otxn_slot | 110 | 180 | 1.64 | outside 1.5x gate -> max 180 |
| otxn_param | 66 | 120 | 1.82 | outside 1.5x gate -> max 120 |
| meta_slot | 53 | 72 | 1.36 | ok |
| xpop_slot | 4600 | 9600 | 2.09 | outside 1.5x gate -> max 9600 |
| prepare | 5400 | 12000 | 2.22 | outside 1.5x gate -> max 12000 |

27 of 75 APIs outside the 1.5x gate.

```
HOOK_API_COST(_g, 220, uint256{})  // unmeasured
HOOK_API_COST(accept, 73, uint256{})
HOOK_API_COST(rollback, 69, uint256{})
HOOK_API_COST(util_raddr, 180, uint256{})  // cross-platform max
HOOK_API_COST(util_accid, 103, uint256{})
HOOK_API_COST(util_verify, 8300, uint256{})  // cross-platform max
HOOK_API_COST(util_sha512h, 899, uint256{})
HOOK_API_COST(util_keylet, 170, uint256{})  // cross-platform max
HOOK_API_COST(sto_validate, 220, uint256{})  // cross-platform max
HOOK_API_COST(sto_subfield, 180, uint256{})  // cross-platform max
HOOK_API_COST(sto_subarray, 130, uint256{})  // cross-platform max
HOOK_API_COST(sto_emplace, 190, uint256{})  // cross-platform max
HOOK_API_COST(sto_erase, 140, uint256{})  // cross-platform max
HOOK_API_COST(etxn_burden, 58, uint256{})
HOOK_API_COST(etxn_details, 130, uint256{})
HOOK_API_COST(etxn_fee_base, 1300, uint256{})  // cross-platform max
HOOK_API_COST(etxn_reserve, 80, uint256{})
HOOK_API_COST(etxn_generation, 50, uint256{})
HOOK_API_COST(etxn_nonce, 103, uint256{})
HOOK_API_COST(emit, 2500, uint256{})  // cross-platform max
HOOK_API_COST(float_set, 68, uint256{})
HOOK_API_COST(float_multiply, 72, uint256{})
HOOK_API_COST(float_mulratio, 58, uint256{})
HOOK_API_COST(float_negate, 51, uint256{})
HOOK_API_COST(float_compare, 57, uint256{})
HOOK_API_COST(float_sum, 60, uint256{})
HOOK_API_COST(float_sto, 55, uint256{})
HOOK_API_COST(float_sto_set, 51, uint256{})
HOOK_API_COST(float_invert, 50, uint256{})
HOOK_API_COST(float_divide, 85, uint256{})  // cross-platform max
HOOK_API_COST(float_one, 43, uint256{})
HOOK_API_COST(float_mantissa, 110, uint256{})  // cross-platform max
HOOK_API_COST(float_sign, 50, uint256{})
HOOK_API_COST(float_int, 51, uint256{})
HOOK_API_COST(float_log, 52, uint256{})
HOOK_API_COST(float_root, 60, uint256{})
HOOK_API_COST(fee_base, 51, uint256{})
HOOK_API_COST(ledger_seq, 51, uint256{})
HOOK_API_COST(ledger_last_time, 51, uint256{})
HOOK_API_COST(ledger_last_hash, 52, uint256{})
HOOK_API_COST(ledger_nonce, 84, uint256{})
HOOK_API_COST(ledger_keylet, 125, uint256{})
HOOK_API_COST(hook_account, 52, uint256{})
HOOK_API_COST(hook_hash, 58, uint256{})
HOOK_API_COST(hook_param_set, 82, uint256{})
HOOK_API_COST(hook_param, 57, uint256{})
HOOK_API_COST(hook_again, 71, uint256{})
HOOK_API_COST(hook_skip, 58, uint256{})
HOOK_API_COST(hook_pos, 43, uint256{})
HOOK_API_COST(slot, 180, uint256{})  // cross-platform max
HOOK_API_COST(slot_clear, 74, uint256{})
HOOK_API_COST(slot_count, 52, uint256{})
HOOK_API_COST(slot_set, 500, uint256{})  // cross-platform max
HOOK_API_COST(slot_size, 140, uint256{})  // cross-platform max
HOOK_API_COST(slot_subarray, 54, uint256{})
HOOK_API_COST(slot_subfield, 55, uint256{})
HOOK_API_COST(slot_type, 55, uint256{})
HOOK_API_COST(slot_float, 63, uint256{})
HOOK_API_COST(state_set, 990, uint256{})  // cross-platform max
HOOK_API_COST(state_foreign_set, 5650, uint256{})
HOOK_API_COST(state, 830, uint256{})  // cross-platform max
HOOK_API_COST(state_foreign, 620, uint256{})  // cross-platform max
HOOK_API_COST(trace, 225, uint256{})
HOOK_API_COST(trace_num, 220, uint256{})  // cross-platform max
HOOK_API_COST(trace_float, 270, uint256{})  // cross-platform max
HOOK_API_COST(otxn_burden, 86, uint256{})  // cross-platform max
HOOK_API_COST(otxn_field, 95, uint256{})  // cross-platform max
HOOK_API_COST(otxn_generation, 87, uint256{})  // cross-platform max
HOOK_API_COST(otxn_id, 51, uint256{})
HOOK_API_COST(otxn_type, 51, uint256{})
HOOK_API_COST(otxn_slot, 180, uint256{})  // cross-platform max
HOOK_API_COST(otxn_param, 120, uint256{})  // cross-platform max
HOOK_API_COST(meta_slot, 53, uint256{})
HOOK_API_COST(xpop_slot, 9600, uint256{})  // cross-platform max
HOOK_API_COST(prepare, 12000, uint256{})  // cross-platform max
```
