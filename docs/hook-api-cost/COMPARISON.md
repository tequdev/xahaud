# Cross-platform comparison (DESIGN §5)

Canonical platform: Linux x86-64. Draft platform: Apple M3 Ultra (`RESULTS.md`).

## Linux x86-64 run

* Host: Ubuntu 26.04 VM, `QEMU Virtual CPU version 2.5+` (10 vCPU, 2.1 GHz, no
  SSE4/AVX/SHA extensions exposed), kvm-clock, `clock resolution 17 ns`.
* Toolchain: nix (nixpkgs weekly rev `56c02bc00adcf003215cc4bd996d6efaf4cff188`),
  gcc 13.4.0, libstdc++, cmake 4 with `CMAKE_POLICY_VERSION_MINIMUM=3.5`,
  conan 2.32, WasmEdge 0.11.2 (manylinux2014 binary), git SHA 255b32b9be.
* Procedure: `README.md` §6. 15 runs pinned to one vCPU with `taskset -c 7`.
  Five runs met the quality gate (`SE(G)/G < 15 %`, `R^2 > 0.998`, `t_call`
  gate passed): pin1, pin3, pin8, pin9, pin10. `RESULTS-linux-x86_64.md` is
  pin1 (the best fit: `t_instr` 5.60 ns, `G` 393 ns, SE 32 ns, `t_call` 304 ns);
  the comparison below uses the per-API **median over those five runs**
  because the VM's run-to-run spread is about 1.25x (worst 1.6x).
* Fit constants across the five runs: `t_instr` 4.9-6.2 ns, `G` 365-488 ns,
  `t_call` 265-304 ns. The interpreter is 1.5x slower per instruction than on
  the M3 while the host functions are not, which is why most Linux costs come
  out lower.

## Per-API comparison and merged table

Rule: the Linux value, unless the two platforms differ by more than 1.5x, in
which case the larger value is taken (`// cross-platform max`).

