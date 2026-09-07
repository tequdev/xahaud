# HookAPICost results

## Header

* CPU: QEMU Virtual CPU version 2.5+
* OS: Linux tequ-ubuntu-general 7.0.0-31-generic #31-Ubuntu SMP PREEMPT_DYNAMIC Sat Aug  1 04:26:38 UTC 2026 x86_64 GNU/Linux
* Compiler: 13.4.0
* Build type: Release (hook_cost_bench=ON)
* WasmEdge: 0.11.2
* git SHA: 5c942671dd879115f90273a90734c52356549131
* t_clk (mean nowNs() pair overhead): 19 ns
* clock resolution (smallest non-zero delta, review #4): 17 ns
* hookcost_sha256:
  * accept0: 5bebf48de6b134c278de84ba7aa5b558f7938cb998228f10e9485c4c5c00df56
  * base1: ed79806cbf4a45d7f89e0b687a69b9e04c355ee9fd688da9e48762eb073bb40d
  * base16: 18b62720e2ba612a20f27bba931d5c56bc80e1cd9bd39c2426cf3a53ca6ee473
  * base2: 6ed65c96351aa1f3b3f995ac11f2fb80caf297d2271614cefbca0f9ab2aafd57
  * base4: f1ecbf9487ef94e7baf3d5813be3c0de070555871fc4fb45917c53015c37d390
  * base64: 053aff2e1f608ff44934f7840c7ea9fc925542d0ee23c74e87f8a5cb1c5a1358
  * base8: 756df872ec57f5213dc6f862eb45ca6eb653f9252b3c0c39eff5218e68383293
  * basei64: 6243f92971fa163ba240b5efaa7671c9f576ceb29925c3bd1f7a626f2e5f0c4f
  * basemem: c1172ff6e40b53411bcc9390992c31ec5ce5ced8250fb662bb68c5025c0b81d7
  * emit_1k_k200: f8a69ea4a961bd6fc5558c3b48f2fb84056786357d3ce307692987fe24e2b9b6
  * emit_min_k200: f5ed2f5bc7089226159a2897a7f7800eacbc0337424bbf58a49f5c32d23bf945
  * etxn_burden: 89f81c8d3ec234bee70abbc5143fde3734b48c6856774117b4f9d47f5813fd61
  * etxn_fee_base_1k: e256f3d736cca07556bae53b841246c61c8a28db4f28877d73307b06ae01edfe
  * etxn_generation: 0b554dbe24b8d092c8845ed7c4a04db1b67fcd32a39037d3ad76fd45f8d7d264
  * etxn_nonce_k200: c113ab10f084cb3675731b21095d3cacf5d3a935f136d0f1305cc19badf8bb8b
  * etxn_reserve_once: 7da965de7e4ec900644d84ebe1db01bc956d4f2ec0737365480f6efb8ae4b3c0
  * fee_base: 7a00e6d54bb2a4c4160b0ca45ba1984b98fd6786d81b8602217eecfaf3acd562
  * float_compare: 791d4c5786200769aa8f55b532c4e3549280deb917e295f77da08224bac95e6d
  * float_compare_le: e38bfe9cf7f7ac2651d9092cd686924e63c9d2b84d4855d1bf71db21127fe384
  * float_divide: 4b08485a9e690572deaa00751464f4345247facade161c5d7a9672159c2ea403
  * float_int: b74a00c316ac30d0a3621ae3a0b9d81321f5eb3c0055ce29720eceb5f03673b2
  * float_invert: 286259b82bcfde5fa3b08be3fa441511b93706d6656fa4766949d11e54582705
  * float_log: cacea7cecde30d89bc058cd3cffb7d6d27464983c3819b03768a6155d6f0be90
  * float_mantissa: 6a7e3bf417b4571c3911c3c87afc401669a141eb38c615798e1f1ae4183f3cf2
  * float_mulratio: d1e0d8757fdcc701cc10ba57961235844c74761a542146ad58b9de302d20c7cc
  * float_multiply: 74ba7f8fe1c6e0339ea9077c5608c90230ead9379511026cf5961f380297ad23
  * float_negate: 732fede51581a7b4c93e9d1431872f9a0f216f93a485d6e904f296dd1ab9defb
  * float_one: 62341ceb6e1ef84b09f9e2be29def8492aaae0211e22fa50de9c41a53ef342ae
  * float_root: 3f8e5116430dbd4f30854b5f438b5e0b3b558a94e2f6c49e6c35dadf760b3cb4
  * float_set: 55c950336ecc3bc19a36ed948d59217eebb090b8f4d0f62783eeaf187d6276a3
  * float_sign: 7ed88fe3f6b8271fefca2fd23ecdd93c475bb986acb294dfa06c469ab56a9f7c
  * float_sto_iou: b6bd6902a74f8ed2da6428099d8effd07b8c453d7b610c3a379f823bd0679597
  * float_sto_set: 191f9b817eaf4ef76d57683ca9c409a2d6d9b0910d335d1f38c666387ff63823
  * float_sto_short: fb471c329f8dc03db0a96f74dc573908e45c463526783e76e41e5f319fb8c795
  * float_sto_xrp: 829a0916a87823e6a22822ea239722fe83f8acf16f62964c3060342165290288
  * float_sum: 9f6d6344bc75cc259a272cc9a36a56d54b4ef1fa65afd23e858e024ef3a0a2e3
  * hook_account_api: 24801bc5f7cbb95fa294bd4e4761df2f7390d09ace0e391695dbce4df6090bee
  * hook_again_once: 98a1de5e6dc1ba962dc4aac7ead66f04a2004f763203c8d7613c149871f24f3a
  * hook_hash_0: 2e6c5384f638c928f10d33f1a6c3e6af1cfbecdc1d1976132c399908ebc507a3
  * hook_hash_neg1: 2e1a4fb004851299b6385f06afbf19e4051abfa37570bd33055d956ce91786b7
  * hook_param_256: 754949d858b108f51239e707ae32554311042b7798d0acb194765e73ff0db25a
  * hook_param_32: 3e76f8304dc6b5442ba4d844a11da92ee2c4be94cf54f4f88460c5f2f330e127
  * hook_param_set_k16: a3a175944dd6d758369b752ec7cc6e60b14e743186ee9fb6a946cf26ca140c9c
  * hook_pos: 4812b2f59016a36e5d087404bce152beae4742689176e9044d646295785e342f
  * hook_pos_k16: 6352bda9a21f076b9522601ce1acc1e1c4bd0db7b5068691bcf7073541cd0be7
  * hook_skip_alt: f0e2da8e85ba8ad1bebaa306200ccafd070034c4bbdaf974801fe09f4b9a6d57
  * ledger_keylet: a5953640a733de61feb792c60cb435da687978f9ae4dcfa8efc0404696b3a32e
  * ledger_last_hash: c90d4b4dbb1275ebb59afcd82772bb7fbc685b3edbfef291ee3b6ed8ab4ee049
  * ledger_last_time: a197cc5ca1ae4d6d4fd405d6f8673ab1de35dd58bfc7cfe161eecdc30bf58153
  * ledger_nonce_k200: 66b04a296aa49177283cae6fa86e077db7734ce0376dafaedf473a5739bb8043
  * ledger_seq: 18aae2457e6248ced17c00f2356ef6c152463801e8a0a3d1b7a7f55dcb9ec801
  * meta_slot_k200: 42a32849abb16681d2022e12a874ff43e1a1589c664e34edd60ad010aaddfe70
  * noexit: 4d861762c484692e5686da23dc63c4a4444d66b14ba6250bd29f769236cf5cef
  * otxn_burden: f726beae37bc1e694095271512c907dcd599f5373136a85362dcfd6b99312969
  * otxn_field_16k: cd653649e2270e019ba637a9b92fad68dbaebc8a88c94af28cc11b8311cf43c2
  * otxn_field_1k: 9b82a1cdfa9631322eb054e8f614463298c6c591f470a8cdc7b515a3a64021ce
  * otxn_field_acc: b12faf93f234be5dd4a183a1e9f79e678836d07fc5486ad4953b60fbe1abb310
  * otxn_generation: af3b04b4c676d18c2c29add3c05e6d24ee322eb6c09b4b12c06db02d061efa22
  * otxn_id_0: 833045a6956e2feed142076020ae756f02eafb106f91f50e05c159274c166a26
  * otxn_id_1: e4ab9afa42abb20f12dc2973cc84f053543cf3c2ab6fb325dfab63e391dcf101
  * otxn_param_256: 22911c572ac8817817d4e733cd545de2fc1dee1349120576e6c6c74949b11dc0
  * otxn_param_32: 188b2a1a3508adb452158ce30a83e628817520a49bd3c86a1ad66d74df6be6bb
  * otxn_slot_16k: 6738e6401303ecbc14d54a8ef8797c2ad6afc77b5caaae7d6d2580007f40e958
  * otxn_slot_1k: 970f29c6052a700e91fa3ba5e55d4c495f01bd8b5bf233210d4567d6a1992155
  * otxn_slot_small: 3bbe585b53a4590a8d5709258fcd3956fc29ee0e0f8f955c29b6be3649c173a3
  * otxn_type: 0f57480494ab61dadd5743de16cd5065a4b47c3e72ec497c8a1f7bf75249b4de
  * prepare_1k: 6662c84304630a91ffae3bf26e3c9c8660c3eb802327067d5ed5a157cce62ffe
  * prepare_min: f7572fdca3a2e8d8c066155d83fb798c048e944789f1e0b9925f2aa983d43f4f
  * rollback0: 2e999489f98a7cdb4306d0767a4a6727ee73ec025717a471aff06e41ba2b3965
  * slot_16k: 9b4f27df25418aa8993d8048be1195da6cf20b3a773eb0ff4c5847c3993d33fb
  * slot_1k: e32c0ca3dc0eacc4e9a851540f053a250e952f13fc5ba37ea24e4569fb02cdc5
  * slot_clear: 8a83a7e57dac20935d18cd92800010133b0279175d1d9cb0a264539be6d51cb3
  * slot_count: d7d7faab581bd26ff6838f553fff10eeef96a619ea0bda455eed93950b47e8cc
  * slot_float: d19bfd2ff9887704bbc429e2ef84d6d7bd11e322347cb2be7b693ca1ff983c0b
  * slot_set_34: 9cbbd919a913ec4f9bb728bd9e18b87da453069ac0bed67236a4024b72299acd
  * slot_size: 9f800177cc88a72c289f9c15c14ae2bd1b068c5010e93f8e5dffbdd3d260b0be
  * slot_subarray: 7253e8880aee00b2b7c4636e7949cd8c1907e781d5683b4e22820f82d0e2a976
  * slot_subfield: 09b247ddb67a48ddb9082094c525f00104d621ec7baff3e9ae83a6de56214e47
  * slot_type_0: 219ab2c902e9b0849d41c0bcf930e327dda682b69f1c0abe384c1ca5142268ec
  * slot_type_1: e1cd0827b52d83a9e4d8bf1fd815f8c84c6efdd98d3f092570f98d3ce1da3f34
  * state_foreign_r_256: bc00bffbfd69733408d9f8860d861e6d68fcc68b984055d24f035e558a8cda31
  * state_foreign_r_32: b08a259837e4ffbe6ff4ce4cdfc4a6524be153fb501916e0c38479eed6d4b52e
  * state_foreign_w: f2763b3241d51d51e558503bdbd476a4e575d3120de888584e0040fb8eb2a0e9
  * state_r_256: 71df9ff2bf907c97e7383b78cb2403d119323ee456bbf7b65d70dc10ad12bad4
  * state_r_32: 4b869cb680585e3a675549282e8681d057aea35a34be2263750d458fdd3aeb8b
  * state_r_4k: 17275cb727c3321a0b4a22ea8fe273798c62569c1507d07afd7e59d6bf0819a2
  * state_w_256: de2450afee2c567d42f98e0abf6b0b5864a8ae1aa9d68e1825b5c759d47925a1
  * state_w_32: 447607d5043f1af946660dafac24854cb4a35874232115c9679b162106735d3b
  * state_w_4k: fd6068df4469446546d53f3e3fc2721b8b02822682da3ff3ee5502eaa2c8ed74
  * state_w_create_32: b40ad464e7cc426958f10a599fe5956433f8f5639f5b1e22bdc57c67ac7a67c1
  * state_w_setup_256: 24220a7ea84e6b5580c90c5630132311438fd138be0038741209b74c0af71f51
  * state_w_setup_32: 55e9e7644da8d41a6b5d9aba2327f3a19376dfaac1f1637c5d90b315e76d7be5
  * state_w_setup_4k: 4f22f380bd200d33b8cd21172fc00ce4779cbad015a522cdea890b7431f5c4b6
  * sto_emplace_small: f8fc315d7cae955852cccaec1b8dc99acda9d604c082b277c5004bb4d847b4c8
  * sto_emplace_tx: 09d939d239724980d21bca20e7e36c3daa3e0a968d6af247f089a407312424e5
  * sto_erase_small: 64161686a68ab1a5b44cc0c8d79b9c1b049c18a8b16d93263d8f97e51edcfd2d
  * sto_erase_tx: 72734f41cde76101026646350cef5e6bd922804e1be3aae99acc60a0cf337c4f
  * sto_subarray_tx: 0a98000c0c8229d924f7675077a48ac37959f8438361ddf9cd1030d6c9e86356
  * sto_subfield_small: 10ad60171505f6a561436e988305119f1fea40aef21a26b1b68ebafc0f678a8c
  * sto_subfield_tx: fb24d142587803d15b85a5c9ae0031eb791c0d3ff41facdafe432484b52e0639
  * sto_validate_small: 03295c9deaeafcc16e3599a7b3c4c12212873dd29d3477de116e61afb12d98d4
  * sto_validate_tx: 68610087a379bfc4098c23af178a0d41f22783682e8774f54a9c9c6e81755cb5
  * trace_1k_hex: 81b1328cbec896fe06ce2ed6b9fd42832ea7cceb9640abb963aaf0597b8ab941
  * trace_32: 1fd02c25c30dbba7a64df15486c5207725e196be3fba64cc0eb2ad902d013b54
  * trace_float: 1bf0f84ddba299172b18ca6760b469b484b5f6f4fc9c260247a2414c230657e3
  * trace_num: 8ad86b6800322331124b99e81706a6661251ea34d349fb7f0ce1b4cec345a281
  * util_accid: ac234ae81fb7fc89fd955e00b68d38f0439896fa323946f3360fd1ac005cd178
  * util_keylet_account: 598b90e85e6eda7487a49c85a5678bedbddc7ba18086e24cb24347102aa959d9
  * util_keylet_amendments: 68da912bb04eb1830ce4575dbd35840375e838eb812f01a665e2c3e58986cace
  * util_keylet_amm: 06cf403a559f52745e5991edff63422741c4306d347c003005db4423c52c9616
  * util_keylet_check: 33cbb06069540a531b8dcbeac99e21fe591dab9e7a3d47929cf7d91999e6c10e
  * util_keylet_child: b94b6622995b1579f83a8a9182fd61d3d3771cd9c86e9015562e43351726a58c
  * util_keylet_cron: 699bb0a6f7f362eb697c09f7b5488859d69f67ba49cb7f56724fc80a84e41996
  * util_keylet_deposit_preauth: e497951d707d07c8e40c9578931cb1b1ba67b745944a2c5921e9ae3324406532
  * util_keylet_did: 729a120d188ea5e0ed8ac96b5daf0bc6d9fe1566e00b0fbb121d53b61c51f529
  * util_keylet_emitted_txn: 4f7a55422b3b3f3e0264790e378311ead05507491e385d03a2881909bb5ad5f1
  * util_keylet_escrow: 4fccd2d3ce8a30c84fc1f3a88443aef9cbb8ba00569b311448652fc7102bfa92
  * util_keylet_hook: 312220ce3dfaa13c80a076b7d514062d21428160c2730099d9a64927fcbc090e
  * util_keylet_hook_definition: 316292f49291fbc965e20517fa84d075d0e344d258a5a15764d1254c7f8802ec
  * util_keylet_hook_state: 086a21332c7bcef05fccd1bd64880d3a6dd216c8da4292faff0a17e01aee7c2f
  * util_keylet_hook_state_dir: 8ab51852c71a786e469f745bba58cff811ccc0fbd16124d180e4832f4cf935fc
  * util_keylet_line: 20a143ab8996da8cf925e8b5b1eee3eeb9ec337048190abd25c254540267e197
  * util_keylet_nft_offer: b93f5d2619c7c83fbd0e5ef05c5a6acaef2284517c5b463de0ca8627727808f7
  * util_keylet_offer: 0e24cfa1bd8d315afa3c49fcbdc75ec1652f02892e87584192d7b14e168d5458
  * util_keylet_oracle: 9fb175756320a283562100e03598a41d7884d1af2951217cf84ff59b3a806b4e
  * util_keylet_owner_dir: d3406d5dcedcc9b96e25f1174b31c89c4217547b500b8d05b457a7c293fb1102
  * util_keylet_page: d38d540b1a3eeb42f61628dc8705cbcd4a4bf6f79c47431dc61fbef2587783e8
  * util_keylet_paychan: d582fb857b0ef6c356ed3c6b9133fcfe0d46a4487628172048e29561cda4c2a9
  * util_keylet_quality: f9b0c095a60e6cebe8603d67670c2d79970ad0b7aa502030a64cfdaf941d88a8
  * util_keylet_signers: e2ac9dd207465b2e8c5a61540eed3f1ec69ea155481eecc8ad07adac3c23cdda
  * util_keylet_skip: f77fe5df649d9dd5145e243e717d124470762b0f2a2e3284c1dc4f27e2845d18
  * util_keylet_unchecked: 8cb74f1d0b75359a0f3a31ba5f5b0586fe707dd4d188f18578a8b7e6b4a2c63b
  * util_raddr: 1a6302ab5f1d6af47e81d095ab6ef160ff0416b1f8051ede21cc542e98d148c5
  * util_sha512h_16k: 3a78c488745364d112441b382595d0d8e92563fb235f03accdea9c2ba1de6071
  * util_sha512h_1k: 1a2ec88f1d1b943efb0858cbf080f78f31be3b54d6f08d57cee94a4945021cbe
  * util_sha512h_32: 133fcaaec67d290b5da355597b0ab0c430a01ca1c87fa12a0aeffffd3a428c2e
  * util_verify_ed25519: 4d5d2a6a9ba98ce0a4846d4f857b6786276814301be68581b8add3876d39e260
  * util_verify_secp256k1: f9ca8c63aa32aa23f07baceac0cb755dc5e3d732a941837ee29c14308268bac8
  * xpop_slot_k100: 446195430687fc37dda861aee428ae52da45a0994e190429d5e9bc1b202e0d48

## Baseline fit

| baseline | N1 | N2 | I(N1) | I(N2) | dI | dTw env.close (ns) | dTw exec.ns (ns) | static/iter | static/runtime ratio |
|---|---|---|---|---|---|---|---|---|---|
| base1 | 130 | 1300 | 4625 | 45575 | 35 | 527.701 | 534.417 | 43.0377 | 5.52873 |
| base2 | 70 | 700 | 3855 | 37875 | 54 | 655.97 | 648.037 | 62.0699 | 3.94696 |
| base4 | 40 | 400 | 4075 | 40075 | 100 | 910.583 | 881.975 | 108.122 | 2.60354 |
| base8 | 25 | 250 | 4775 | 47075 | 188 | 1406.08 | 1373.15 | 196.195 | 1.86352 |
| base16 | 5 | 50 | 1895 | 18275 | 364 | 2346.67 | 2353.22 | 372.961 | 1.50484 |
| base64 | 3 | 38 | 4335 | 54035 | 1420 | 8243.17 | 8389.06 | 1429.26 | 1.1552 |

Fitted (env.close() wall-clock, calibration channel): t_instr = 5.5589 ns, G (_g total per-iteration cost) = 346.232 ns, SE(G) = 8.39571 ns, R^2 = 0.999975
Fitted (exec.ns, wasm-window only, comparison): t_instr = 5.6772 ns, G = 318.571 ns, SE(G) = 11.6164 ns, R^2 = 0.999954

### Sensitivity baselines (t_instr alone, using G)

| baseline | dI | dTw env.close (ns) | t_instr alone (ns) |
|---|---|---|---|
| basei64 | 194 | 1478.08 | 5.83425 |
| basemem | 118 | 1028.49 | 5.78184 |

* t_instr = 5.5589 ns
* G (loop-head _g total per-iteration cost) = 346.232 ns
* R^2 (baseline fit) = 0.999975
* t_call (0-arg boundary, from E2E(hook_pos) - (M_pos - 2*t_clk)) = 283.582 ns
* O_g (the `_g` 2-arg call's own G above) = 346.232 ns vs t_call (0-arg hook_pos) = 283.582 ns -- host-call boundary grows roughly 31.3252 ns per argument

## Per-API results

| api | variant | K | calls | ns/call (M) | E2E (ns) | HF (ns) | used | cost (proposed) | cost (current) | notes |
|---|---|---|---|---|---|---|---|---|---|---|
| hook_pos | K=4 | 4 | 3400 | 19.0938 | 264.675787 | 264.676 | HF | 48 | 40 | HF (E2E noisy) |
| fee_base | K=4 | 4 | 1800 | 69.4694 | 311.079537 | 315.051 | HF | 57 | 70 | HF (E2E noisy) |
| ledger_seq | K=4 | 4 | 1800 | 69.2728 | 329.901759 | 314.855 | HF | 57 | 140 | HF (E2E noisy) |
| float_one | K=4 | 4 | 1800 | 19.1267 | 273.295525 | 264.709 | HF | 48 | 20 | HF (E2E noisy) |
| otxn_type | K=4 | 4 | 1800 | 68.785 | 329.665339 | 314.367 | HF | 57 | 130 | HF (E2E noisy) |
| etxn_generation | K=4 | 4 | 1800 | 63.7889 | 303.027007 | 309.371 | HF | 56 | 130 | HF (E2E noisy) |
| util_sha512h | 32B | 1 | 1000 | 246.871 | 520.609492 | 492.453 | HF | 89 | 340 | HF (E2E noisy) |
| util_sha512h | 1KiB | 1 | 1000 | 1386.36 | 1654.169492 | 1631.94 | E2E | 300 | 340 |  |
| util_sha512h | 16KiB | 1 | 1000 | 17845.8 | 18710.527269 | 18091.3 | E2E | 3400 | 340 |  |
| state | 32B | 1 | 200 | 1989.44 | 2766.598256 | 2235.02 | HF | 410 | 1700 | HF (E2E noisy) |
| state | 256B | 1 | 200 | 2067.66 | 2524.726034 | 2313.24 | HF | 420 | 1700 | HF (E2E noisy) |
| state_set | 32B, modify (fixed keys) | 1 | 200 | 679.33 | 7623.767136 | 3504.52 | HF | 640 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.175409; review #6: modify path |
| state_set | 32B, create (fresh keys, salt=rep) | 1 | 200 | 669.81 | 26396.063749 | 2869.72 | HF | 520 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 9.198126; review #6: create path |
| state_set | 256B | 1 | 200 | 731.885 | 8802.544913 | 3726.61 | HF | 680 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.362080 |
| util_raddr | K=4 | 4 | 1200 | 390.48 | 686.609378 | 636.062 | HF | 120 | 980 | HF (E2E noisy) |
| util_accid | K=4 | 4 | 1200 | 365.779 | 625.445489 | 611.361 | HF | 110 | 690 | HF (E2E noisy) |
| util_keylet | ACCOUNT | 4 | 1200 | 247.799 | 519.406555 | 493.381 | HF | 89 | 230 | HF (E2E noisy) |
| util_keylet | CHILD | 4 | 1200 | 80.2717 | 407.090815 | 325.854 | HF | 59 | 230 | HF (E2E noisy) |
| util_keylet | ESCROW | 4 | 1200 | 257.827 | 538.560259 | 503.409 | HF | 91 | 230 | HF (E2E noisy) |
| util_keylet | LINE | 4 | 1200 | 260.144 | 544.920444 | 505.726 | HF | 91 | 230 | HF (E2E noisy) |
| util_keylet | AMENDMENTS | 4 | 1200 | 78.6733 | 367.276000 | 324.255 | HF | 59 | 230 | HF (E2E noisy) |
| util_keylet | QUALITY | 4 | 1200 | 83.3017 | 364.427852 | 328.884 | HF | 60 | 230 | HF (E2E noisy); AMENDMENTS's case also covers FEES/NEGATIVE_UNL/EMITTED_DIR (identical switch case); AMM/BRIDGE/XCHAIN_*/MPTOKEN_*/CREDENTIAL/PERMISSIONED_DOMAIN not built (complex multi-part operands -- asset pairs, bridge specs); every other keylet_type is covered below |
| util_keylet | HOOK | 4 | 1200 | 247.657 | 537.235259 | 493.239 | HF | 89 | 230 | HF (E2E noisy) |
| util_keylet | HOOK_STATE | 4 | 1200 | 255.778 | 531.566741 | 501.359 | HF | 91 | 230 | HF (E2E noisy) |
| util_keylet | SKIP | 4 | 1200 | 86.1725 | 391.699148 | 331.754 | HF | 60 | 230 | HF (E2E noisy) |
| util_keylet | OFFER | 4 | 1200 | 259.97 | 491.716741 | 505.552 | HF | 91 | 230 | HF (E2E noisy) |
| util_keylet | SIGNERS | 4 | 1200 | 253.178 | 538.741741 | 498.76 | HF | 90 | 230 | HF (E2E noisy) |
| util_keylet | CHECK | 4 | 1200 | 258.424 | 552.513963 | 504.006 | HF | 91 | 230 | HF (E2E noisy) |
| util_keylet | DEPOSIT_PREAUTH | 4 | 1200 | 253.261 | 532.001926 | 498.843 | HF | 90 | 230 | HF (E2E noisy) |
| util_keylet | UNCHECKED | 4 | 1200 | 79.9 | 360.183407 | 325.482 | HF | 59 | 230 | HF (E2E noisy) |
| util_keylet | OWNER_DIR | 4 | 1200 | 248.587 | 545.488963 | 494.169 | HF | 89 | 230 | HF (E2E noisy) |
| util_keylet | PAGE | 4 | 1200 | 251.333 | 536.732481 | 496.914 | HF | 90 | 230 | HF (E2E noisy) |
| util_keylet | PAYCHAN | 4 | 1200 | 262.788 | 518.952852 | 508.369 | HF | 92 | 230 | HF (E2E noisy) |
| util_keylet | EMITTED_TXN | 4 | 1200 | 246.603 | 508.224148 | 492.185 | HF | 89 | 230 | HF (E2E noisy) |
| util_keylet | NFT_OFFER | 4 | 1200 | 259.46 | 497.456555 | 505.042 | HF | 91 | 230 | HF (E2E noisy) |
| util_keylet | HOOK_DEFINITION | 4 | 1200 | 248.179 | 505.122296 | 493.761 | HF | 89 | 230 | HF (E2E noisy) |
| util_keylet | HOOK_STATE_DIR | 4 | 1200 | 270.246 | 511.602852 | 515.828 | HF | 93 | 230 | HF (E2E noisy) |
| util_keylet | CRON | 4 | 1200 | 309.124 | 600.322296 | 554.706 | HF | 100 | 230 | HF (E2E noisy) |
| util_keylet | ORACLE | 4 | 1200 | 283.041 | 537.245444 | 528.623 | HF | 96 | 230 | HF (E2E noisy) |
| etxn_burden | K=4 | 4 | 1200 | 107.058 | 349.940339 | 352.64 | HF | 64 | 260 | HF (E2E noisy) |
| otxn_burden | K=4 | 4 | 1200 | 108.007 | 362.571142 | 353.589 | HF | 64 | 260 | HF (E2E noisy) |
| otxn_generation | K=4 | 4 | 1200 | 104.595 | 351.015587 | 350.177 | HF | 63 | 280 | HF (E2E noisy) |
| ledger_last_time | K=4 | 4 | 1200 | 69.435 | 336.220895 | 315.017 | HF | 57 | 110 | HF (E2E noisy) |
| ledger_last_hash | K=4 | 4 | 1200 | 75.305 | 312.444766 | 320.887 | HF | 58 | 210 | HF (E2E noisy) |
| hook_account | K=4 | 4 | 1200 | 74.3033 | 329.914210 | 319.885 | HF | 58 | 140 | HF (E2E noisy) |
| hook_hash | hook_no=0 | 4 | 1200 | 111.823 | 382.599757 | 357.405 | HF | 65 | 340 | HF (E2E noisy) |
| hook_hash | hook_no=-1 | 4 | 1200 | 74.8692 | 339.676609 | 320.451 | HF | 58 | 340 | HF (E2E noisy) |
| otxn_id | flags=0 | 4 | 1200 | 74.1192 | 312.701609 | 319.701 | HF | 58 | 450 | HF (E2E noisy) |
| otxn_id | flags=1 | 4 | 1200 | 74.5525 | 319.319201 | 320.134 | HF | 58 | 450 | HF (E2E noisy) |
| float_multiply | K=4 | 4 | 1200 | 197.374 | 415.107051 | 442.956 | HF | 80 | 240 | HF (E2E noisy) |
| float_mulratio | K=4 | 4 | 1200 | 110.477 | 372.234625 | 356.059 | HF | 65 | 390 | HF (E2E noisy) |
| float_negate | K=4 | 4 | 1200 | 68.8433 | 317.335393 | 314.425 | HF | 57 | 160 | HF (E2E noisy) |
| float_compare | COMPARE_EQUAL | 4 | 1200 | 104.787 | 390.312720 | 350.369 | HF | 64 | 140 | HF (E2E noisy) |
| float_compare | COMPARE_LESS|COMPARE_EQUAL | 4 | 1200 | 104.588 | 351.252535 | 350.17 | HF | 63 | 140 | HF (E2E noisy) |
| float_sum | K=4 | 4 | 1200 | 118.357 | 397.801495 | 363.939 | HF | 66 | 350 | HF (E2E noisy) |
| float_invert | K=4 | 4 | 1200 | 69.0092 | 345.324282 | 314.591 | HF | 57 | 230 | HF (E2E noisy) |
| float_divide | K=4 | 4 | 1200 | 92.1217 | 334.273717 | 337.704 | HF | 61 | 280 | HF (E2E noisy) |
| float_mantissa | K=4 | 4 | 1200 | 69.2267 | 329.334467 | 314.809 | HF | 57 | 170 | HF (E2E noisy) |
| float_sign | K=4 | 4 | 1200 | 69.3142 | 325.237245 | 314.896 | HF | 57 | 80 | HF (E2E noisy) |
| float_int | K=4 | 4 | 1200 | 70.4225 | 353.192597 | 316.004 | HF | 57 | 100 | HF (E2E noisy) |
| float_log | K=4 | 4 | 1200 | 82.6092 | 370.477985 | 328.191 | HF | 60 | 100 | HF (E2E noisy) |
| float_root | K=4 | 4 | 1200 | 125.574 | 397.031125 | 371.156 | HF | 67 | 190 | HF (E2E noisy) |
| float_set | K=4 | 4 | 1200 | 138.118 | 376.205199 | 383.699 | HF | 70 | 110 | HF (E2E noisy) |
| float_sto | XRP | 4 | 1200 | 88.4825 | 370.271935 | 334.064 | HF | 61 | 230 | HF (E2E noisy) |
| float_sto | IOU | 4 | 1200 | 92.1108 | 340.704342 | 337.693 | HF | 61 | 230 | HF (E2E noisy) |
| float_sto | short | 4 | 1200 | 88.425 | 326.869157 | 334.007 | HF | 61 | 230 | HF (E2E noisy) |
| float_sto_set | K=4 | 4 | 1200 | 74.7058 | 367.713532 | 320.288 | HF | 58 | 140 | HF (E2E noisy) |
| trace | 32B | 4 | 1200 | 270.433 | 582.990859 | 516.014 | HF | 93 | 100 | HF (E2E noisy); default journal level: early-returns on !j.trace() (design review B) |
| trace | 1KiB hex | 4 | 1200 | 1117.86 | 1397.163081 | 1363.44 | HF | 250 | 100 | HF (E2E noisy) |
| trace_num | K=4 | 4 | 1200 | 277.458 | 538.921708 | 523.04 | HF | 95 | 100 | HF (E2E noisy) |
| trace_float | K=4 | 4 | 1200 | 322.153 | 597.084581 | 567.735 | HF | 110 | 100 | HF (E2E noisy) |
| otxn_param | 32B | 4 | 1201 | 159.81 | 438.986230 | 405.392 | HF | 73 | 830 | HF (E2E noisy) |
| otxn_param | 256B | 4 | 1201 | 165.415 | 459.372341 | 410.997 | HF | 74 | 830 | HF (E2E noisy) |
| hook_param | 32B | 4 | 1200 | 101.87 | 391.889007 | 347.452 | HF | 63 | 510 | HF (E2E noisy) |
| hook_param | 256B | 4 | 1200 | 106.085 | 354.114933 | 351.667 | HF | 64 | 510 | HF (E2E noisy) |
| otxn_field | sfAccount(20B) | 1 | 300 | 103.96 | 318.587367 | 349.542 | HF | 63 | 460 | HF (E2E noisy) |
| otxn_field | 1KiB Blob | 1 | 300 | 136.19 | 175.772553 | 381.772 | HF | 69 | 460 | HF (E2E noisy); E2E/HF ratio 0.460412 |
| otxn_field | 16KiB Blob | 1 | 300 | 682.66 | 1012.313293 | 928.242 | HF | 170 | 460 | HF (E2E noisy) |
| otxn_slot | small tx | 1 | 300 | 368.9 | 743.964422 | 614.482 | HF | 120 | 310 | HF (E2E noisy) |
| otxn_slot | 1KiB Blob | 1 | 300 | 399.22 | 692.219978 | 644.802 | HF | 120 | 310 | HF (E2E noisy) |
| otxn_slot | 16KiB Blob | 1 | 300 | 675.19 | 968.360719 | 920.772 | HF | 170 | 310 | HF (E2E noisy) |
| slot | 1KiB Blob | 1 | 300 | 394.98 | 843.228108 | 640.562 | HF | 120 | 1400 | HF (E2E noisy); E2E/HF ratio 1.316388 |
| slot | 16KiB Blob | 1 | 300 | 1037.44 | 1348.805886 | 1283.02 | HF | 240 | 1400 | HF (E2E noisy) |
| slot_size | K=1 | 1 | 300 | 254.413 | 457.053311 | 499.995 | HF | 90 | 330 | HF (E2E noisy) |
| slot_type | flags=0 | 1 | 300 | 73.3733 | 367.432624 | 318.955 | HF | 58 | 210 | HF (E2E noisy) |
| slot_type | flags=1 | 1 | 300 | 96.63 | 512.764784 | 342.212 | HF | 62 | 210 | HF (E2E noisy); E2E/HF ratio 1.498384 |
| slot_count | 3 Memos | 1 | 300 | 75.3367 | 262.331089 | 320.919 | HF | 58 | 230 | HF (E2E noisy) |
| slot_subfield | sfAccount | 1 | 300 | 92.5467 | 321.709590 | 338.129 | HF | 61 | 220 | HF (E2E noisy) |
| slot_float | sfAmount (own tx, Payment) | 1 | 300 | 141.093 | 449.560719 | 386.675 | HF | 70 | 150 | HF (E2E noisy) |
| slot_subarray | Memos[0] | 1 | 300 | 86.99 | 524.268849 | 332.572 | HF | 60 | 330 | HF (E2E noisy); E2E/HF ratio 1.576407 |
| slot_set | 34B keylet | 1 | 300 | 1542.66 | 1984.642923 | 1788.24 | HF | 330 | 350 | HF (E2E noisy) |
| slot_clear | K=1 | 1 | 300 | 206.427 | 114.960344 | 452.009 | HF | 82 | 230 | HF (E2E noisy); E2E/HF ratio 0.254332 |
| sto_validate | ~31B | 1 | 300 | 144.883 | 431.595859 | 390.465 | HF | 71 | 350 | HF (E2E noisy) |
| sto_validate | ~tx (250B) | 1 | 300 | 407.36 | 748.742923 | 652.942 | HF | 120 | 350 | HF (E2E noisy) |
| sto_validate | ~4KiB (Blob) | 1 | 300 | 492.84 | 763.916997 | 738.422 | HF | 140 | 350 | HF (E2E noisy) |
| sto_subfield | ~31B | 1 | 300 | 111.83 | 394.288813 | 357.412 | HF | 65 | 340 | HF (E2E noisy) |
| sto_subfield | ~tx (250B) | 1 | 300 | 268.067 | 514.546988 | 513.649 | HF | 93 | 340 | HF (E2E noisy) |
| sto_subfield | ~4KiB (Blob) | 1 | 300 | 361.793 | 744.409951 | 607.375 | HF | 110 | 340 | HF (E2E noisy) |
| sto_subarray | ~tx (250B) | 1 | 300 | 164.317 | 427.065507 | 409.899 | HF | 74 | 290 | HF (E2E noisy); no small-object point (deferred); single-point table value |
| sto_subarray | 3 Memos, one ~1KiB | 1 | 300 | 173.257 | 625.472914 | 418.839 | HF | 76 | 290 | HF (E2E noisy); E2E/HF ratio 1.493351 |
| sto_emplace | ~31B | 1 | 300 | 219.283 | 475.282852 | 464.865 | HF | 84 | 980 | HF (E2E noisy) |
| sto_emplace | ~tx (250B) | 1 | 300 | 286.127 | 689.941027 | 531.709 | HF | 96 | 980 | HF (E2E noisy) |
| sto_emplace | ~4KiB (Blob) | 1 | 300 | 473.667 | 1008.707693 | 719.249 | HF | 130 | 980 | HF (E2E noisy); E2E/HF ratio 1.402446 |
| sto_erase | ~31B | 1 | 300 | 150.313 | 433.593240 | 395.895 | HF | 72 | 970 | HF (E2E noisy) |
| sto_erase | ~tx (250B) | 1 | 300 | 192.92 | 429.481044 | 438.502 | HF | 79 | 970 | HF (E2E noisy) |
| sto_erase | ~4KiB (Blob) | 1 | 300 | 389.62 | 571.944007 | 635.202 | HF | 120 | 970 | HF (E2E noisy) |
| ledger_nonce | K=200/exec | 1 | 200 | 263.52 | 534.918487 | 509.102 | HF | 92 | 170 | HF (E2E noisy) |
| etxn_nonce | K=200/exec | 1 | 200 | 357.205 | 880.146265 | 602.787 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.460128 |
| util_verify | ed25519 (passing) | 1 | 301 | 23146.1 | 23925.273637 | 23391.7 | E2E | 4400 | 24000 |  |
| util_verify | secp256k1 (passing) | 1 | 301 | 22127.2 | 22958.940304 | 22372.8 | E2E | 4200 | 24000 |  |
| hook_param_set | K=16/exec (cap) | 1 | 16 | 242.812 | - | 488.394 | HF | 88 | 370 |  |
| meta_slot | K=200/exec, weak/AAW pass | 1 | 202 | 81.4505 | - | 327.032 | HF | 59 | 220 | HF (capped/one-shot) |
| prepare | min Payment spec | 1 | 250 | 31901.3 | 33186.648095 | 32146.8 | E2E | 6000 | 36000 | reference size (minimal Payment) |
| prepare | 1KiB ttINVOKE+sfBlob | 1 | 301 | 31404.7 | 32234.432173 | 31650.3 | E2E | 5800 | 36000 | 1KiB sfBlob variant (Phase 3 item 3) |
| etxn_fee_base | 1KiB ttINVOKE+sfBlob | 1 | 302 | 4386.26 | 4189.149969 | 4631.84 | HF | 840 | 4600 | HF (E2E noisy); 1KiB sfBlob variant, direct call (not via emit) -- reference (min Payment) value comes from emit_min_k200's loop, see below |
| ledger_keylet | full range | 1 | 300 | 481.98 | 733.210674 | 727.562 | HF | 140 | 300 | HF (E2E noisy); lower bound: near-empty JTX ledger (design review F3) |
| state | 4KiB (ExtendedHookState) | 1 | 200 | 3025.32 | 4054.938274 | 3270.9 | HF | 590 | 1700 | HF (E2E noisy) |
| state_set | 4KiB (ExtendedHookState) | 1 | 200 | 923.78 | 15751.583802 | 5277.45 | HF | 950 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.984698 |
| state_foreign | read 32B (no grant needed) | 1 | 200 | 2039.97 | 2519.247127 | 2285.55 | HF | 420 | 1700 | HF (E2E noisy) |
| state_foreign | read 256B (no grant needed) | 1 | 200 | 2144.97 | 2792.380460 | 2390.55 | HF | 440 | 1700 | HF (E2E noisy) |
| state_foreign_set | write, K=1 (first call, grant scan) | 1 | 1 | 16496 | - | 33546.6 | HF | 6100 | 3400 | HF (capped/one-shot) |
| state_foreign_set | write, K=200 (grant cached after 1st) | 1 | 200 | 742.7 | 7843.308238 | 3748.73 | HF | 680 | 3400 | HF (ledger-write cost reported separately); E2E/HF ratio 2.092259 |
| emit | K=200/exec, min Payment, own nonce+details+fee_base | 1 | 200 | 8970.65 | - | 9216.23 | HF | 1700 | 8700 | HF (undecomposable body) |
| etxn_details | inside emit_min_k200's loop | 1 | 200 | 500.345 | - | 745.927 | HF | 140 | 470 | HF (undecomposable body) |
| etxn_fee_base | inside emit_min_k200's loop | 1 | 200 | 4389.98 | - | 4635.57 | HF | 840 | 4600 | HF (undecomposable body) |
| emit | K=200/exec, 1KiB ttINVOKE+sfBlob | 1 | 200 | 9638.39 | - | 9883.97 | HF | 1800 | 8700 | HF (undecomposable body) |
| hook_skip | alternating scan/erase (2-hook chain) | 1 | 300 | 117.867 | 697.914378 | 363.449 | HF | 66 | 170 | HF (E2E noisy); E2E/HF ratio 1.920256 |

(`xpop_slot` not observed as a call on fixture `w_regular_key` -- Import tx likely did not reach the hook as ttIMPORT; skipped)

## xpop_slot_k100 (separate Env per rep)

| api | variant | calls | ns/call | t_api (ns) | cost (proposed) | cost (current) | notes |
|---|---|---|---|---|---|---|---|
| xpop_slot | K=100/exec, min over 2 rep(s) (ttIMPORT, one fixture per fresh Env) | 100 | 27205.1 | 27450.7 | 5000 | 37000 | HF (capped/one-shot): anti-replay caps reps to the number of distinct fixtures, no N1/N2 E2E |
| util_keylet | AMM (own Env, featureAMM added) | 4 | 1201 | 306.904 | 597.088963 | 552.486 | HF | 100 | 230 | HF (E2E noisy) |
| util_keylet | DID (own Env, featureDID added) | 4 | 1200 | 266.103 | 555.849148 | 511.685 | HF | 93 | 230 | HF (E2E noisy) |
| etxn_reserve | direct (1st call) | 1 | 1 | 231 | - | 476.582 | HF | 86 | 150 | HF (capped/one-shot): error path after 1st call is trivial (design review B) |
| hook_again | direct (1st call, strong pass) | 1 | 1 | 179 | - | 424.582 | HF | 77 | 260 | HF (capped/one-shot): error path after 1st call is trivial (design review B) |

## Apply-time ledger cost (not charged by HOOK_API_COST)

Per created / modified hook-state entry on this platform; per ledger entry, node-store dependent, not per API call (DESIGN §2.1).

| variant | E2E (ns/call) | HF (ns/call) | (E2E - HF) ns/entry | path |
|---|---|---|---|---|
| state_set: 32B, modify (fixed keys) | 7623.767136 | 3504.52 | 4119.245173 | modify |
| state_set: 32B, create (fresh keys, salt=rep) | 26396.063749 | 2869.72 | 23526.341786 | create |
| state_set: 256B | 8802.544913 | 3726.61 | 5075.937951 | modify |
| state_set: 4KiB (ExtendedHookState) | 15751.583802 | 5277.45 | 10474.136839 | modify |
| state_foreign_set: write, K=1 (first call, grant scan) | - | 33546.6 | - | modify |
| state_foreign_set: write, K=200 (grant cached after 1st) | 7843.308238 | 3748.73 | 4094.581275 | modify |

## Terminal APIs (accept / rollback)

| api | calls | ns/call (min) | ns/call (mean) | t_api (ns, from mean) | cost (proposed) | cost (current) | exec.ns diff vs noexit |
|---|---|---|---|---|---|---|---|

`noexit` (hook returns 0 without calling accept/rollback/exit): mean exec.ns = 35013.4 over 200/200 reps

| accept | 1 | 174 | 237.665 | 483.247 | 87 | 150 | -4046.72 |
| rollback | 1 | 139.5 | 171.303 | 416.884 | 75 | 180 | 3240.31 |

## Table value per API (DESIGN §2.4 rule)

| api | rule | rows | table cost |
|---|---|---|---|
| accept | max (single size, multiple paths) | 1 | 87 |
| emit | max (single size, multiple paths) | 2 | 1800 |
| etxn_burden | max (single size, multiple paths) | 1 | 64 |
| etxn_details | max (single size, multiple paths) | 1 | 140 |
| etxn_fee_base | max (single size, multiple paths) | 2 | 840 |
| etxn_generation | max (single size, multiple paths) | 1 | 56 |
| etxn_nonce | max (single size, multiple paths) | 1 | 110 |
| etxn_reserve | max (single size, multiple paths) | 1 | 86 |
| fee_base | max (single size, multiple paths) | 1 | 57 |
| float_compare | mode: max | 2 | 64 |
| float_divide | max (single size, multiple paths) | 1 | 61 |
| float_int | max (single size, multiple paths) | 1 | 57 |
| float_invert | max (single size, multiple paths) | 1 | 57 |
| float_log | max (single size, multiple paths) | 1 | 60 |
| float_mantissa | max (single size, multiple paths) | 1 | 57 |
| float_mulratio | max (single size, multiple paths) | 1 | 65 |
| float_multiply | max (single size, multiple paths) | 1 | 80 |
| float_negate | max (single size, multiple paths) | 1 | 57 |
| float_one | max (single size, multiple paths) | 1 | 48 |
| float_root | max (single size, multiple paths) | 1 | 67 |
| float_set | max (single size, multiple paths) | 1 | 70 |
| float_sign | max (single size, multiple paths) | 1 | 57 |
| float_sto | mode: max | 3 | 61 |
| float_sto_set | max (single size, multiple paths) | 1 | 58 |
| float_sum | max (single size, multiple paths) | 1 | 66 |
| hook_account | max (single size, multiple paths) | 1 | 58 |
| hook_again | max (single size, multiple paths) | 1 | 77 |
| hook_hash | mode: max | 2 | 65 |
| hook_param | max (single size, multiple paths) | 2 | 64 |
| hook_param_set | max (single size, multiple paths) | 1 | 88 |
| hook_pos | max (single size, multiple paths) | 1 | 48 |
| hook_skip | max (single size, multiple paths) | 1 | 66 |
| ledger_keylet | max (single size, multiple paths) | 1 | 140 |
| ledger_last_hash | max (single size, multiple paths) | 1 | 58 |
| ledger_last_time | max (single size, multiple paths) | 1 | 57 |
| ledger_nonce | max (single size, multiple paths) | 1 | 92 |
| ledger_seq | max (single size, multiple paths) | 1 | 57 |
| meta_slot | max (single size, multiple paths) | 1 | 59 |
| otxn_burden | max (single size, multiple paths) | 1 | 64 |
| otxn_field | size: reference (DESIGN §2.4) | 3 | 69 |
| otxn_generation | max (single size, multiple paths) | 1 | 63 |
| otxn_id | mode: max | 2 | 58 |
| otxn_param | mode: max | 2 | 74 |
| otxn_slot | size: reference (DESIGN §2.4) | 3 | 120 |
| otxn_type | max (single size, multiple paths) | 1 | 57 |
| prepare | max (single size, multiple paths) | 2 | 5800 |
| rollback | max (single size, multiple paths) | 1 | 75 |
| slot | size: reference (DESIGN §2.4) | 2 | 120 |
| slot_clear | max (single size, multiple paths) | 1 | 82 |
| slot_count | max (single size, multiple paths) | 1 | 58 |
| slot_float | max (single size, multiple paths) | 1 | 70 |
| slot_set | max (single size, multiple paths) | 1 | 330 |
| slot_size | max (single size, multiple paths) | 1 | 90 |
| slot_subarray | max (single size, multiple paths) | 1 | 60 |
| slot_subfield | max (single size, multiple paths) | 1 | 61 |
| slot_type | mode: max | 2 | 62 |
| state | size: reference (DESIGN §2.4) | 3 | 420 |
| state_foreign | mode: max | 2 | 440 |
| state_foreign_set | mode: max | 2 | 6100 |
| state_set | size: reference (DESIGN §2.4) | 4 | 680 |
| sto_emplace | size: reference (DESIGN §2.4) | 3 | 96 |
| sto_erase | size: reference (DESIGN §2.4) | 3 | 79 |
| sto_subarray | size: reference (DESIGN §2.4) | 2 | 74 |
| sto_subfield | size: reference (DESIGN §2.4) | 3 | 93 |
| sto_validate | size: reference (DESIGN §2.4) | 3 | 120 |
| trace | mode: max | 2 | 250 |
| trace_float | max (single size, multiple paths) | 1 | 110 |
| trace_num | max (single size, multiple paths) | 1 | 95 |
| util_accid | max (single size, multiple paths) | 1 | 110 |
| util_keylet | mode: max | 25 | 100 |
| util_raddr | max (single size, multiple paths) | 1 | 120 |
| util_sha512h | size: geomean(ref, largest) [>10x] | 3 | 1010 |
| util_verify | mode: max | 2 | 4400 |
| xpop_slot | max (single size, multiple paths) | 1 | 5000 |
| _g | loop-head guard: fit intercept G / t_instr | 6 | 63 |

## Proposed HOOK_API_COST block

In include/xrpl/hook/hook_api.macro declaration order; amendment column preserved from that file. An API with no measured row this run keeps its current value, annotated `// unmeasured`. `_g` is the baseline fit intercept G over t_instr (not charged by the guard checker today).

```
HOOK_API_COST(_g, 63, uint256{})
HOOK_API_COST(accept, 87, uint256{})
HOOK_API_COST(rollback, 75, uint256{})
HOOK_API_COST(util_raddr, 120, uint256{})
HOOK_API_COST(util_accid, 110, uint256{})
HOOK_API_COST(util_verify, 4400, uint256{})  // ARM SHA-512 hardware acceleration; x86-64 run required before adoption (DESIGN §5)
HOOK_API_COST(util_sha512h, 1010, uint256{})  // ARM SHA-512 hardware acceleration; x86-64 run required before adoption (DESIGN §5)
HOOK_API_COST(util_keylet, 100, uint256{})
HOOK_API_COST(sto_validate, 120, uint256{})
HOOK_API_COST(sto_subfield, 93, uint256{})
HOOK_API_COST(sto_subarray, 74, uint256{})
HOOK_API_COST(sto_emplace, 96, uint256{})
HOOK_API_COST(sto_erase, 79, uint256{})
HOOK_API_COST(etxn_burden, 64, uint256{})
HOOK_API_COST(etxn_details, 140, uint256{})
HOOK_API_COST(etxn_fee_base, 840, uint256{})
HOOK_API_COST(etxn_reserve, 86, uint256{})
HOOK_API_COST(etxn_generation, 56, uint256{})
HOOK_API_COST(etxn_nonce, 110, uint256{})
HOOK_API_COST(emit, 1800, uint256{})
HOOK_API_COST(float_set, 70, uint256{})
HOOK_API_COST(float_multiply, 80, uint256{})
HOOK_API_COST(float_mulratio, 65, uint256{})
HOOK_API_COST(float_negate, 57, uint256{})
HOOK_API_COST(float_compare, 64, uint256{})
HOOK_API_COST(float_sum, 66, uint256{})
HOOK_API_COST(float_sto, 61, uint256{})
HOOK_API_COST(float_sto_set, 58, uint256{})
HOOK_API_COST(float_invert, 57, uint256{})
HOOK_API_COST(float_divide, 61, uint256{})
HOOK_API_COST(float_one, 48, uint256{})
HOOK_API_COST(float_mantissa, 57, uint256{})
HOOK_API_COST(float_sign, 57, uint256{})
HOOK_API_COST(float_int, 57, uint256{})
HOOK_API_COST(float_log, 60, uint256{})
HOOK_API_COST(float_root, 67, uint256{})
HOOK_API_COST(fee_base, 57, uint256{})
HOOK_API_COST(ledger_seq, 57, uint256{})
HOOK_API_COST(ledger_last_time, 57, uint256{})
HOOK_API_COST(ledger_last_hash, 58, uint256{})
HOOK_API_COST(ledger_nonce, 92, uint256{})
HOOK_API_COST(ledger_keylet, 140, uint256{})
HOOK_API_COST(hook_account, 58, uint256{})
HOOK_API_COST(hook_hash, 65, uint256{})
HOOK_API_COST(hook_param_set, 88, uint256{})
HOOK_API_COST(hook_param, 64, uint256{})
HOOK_API_COST(hook_again, 77, uint256{})
HOOK_API_COST(hook_skip, 66, uint256{})
HOOK_API_COST(hook_pos, 48, uint256{})
HOOK_API_COST(slot, 120, uint256{})
HOOK_API_COST(slot_clear, 82, uint256{})
HOOK_API_COST(slot_count, 58, uint256{})
HOOK_API_COST(slot_set, 330, uint256{})
HOOK_API_COST(slot_size, 90, uint256{})
HOOK_API_COST(slot_subarray, 60, uint256{})
HOOK_API_COST(slot_subfield, 61, uint256{})
HOOK_API_COST(slot_type, 62, uint256{})
HOOK_API_COST(slot_float, 70, uint256{})
HOOK_API_COST(state_set, 680, uint256{})
HOOK_API_COST(state_foreign_set, 6100, uint256{})
HOOK_API_COST(state, 420, uint256{})
HOOK_API_COST(state_foreign, 440, uint256{})
HOOK_API_COST(trace, 250, uint256{})
HOOK_API_COST(trace_num, 95, uint256{})
HOOK_API_COST(trace_float, 110, uint256{})
HOOK_API_COST(otxn_burden, 64, uint256{})
HOOK_API_COST(otxn_field, 69, uint256{})
HOOK_API_COST(otxn_generation, 63, uint256{})
HOOK_API_COST(otxn_id, 58, uint256{})
HOOK_API_COST(otxn_type, 57, uint256{})
HOOK_API_COST(otxn_slot, 120, uint256{})
HOOK_API_COST(otxn_param, 74, uint256{})
HOOK_API_COST(meta_slot, 59, uint256{})
HOOK_API_COST(xpop_slot, 5000, uint256{})
HOOK_API_COST(prepare, 5800, uint256{})
```

## Deferred (not measured this run)

* `util_keylet` -- every keylet_type with a dedicated constant in hookapi.h is covered except BRIDGE, XCHAIN_OWNED_CLAIM_ID, XCHAIN_OWNED_CREATE_ACCOUNT_CLAIM_ID, MPTOKEN_ISSUANCE, MPTOKEN, CREDENTIAL, and PERMISSIONED_DOMAIN: applyHook.cpp's util_keylet unconditionally returns INVALID_ARGUMENT for these (not measurable regardless of amendment state, see the comment at applyHook.cpp's keylet_code::BRIDGE case); TICKET (13) has no case in util_keylet's switch at all and is not accepted. AMM and DID are both measured (own Env with featureAMM/featureDID added, since both are Supported::no and so not in supported_amendments()).

## Notes

* HOOK_API_COST(_g) is dead: loop-head guards are consumed by the checker without being counted (design review sec A3). t_call/t_instr above still reflect the real cost of `_g`, reported for completeness.
* HOOK_API_COST is in static worst-case instruction units; t_instr is measured against the runtime instruction count, which is conservative (design review sec A4).