| API | Linux x86-64 (median) | Apple M3 Ultra | ratio | verdict |
|---|---:|---:|---:|---|
| _g | 220 | 220 | - | unmeasured |
| accept | 81 | 69 | 0.85 | ok |
| rollback | 76 | 69 | 0.91 | ok |
| util_raddr | 120 | 120 | 1.00 | ok |
| util_accid | 120 | 130 | 1.08 | ok |
| util_verify | 4500 | 6900 | 1.53 | outside 1.5x gate -> max 6900 |
| util_sha512h | 1022 | 790 | 0.77 | ok |
| util_keylet | 110 | 120 | 1.09 | ok |
| sto_validate | 130 | 200 | 1.54 | outside 1.5x gate -> max 200 |
| sto_subfield | 97 | 150 | 1.55 | outside 1.5x gate -> max 150 |
| sto_subarray | 78 | 110 | 1.41 | ok |
| sto_emplace | 100 | 170 | 1.70 | outside 1.5x gate -> max 170 |
| sto_erase | 83 | 120 | 1.45 | ok |
| etxn_burden | 66 | 96 | 1.45 | ok |
| etxn_details | 140 | 160 | 1.14 | ok |
| etxn_fee_base | 860 | 1000 | 1.16 | ok |
| etxn_reserve | 87 | 58 | 0.67 | ok |
| etxn_generation | 59 | 65 | 1.10 | ok |
| etxn_nonce | 110 | 110 | 1.00 | ok |
| emit | 1900 | 2100 | 1.11 | ok |
| float_set | 79 | 75 | 0.95 | ok |
| float_multiply | 83 | 80 | 0.96 | ok |
| float_mulratio | 68 | 75 | 1.10 | ok |
| float_negate | 60 | 65 | 1.08 | ok |
| float_compare | 66 | 72 | 1.09 | ok |
| float_sum | 69 | 89 | 1.29 | ok |
| float_sto | 64 | 89 | 1.39 | ok |
| float_sto_set | 61 | 90 | 1.48 | ok |
| float_invert | 60 | 65 | 1.08 | ok |
| float_divide | 64 | 76 | 1.19 | ok |
| float_one | 51 | 53 | 1.04 | ok |
| float_mantissa | 60 | 87 | 1.45 | ok |
| float_sign | 60 | 66 | 1.10 | ok |
| float_int | 60 | 66 | 1.10 | ok |
| float_log | 62 | 68 | 1.10 | ok |
| float_root | 70 | 94 | 1.34 | ok |
| fee_base | 60 | 71 | 1.18 | ok |
| ledger_seq | 62 | 70 | 1.13 | ok |
| ledger_last_time | 60 | 65 | 1.08 | ok |
| ledger_last_hash | 61 | 67 | 1.10 | ok |
| ledger_nonce | 95 | 97 | 1.02 | ok |
| ledger_keylet | 140 | 120 | 0.86 | ok |
| hook_account | 61 | 68 | 1.11 | ok |
| hook_hash | 68 | 75 | 1.10 | ok |
| hook_param_set | 92 | 93 | 1.01 | ok |
| hook_param | 67 | 79 | 1.18 | ok |
| hook_again | 81 | 64 | 0.79 | ok |
| hook_skip | 69 | 76 | 1.10 | ok |
| hook_pos | 51 | 51 | 1.00 | ok |
| slot | 120 | 150 | 1.25 | ok |
| slot_clear | 84 | 97 | 1.15 | ok |
| slot_count | 62 | 67 | 1.08 | ok |
| slot_set | 330 | 400 | 1.21 | ok |
| slot_size | 93 | 150 | 1.61 | outside 1.5x gate -> max 150 |
| slot_subarray | 64 | 68 | 1.06 | ok |
| slot_subfield | 65 | 73 | 1.12 | ok |
| slot_type | 65 | 71 | 1.09 | ok |
| slot_float | 73 | 75 | 1.03 | ok |
| state_set | 680 | 830 | 1.22 | ok |
| state_foreign_set | 6300 | 4100 | 0.65 | outside 1.5x gate -> max 6300 |
| state | 430 | 490 | 1.14 | ok |
| state_foreign | 450 | 500 | 1.11 | ok |
| trace | 250 | 270 | 1.08 | ok |
| trace_num | 95 | 190 | 2.00 | outside 1.5x gate -> max 190 |
| trace_float | 110 | 210 | 1.91 | outside 1.5x gate -> max 210 |
| otxn_burden | 66 | 77 | 1.17 | ok |
| otxn_field | 72 | 84 | 1.17 | ok |
| otxn_generation | 67 | 78 | 1.16 | ok |
| otxn_id | 61 | 67 | 1.10 | ok |
| otxn_type | 60 | 71 | 1.18 | ok |
| otxn_slot | 120 | 150 | 1.25 | ok |
| otxn_param | 77 | 98 | 1.27 | ok |
| meta_slot | 62 | 67 | 1.08 | ok |
| xpop_slot | 5400 | 9200 | 1.70 | outside 1.5x gate -> max 9200 |
| prepare | 6000 | 9500 | 1.58 | outside 1.5x gate -> max 9500 |

10 of 75 APIs outside the 1.5x gate.

```
HOOK_API_COST(_g, 220, uint256{})  // unmeasured
HOOK_API_COST(accept, 81, uint256{})
HOOK_API_COST(rollback, 76, uint256{})
HOOK_API_COST(util_raddr, 120, uint256{})
HOOK_API_COST(util_accid, 120, uint256{})
HOOK_API_COST(util_verify, 6900, uint256{})  // cross-platform max
HOOK_API_COST(util_sha512h, 1022, uint256{})
HOOK_API_COST(util_keylet, 110, uint256{})
HOOK_API_COST(sto_validate, 200, uint256{})  // cross-platform max
HOOK_API_COST(sto_subfield, 150, uint256{})  // cross-platform max
HOOK_API_COST(sto_subarray, 78, uint256{})
HOOK_API_COST(sto_emplace, 170, uint256{})  // cross-platform max
HOOK_API_COST(sto_erase, 83, uint256{})
HOOK_API_COST(etxn_burden, 66, uint256{})
HOOK_API_COST(etxn_details, 140, uint256{})
HOOK_API_COST(etxn_fee_base, 860, uint256{})
HOOK_API_COST(etxn_reserve, 87, uint256{})
HOOK_API_COST(etxn_generation, 59, uint256{})
HOOK_API_COST(etxn_nonce, 110, uint256{})
HOOK_API_COST(emit, 1900, uint256{})
HOOK_API_COST(float_set, 79, uint256{})
HOOK_API_COST(float_multiply, 83, uint256{})
HOOK_API_COST(float_mulratio, 68, uint256{})
HOOK_API_COST(float_negate, 60, uint256{})
HOOK_API_COST(float_compare, 66, uint256{})
HOOK_API_COST(float_sum, 69, uint256{})
HOOK_API_COST(float_sto, 64, uint256{})
HOOK_API_COST(float_sto_set, 61, uint256{})
HOOK_API_COST(float_invert, 60, uint256{})
HOOK_API_COST(float_divide, 64, uint256{})
HOOK_API_COST(float_one, 51, uint256{})
HOOK_API_COST(float_mantissa, 60, uint256{})
HOOK_API_COST(float_sign, 60, uint256{})
HOOK_API_COST(float_int, 60, uint256{})
HOOK_API_COST(float_log, 62, uint256{})
HOOK_API_COST(float_root, 70, uint256{})
HOOK_API_COST(fee_base, 60, uint256{})
HOOK_API_COST(ledger_seq, 62, uint256{})
HOOK_API_COST(ledger_last_time, 60, uint256{})
HOOK_API_COST(ledger_last_hash, 61, uint256{})
HOOK_API_COST(ledger_nonce, 95, uint256{})
HOOK_API_COST(ledger_keylet, 140, uint256{})
HOOK_API_COST(hook_account, 61, uint256{})
HOOK_API_COST(hook_hash, 68, uint256{})
HOOK_API_COST(hook_param_set, 92, uint256{})
HOOK_API_COST(hook_param, 67, uint256{})
HOOK_API_COST(hook_again, 81, uint256{})
HOOK_API_COST(hook_skip, 69, uint256{})
HOOK_API_COST(hook_pos, 51, uint256{})
HOOK_API_COST(slot, 120, uint256{})
HOOK_API_COST(slot_clear, 84, uint256{})
HOOK_API_COST(slot_count, 62, uint256{})
HOOK_API_COST(slot_set, 330, uint256{})
HOOK_API_COST(slot_size, 150, uint256{})  // cross-platform max
HOOK_API_COST(slot_subarray, 64, uint256{})
HOOK_API_COST(slot_subfield, 65, uint256{})
HOOK_API_COST(slot_type, 65, uint256{})
HOOK_API_COST(slot_float, 73, uint256{})
HOOK_API_COST(state_set, 680, uint256{})
HOOK_API_COST(state_foreign_set, 6300, uint256{})
HOOK_API_COST(state, 430, uint256{})
HOOK_API_COST(state_foreign, 450, uint256{})
HOOK_API_COST(trace, 250, uint256{})
HOOK_API_COST(trace_num, 190, uint256{})  // cross-platform max
HOOK_API_COST(trace_float, 210, uint256{})  // cross-platform max
HOOK_API_COST(otxn_burden, 66, uint256{})
HOOK_API_COST(otxn_field, 72, uint256{})
HOOK_API_COST(otxn_generation, 67, uint256{})
HOOK_API_COST(otxn_id, 61, uint256{})
HOOK_API_COST(otxn_type, 60, uint256{})
HOOK_API_COST(otxn_slot, 120, uint256{})
HOOK_API_COST(otxn_param, 77, uint256{})
HOOK_API_COST(meta_slot, 62, uint256{})
HOOK_API_COST(xpop_slot, 9200, uint256{})  // cross-platform max
HOOK_API_COST(prepare, 9500, uint256{})  // cross-platform max
```
