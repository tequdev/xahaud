# HookAPICost results

## Header

* CPU: Apple M3 Ultra
* OS: Darwin Yu-Mac-Studio-m3.local 25.5.0 Darwin Kernel Version 25.5.0: Mon Apr 27 20:39:42 PDT 2026; root:xnu-12377.121.6~2/RELEASE_ARM64_T6031 arm64 arm Darwin
* Compiler: Apple LLVM 16.0.0 (clang-1600.0.26.6)
* Build type: Release (hook_cost_bench=ON)
* WasmEdge: 0.11.2
* git SHA: d742f4912d82827457aedc02b39f44c30e44a57e
* t_clk (mean nowNs() pair overhead): 14 ns
* clock resolution (smallest non-zero delta, review #4): 41 ns
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
| base1 | 130 | 1300 | 4625 | 45575 | 35 | 399.715 | 388.997 | 43.0377 | 5.52873 |
| base2 | 70 | 700 | 3855 | 37875 | 54 | 502.446 | 461.64 | 62.0699 | 3.94696 |
| base4 | 40 | 400 | 4075 | 40075 | 100 | 681.711 | 657.872 | 108.122 | 2.60354 |
| base8 | 25 | 250 | 4775 | 47075 | 188 | 994.631 | 971.853 | 196.195 | 1.86352 |
| base16 | 5 | 50 | 1895 | 18275 | 364 | 1602.78 | 1618.51 | 372.961 | 1.50484 |
| base64 | 3 | 38 | 4335 | 54035 | 1420 | 5733.34 | 5530.94 | 1429.26 | 1.1552 |

Fitted (env.close() wall-clock, calibration channel): t_instr = 3.83795 ns, G (_g total per-iteration cost) = 270.135 ns, SE(G) = 19.2624 ns, R^2 = 0.999725
Fitted (exec.ns, wasm-window only, comparison): t_instr = 3.70532 ns, G = 270.437 ns, SE(G) = 5.75349 ns, R^2 = 0.999974

### Sensitivity baselines (t_instr alone, using G)

| baseline | dI | dTw env.close (ns) | t_instr alone (ns) |
|---|---|---|---|
| basei64 | 194 | 1005.91 | 3.79264 |
| basemem | 118 | 748.622 | 4.05497 |

* t_instr = 3.83795 ns
* G (loop-head _g total per-iteration cost) = 270.135 ns
* R^2 (baseline fit) = 0.999725
* t_call (0-arg boundary, from E2E(hook_pos) - (M_pos - 2*t_clk)) = 200.464 ns
* O_g (the `_g` 2-arg call's own G above) = 270.135 ns vs t_call (0-arg hook_pos) = 200.464 ns -- host-call boundary grows roughly 34.8357 ns per argument

## Per-API results

| api | variant | K | calls | ns/call (M) | E2E (ns) | HF (ns) | used | cost (proposed) | cost (current) | notes |
|---|---|---|---|---|---|---|---|---|---|---|
| hook_pos | K=4 | 4 | 3400 | 13.8985 | 186.362296 | 186.362 | HF | 49 | 40 | HF (E2E noisy) |
| fee_base | K=4 | 4 | 1800 | 68.1967 | 272.335048 | 240.66 | E2E | 71 | 70 |  |
| ledger_seq | K=4 | 4 | 1800 | 66.4206 | 264.901714 | 238.884 | HF | 63 | 140 | HF (E2E noisy) |
| float_one | K=4 | 4 | 1800 | 12.5272 | 183.125400 | 184.991 | HF | 49 | 20 | HF (E2E noisy) |
| otxn_type | K=4 | 4 | 1800 | 66.0133 | 269.196776 | 238.477 | E2E | 71 | 130 |  |
| etxn_generation | K=4 | 4 | 1800 | 53.0489 | 246.473548 | 225.513 | HF | 59 | 130 | HF (E2E noisy) |
| util_sha512h | 32B | 1 | 1000 | 151.55 | 358.313685 | 324.014 | HF | 85 | 340 | HF (E2E noisy) |
| util_sha512h | 1KiB | 1 | 1000 | 706.88 | 907.712574 | 879.344 | HF | 230 | 340 | HF (E2E noisy) |
| util_sha512h | 16KiB | 1 | 1000 | 9237.12 | 9460.629240 | 9409.59 | E2E | 2500 | 340 |  |
| state | 32B | 1 | 200 | 1649.43 | 2307.364585 | 1821.9 | HF | 480 | 1700 | HF (E2E noisy) |
| state | 256B | 1 | 200 | 1805.21 | 2586.064585 | 1977.68 | HF | 520 | 1700 | HF (E2E noisy); E2E/HF ratio 1.307626 |
| state_set | 32B, modify (fixed keys) | 1 | 200 | 572.955 | 7258.848856 | 2961.66 | HF | 780 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.450936; review #6: modify path |
| state_set | 32B, create (fresh keys, salt=rep) | 1 | 200 | 591.19 | 23306.193369 | 2218.03 | HF | 580 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 10.507615; review #6: create path |
| state_set | 256B | 1 | 200 | 599.98 | 7621.109967 | 3533.48 | HF | 930 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.156826 |
| util_raddr | K=4 | 4 | 1200 | 273.919 | 504.192192 | 446.383 | HF | 120 | 980 | HF (E2E noisy) |
| util_accid | K=4 | 4 | 1200 | 262.087 | 502.340340 | 434.55 | E2E | 140 | 690 |  |
| util_keylet | ACCOUNT | 4 | 1200 | 167.026 | 442.795027 | 339.49 | HF | 89 | 230 | HF (E2E noisy); E2E/HF ratio 1.304296 |
| util_keylet | CHILD | 4 | 1200 | 74.4092 | 314.593175 | 246.873 | HF | 65 | 230 | HF (E2E noisy) |
| util_keylet | ESCROW | 4 | 1200 | 170.722 | 413.550582 | 343.186 | HF | 90 | 230 | HF (E2E noisy) |
| util_keylet | LINE | 4 | 1200 | 182.627 | 421.923731 | 355.09 | HF | 93 | 230 | HF (E2E noisy) |
| util_keylet | AMENDMENTS | 4 | 1200 | 76.8808 | 350.048731 | 249.345 | HF | 65 | 230 | HF (E2E noisy); E2E/HF ratio 1.403875 |
| util_keylet | QUALITY | 4 | 1200 | 73.5917 | 306.067249 | 246.055 | HF | 65 | 230 | HF (E2E noisy); AMENDMENTS's case also covers FEES/NEGATIVE_UNL/EMITTED_DIR (identical switch case); AMM/BRIDGE/XCHAIN_*/MPTOKEN_*/CREDENTIAL/PERMISSIONED_DOMAIN not built (complex multi-part operands -- asset pairs, bridge specs); every other keylet_type is covered below |
| util_keylet | HOOK | 4 | 1200 | 165.789 | 419.879286 | 338.253 | HF | 89 | 230 | HF (E2E noisy) |
| util_keylet | HOOK_STATE | 4 | 1200 | 191.213 | 422.733916 | 363.676 | HF | 95 | 230 | HF (E2E noisy) |
| util_keylet | SKIP | 4 | 1200 | 79.1667 | 390.596879 | 251.63 | HF | 66 | 230 | HF (E2E noisy); E2E/HF ratio 1.552264 |
| util_keylet | OFFER | 4 | 1200 | 168.939 | 420.187619 | 341.403 | HF | 89 | 230 | HF (E2E noisy) |
| util_keylet | SIGNERS | 4 | 1200 | 169.219 | 413.783916 | 341.683 | HF | 90 | 230 | HF (E2E noisy) |
| util_keylet | CHECK | 4 | 1200 | 172.864 | 406.145027 | 345.328 | HF | 90 | 230 | HF (E2E noisy) |
| util_keylet | DEPOSIT_PREAUTH | 4 | 1200 | 174.173 | 407.146879 | 346.637 | HF | 91 | 230 | HF (E2E noisy) |
| util_keylet | UNCHECKED | 4 | 1200 | 73.9542 | 334.655212 | 246.418 | HF | 65 | 230 | HF (E2E noisy); E2E/HF ratio 1.358080 |
| util_keylet | OWNER_DIR | 4 | 1200 | 165.363 | 411.699657 | 337.826 | HF | 89 | 230 | HF (E2E noisy) |
| util_keylet | PAGE | 4 | 1200 | 169.512 | 400.279286 | 341.975 | HF | 90 | 230 | HF (E2E noisy) |
| util_keylet | PAYCHAN | 4 | 1200 | 175.216 | 402.981138 | 347.68 | HF | 91 | 230 | HF (E2E noisy) |
| util_keylet | EMITTED_TXN | 4 | 1200 | 162.012 | 397.965397 | 334.475 | HF | 88 | 230 | HF (E2E noisy) |
| util_keylet | NFT_OFFER | 4 | 1200 | 170.067 | 408.845027 | 342.531 | HF | 90 | 230 | HF (E2E noisy) |
| util_keylet | HOOK_DEFINITION | 4 | 1200 | 160.66 | 441.521879 | 333.124 | HF | 87 | 230 | HF (E2E noisy); E2E/HF ratio 1.325399 |
| util_keylet | HOOK_STATE_DIR | 4 | 1200 | 216.703 | 469.762619 | 389.167 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | CRON | 4 | 1200 | 213.143 | 457.919101 | 385.607 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | ORACLE | 4 | 1200 | 213.337 | 445.920953 | 385.8 | HF | 110 | 230 | HF (E2E noisy) |
| etxn_burden | K=4 | 4 | 1200 | 115.932 | 320.045850 | 288.395 | HF | 76 | 260 | HF (E2E noisy) |
| otxn_burden | K=4 | 4 | 1200 | 113.11 | 304.241141 | 285.574 | E2E | 80 | 260 |  |
| otxn_generation | K=4 | 4 | 1200 | 111.213 | 286.108733 | 283.677 | HF | 74 | 280 | HF (E2E noisy) |
| ledger_last_time | K=4 | 4 | 1200 | 65.8075 | 241.996776 | 238.271 | HF | 63 | 110 | HF (E2E noisy) |
| ledger_last_hash | K=4 | 4 | 1200 | 73.2267 | 210.556984 | 245.69 | HF | 65 | 210 | HF (E2E noisy) |
| hook_account | K=4 | 4 | 1200 | 74.7275 | 333.356984 | 247.191 | HF | 65 | 140 | HF (E2E noisy); E2E/HF ratio 1.348579 |
| hook_hash | hook_no=0 | 4 | 1200 | 103.891 | 305.676440 | 276.355 | HF | 73 | 340 | HF (E2E noisy) |
| hook_hash | hook_no=-1 | 4 | 1200 | 71.2167 | 301.278292 | 243.68 | HF | 64 | 340 | HF (E2E noisy) |
| otxn_id | flags=0 | 4 | 1200 | 72.58 | 284.188477 | 245.044 | HF | 64 | 450 | HF (E2E noisy) |
| otxn_id | flags=1 | 4 | 1200 | 72.185 | 252.011625 | 244.649 | HF | 64 | 450 | HF (E2E noisy) |
| float_multiply | K=4 | 4 | 1200 | 123.225 | 330.708756 | 295.689 | E2E | 87 | 240 |  |
| float_mulratio | K=4 | 4 | 1200 | 99.5183 | 294.560631 | 271.982 | HF | 71 | 390 | HF (E2E noisy) |
| float_negate | K=4 | 4 | 1200 | 66.1275 | 257.849485 | 238.591 | HF | 63 | 160 | HF (E2E noisy) |
| float_compare | COMPARE_EQUAL | 4 | 1200 | 87.3992 | 301.664403 | 259.863 | HF | 68 | 140 | HF (E2E noisy) |
| float_compare | COMPARE_LESS|COMPARE_EQUAL | 4 | 1200 | 90.8642 | 301.356070 | 263.328 | HF | 69 | 140 | HF (E2E noisy) |
| float_sum | K=4 | 4 | 1200 | 105.802 | 336.380052 | 278.266 | HF | 73 | 350 | HF (E2E noisy) |
| float_invert | K=4 | 4 | 1200 | 66.5942 | 257.193004 | 239.058 | HF | 63 | 230 | HF (E2E noisy) |
| float_divide | K=4 | 4 | 1200 | 110.661 | 327.391163 | 283.125 | E2E | 86 | 280 |  |
| float_mantissa | K=4 | 4 | 1200 | 66.0383 | 277.062448 | 238.502 | HF | 63 | 170 | HF (E2E noisy) |
| float_sign | K=4 | 4 | 1200 | 66.7683 | 287.246708 | 239.232 | HF | 63 | 80 | HF (E2E noisy) |
| float_int | K=4 | 4 | 1200 | 67.3583 | 284.045804 | 239.822 | HF | 63 | 100 | HF (E2E noisy) |
| float_log | K=4 | 4 | 1200 | 74.8658 | 262.402263 | 247.33 | HF | 65 | 100 | HF (E2E noisy) |
| float_root | K=4 | 4 | 1200 | 98.5258 | 282.638386 | 270.99 | HF | 71 | 190 | HF (E2E noisy) |
| float_set | K=4 | 4 | 1200 | 94.495 | 304.204126 | 266.959 | HF | 70 | 110 | HF (E2E noisy) |
| float_sto | XRP | 4 | 1200 | 91.6858 | 295.397793 | 264.15 | HF | 69 | 230 | HF (E2E noisy) |
| float_sto | IOU | 4 | 1200 | 108.055 | 360.291312 | 280.519 | E2E | 94 | 230 |  |
| float_sto | short | 4 | 1200 | 94.4092 | 244.010756 | 266.873 | HF | 70 | 230 | HF (E2E noisy) |
| float_sto_set | K=4 | 4 | 1200 | 95.7092 | 355.091163 | 268.173 | HF | 70 | 140 | HF (E2E noisy); E2E/HF ratio 1.324113 |
| trace | 32B | 4 | 1200 | 432.362 | 687.140340 | 604.825 | E2E | 180 | 100 | default journal level: early-returns on !j.trace() (design review B) |
| trace | 1KiB hex | 4 | 1200 | 743.718 | 1023.019970 | 916.182 | E2E | 270 | 100 |  |
| trace_num | K=4 | 4 | 1200 | 421.779 | 638.069718 | 594.243 | E2E | 170 | 100 |  |
| trace_float | K=4 | 4 | 1200 | 521.322 | 770.509762 | 693.785 | E2E | 210 | 100 |  |
| otxn_param | 32B | 4 | 1201 | 197.626 | 431.430155 | 370.09 | HF | 97 | 830 | HF (E2E noisy) |
| otxn_param | 256B | 4 | 1201 | 195.739 | 440.612562 | 368.203 | HF | 96 | 830 | HF (E2E noisy) |
| hook_param | 32B | 4 | 1200 | 108.658 | 331.507007 | 281.122 | HF | 74 | 510 | HF (E2E noisy) |
| hook_param | 256B | 4 | 1200 | 106.976 | 326.916266 | 279.44 | E2E | 86 | 510 |  |
| otxn_field | sfAccount(20B) | 1 | 300 | 105.827 | 532.552263 | 278.29 | HF | 73 | 460 | HF (E2E noisy); E2E/HF ratio 1.913656 |
| otxn_field | 1KiB Blob | 1 | 300 | 138.607 | 292.430041 | 311.07 | HF | 82 | 460 | HF (E2E noisy) |
| otxn_field | 16KiB Blob | 1 | 300 | 516.8 | 464.189300 | 689.264 | HF | 180 | 460 | HF (E2E noisy); E2E/HF ratio 0.673457 |
| otxn_slot | small tx | 1 | 300 | 338.337 | 624.639277 | 510.8 | HF | 140 | 310 | HF (E2E noisy) |
| otxn_slot | 1KiB Blob | 1 | 300 | 376.387 | 593.776314 | 548.85 | HF | 150 | 310 | HF (E2E noisy) |
| otxn_slot | 16KiB Blob | 1 | 300 | 563.873 | 685.294833 | 736.337 | HF | 200 | 310 | HF (E2E noisy) |
| slot | 1KiB Blob | 1 | 300 | 383.053 | 650.763374 | 555.517 | HF | 150 | 1400 | HF (E2E noisy) |
| slot | 16KiB Blob | 1 | 300 | 1276.93 | 1713.418929 | 1449.39 | HF | 380 | 1400 | HF (E2E noisy) |
| slot_size | K=1 | 1 | 300 | 282.633 | 264.454092 | 455.097 | HF | 120 | 330 | HF (E2E noisy); E2E/HF ratio 0.581094 |
| slot_type | flags=0 | 1 | 300 | 76.25 | 397.978097 | 248.714 | HF | 65 | 210 | HF (E2E noisy); E2E/HF ratio 1.600145 |
| slot_type | flags=1 | 1 | 300 | 83.8833 | 301.356881 | 256.347 | HF | 67 | 210 | HF (E2E noisy) |
| slot_count | 3 Memos | 1 | 300 | 69.57 | 244.554092 | 242.034 | HF | 64 | 230 | HF (E2E noisy) |
| slot_subfield | sfAccount | 1 | 300 | 99.42 | 295.826337 | 271.884 | HF | 71 | 220 | HF (E2E noisy) |
| slot_float | sfAmount (own tx, Payment) | 1 | 300 | 97.7667 | 263.683721 | 270.23 | HF | 71 | 150 | HF (E2E noisy) |
| slot_subarray | Memos[0] | 1 | 300 | 75.2733 | 260.174485 | 247.737 | HF | 65 | 330 | HF (E2E noisy) |
| slot_set | 34B keylet | 1 | 300 | 1277.19 | 1492.430041 | 1449.66 | HF | 380 | 350 | HF (E2E noisy) |
| slot_clear | K=1 | 1 | 300 | 179.193 | 322.745405 | 351.657 | HF | 92 | 230 | HF (E2E noisy) |
| sto_validate | ~31B | 1 | 300 | 184.567 | 393.112482 | 357.03 | HF | 94 | 350 | HF (E2E noisy) |
| sto_validate | ~tx (250B) | 1 | 300 | 590.947 | 929.311522 | 763.41 | HF | 200 | 350 | HF (E2E noisy) |
| sto_validate | ~4KiB (Blob) | 1 | 300 | 654.163 | 917.737448 | 826.627 | HF | 220 | 350 | HF (E2E noisy) |
| sto_subfield | ~31B | 1 | 300 | 139.44 | 464.881938 | 311.904 | HF | 82 | 340 | HF (E2E noisy); E2E/HF ratio 1.490466 |
| sto_subfield | ~tx (250B) | 1 | 300 | 403.047 | 585.506904 | 575.51 | HF | 150 | 340 | HF (E2E noisy) |
| sto_subfield | ~4KiB (Blob) | 1 | 300 | 480.017 | 674.236533 | 652.48 | HF | 180 | 340 | HF (E2E noisy) |
| sto_subarray | ~tx (250B) | 1 | 300 | 224.183 | 382.269867 | 396.647 | HF | 110 | 290 | HF (E2E noisy); no small-object point (deferred); single-point table value |
| sto_subarray | 3 Memos, one ~1KiB | 1 | 300 | 245.83 | 525.784682 | 418.294 | HF | 110 | 290 | HF (E2E noisy) |
| sto_emplace | ~31B | 1 | 300 | 300.83 | 523.452354 | 473.294 | HF | 130 | 980 | HF (E2E noisy) |
| sto_emplace | ~tx (250B) | 1 | 300 | 447.067 | 688.825468 | 619.53 | HF | 170 | 980 | HF (E2E noisy) |
| sto_emplace | ~4KiB (Blob) | 1 | 300 | 611.39 | 819.229172 | 783.854 | HF | 210 | 980 | HF (E2E noisy) |
| sto_erase | ~31B | 1 | 300 | 197.913 | 420.794924 | 370.377 | HF | 97 | 970 | HF (E2E noisy) |
| sto_erase | ~tx (250B) | 1 | 300 | 270.01 | 441.408779 | 442.474 | HF | 120 | 970 | HF (E2E noisy) |
| sto_erase | ~4KiB (Blob) | 1 | 300 | 425.743 | 620.116186 | 598.207 | HF | 160 | 970 | HF (E2E noisy) |
| ledger_nonce | K=200/exec | 1 | 200 | 187.085 | 339.095770 | 359.549 | HF | 94 | 170 | HF (E2E noisy) |
| etxn_nonce | K=200/exec | 1 | 200 | 253.135 | 537.934659 | 425.599 | HF | 120 | 230 | HF (E2E noisy) |
| util_verify | ed25519 (passing) | 1 | 301 | 25242.7 | 26125.512482 | 25415.1 | E2E | 6900 | 24000 |  |
| util_verify | secp256k1 (passing) | 1 | 301 | 20146.7 | 20989.249519 | 20319.2 | E2E | 5500 | 24000 |  |
| hook_param_set | K=16/exec (cap) | 1 | 16 | 177.062 | 1803.925696 | 349.526 | HF | 92 | 370 | HF (E2E noisy); E2E/HF ratio 5.161059 |
| meta_slot | K=200/exec, weak/AAW pass | 1 | 202 | 66 | - | 238.464 | HF | 63 | 220 | HF (capped/one-shot) |
| prepare | min Payment spec | 1 | 250 | 33151 | 34034.347013 | 33323.5 | E2E | 8900 | 36000 | reference size (minimal Payment) |
| prepare | 1KiB ttINVOKE+sfBlob | 1 | 301 | 35400 | 36189.055052 | 35572.5 | E2E | 9500 | 36000 | 1KiB sfBlob variant (Phase 3 item 3) |
| etxn_fee_base | 1KiB ttINVOKE+sfBlob | 1 | 302 | 3764.76 | 4147.812437 | 3937.23 | HF | 1100 | 4600 | HF (E2E noisy); 1KiB sfBlob variant, direct call (not via emit) -- reference (min Payment) value comes from emit_min_k200's loop, see below |
| ledger_keylet | full range | 1 | 300 | 242.77 | 455.919890 | 415.234 | HF | 110 | 300 | HF (E2E noisy); lower bound: near-empty JTX ledger (design review F3) |
| state | 4KiB (ExtendedHookState) | 1 | 200 | 2345.39 | 2974.301599 | 2517.85 | HF | 660 | 1700 | HF (E2E noisy) |
| state_set | 4KiB (ExtendedHookState) | 1 | 200 | 749.51 | 13063.243300 | 4320.93 | HF | 1200 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 3.023245 |
| state_foreign | read 32B (no grant needed) | 1 | 200 | 1658.13 | 2415.655349 | 1830.59 | HF | 480 | 1700 | HF (E2E noisy); E2E/HF ratio 1.319602 |
| state_foreign | read 256B (no grant needed) | 1 | 200 | 1714.95 | 2353.616460 | 1887.42 | HF | 500 | 1700 | HF (E2E noisy) |
| state_foreign_set | write, K=1 (first call, grant scan) | 1 | 1 | 8917 | - | 16006.5 | HF | 4200 | 3400 | HF (capped/one-shot) |
| state_foreign_set | write, K=200 (grant cached after 1st) | 1 | 200 | 641.88 | 7007.322015 | 3156.22 | HF | 830 | 3400 | HF (ledger-write cost reported separately); E2E/HF ratio 2.220164 |
| emit | K=200/exec, min Payment, own nonce+details+fee_base | 1 | 200 | 8144.6 | - | 8317.06 | HF | 2200 | 8700 | HF (undecomposable body) |
| etxn_details | inside emit_min_k200's loop | 1 | 200 | 373.95 | - | 546.414 | HF | 150 | 470 | HF (undecomposable body) |
| etxn_fee_base | inside emit_min_k200's loop | 1 | 200 | 3956.62 | - | 4129.09 | HF | 1100 | 4600 | HF (undecomposable body) |
| emit | K=200/exec, 1KiB ttINVOKE+sfBlob | 1 | 200 | 7728.53 | - | 7901 | HF | 2100 | 8700 | HF (undecomposable body) |
| hook_skip | alternating scan/erase (2-hook chain) | 1 | 300 | 105.82 | 300.671741 | 278.284 | HF | 73 | 170 | HF (E2E noisy) |

(`xpop_slot` not observed as a call on fixture `w_regular_key` -- Import tx likely did not reach the hook as ttIMPORT; skipped)

## xpop_slot_k100 (separate Env per rep)

| api | variant | calls | ns/call | t_api (ns) | cost (proposed) | cost (current) | notes |
|---|---|---|---|---|---|---|---|
| xpop_slot | K=100/exec, min over 2 rep(s) (ttIMPORT, one fixture per fresh Env) | 100 | 39088.3 | 39260.8 | 11000 | 37000 | HF (capped/one-shot): anti-replay caps reps to the number of distinct fixtures, no N1/N2 E2E |
| util_keylet | AMM (own Env, featureAMM added) | 4 | 1201 | 240.32 | 682.494101 | 412.783 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.653395 |
| util_keylet | DID (own Env, featureDID added) | 4 | 1200 | 216.709 | 473.814471 | 389.173 | HF | 110 | 230 | HF (E2E noisy) |
| etxn_reserve | direct (1st call) | 1 | 1 | 42 | - | 214.464 | HF | 56 | 150 | HF (capped/one-shot): error path after 1st call is trivial (design review B) |
| hook_again | direct (1st call, strong pass) | 1 | 1 | 62 | - | 234.464 | HF | 62 | 260 | HF (capped/one-shot): error path after 1st call is trivial (design review B) |

## Apply-time ledger cost (not charged by HOOK_API_COST)

Per created / modified hook-state entry on this platform; per ledger entry, node-store dependent, not per API call (DESIGN §2.1).

| variant | E2E (ns/call) | HF (ns/call) | (E2E - HF) ns/entry | path |
|---|---|---|---|---|
| state_set: 32B, modify (fixed keys) | 7258.848856 | 2961.66 | 4297.185090 | modify |
| state_set: 32B, create (fresh keys, salt=rep) | 23306.193369 | 2218.03 | 21088.164602 | create |
| state_set: 256B | 7621.109967 | 3533.48 | 4087.626201 | modify |
| state_set: 4KiB (ExtendedHookState) | 13063.243300 | 4320.93 | 8742.309534 | modify |
| state_foreign_set: write, K=1 (first call, grant scan) | - | 16006.5 | - | modify |
| state_foreign_set: write, K=200 (grant cached after 1st) | 7007.322015 | 3156.22 | 3851.103249 | modify |

## Terminal APIs (accept / rollback)

| api | calls | ns/call (min) | ns/call (mean) | t_api (ns, from mean) | cost (proposed) | cost (current) | exec.ns diff vs noexit |
|---|---|---|---|---|---|---|---|

`noexit` (hook returns 0 without calling accept/rollback/exit): mean exec.ns = 26014.2 over 200/200 reps

| accept | 1 | 41 | 83.53 | 255.994 | 67 | 150 | -11381.8 |
| rollback | 1 | 41.5 | 80.9275 | 253.391 | 67 | 180 | 1086.63 |

## Table value per API (DESIGN §2.4 rule)

| api | rule | rows | table cost |
|---|---|---|---|
| accept | max (single size, multiple paths) | 1 | 67 |
| emit | max (single size, multiple paths) | 2 | 2100 |
| etxn_burden | max (single size, multiple paths) | 1 | 76 |
| etxn_details | max (single size, multiple paths) | 1 | 150 |
| etxn_fee_base | max (single size, multiple paths) | 2 | 1100 |
| etxn_generation | max (single size, multiple paths) | 1 | 59 |
| etxn_nonce | max (single size, multiple paths) | 1 | 120 |
| etxn_reserve | max (single size, multiple paths) | 1 | 56 |
| fee_base | max (single size, multiple paths) | 1 | 71 |
| float_compare | mode: max | 2 | 69 |
| float_divide | max (single size, multiple paths) | 1 | 86 |
| float_int | max (single size, multiple paths) | 1 | 63 |
| float_invert | max (single size, multiple paths) | 1 | 63 |
| float_log | max (single size, multiple paths) | 1 | 65 |
| float_mantissa | max (single size, multiple paths) | 1 | 63 |
| float_mulratio | max (single size, multiple paths) | 1 | 71 |
| float_multiply | max (single size, multiple paths) | 1 | 87 |
| float_negate | max (single size, multiple paths) | 1 | 63 |
| float_one | max (single size, multiple paths) | 1 | 49 |
| float_root | max (single size, multiple paths) | 1 | 71 |
| float_set | max (single size, multiple paths) | 1 | 70 |
| float_sign | max (single size, multiple paths) | 1 | 63 |
| float_sto | mode: max | 3 | 94 |
| float_sto_set | max (single size, multiple paths) | 1 | 70 |
| float_sum | max (single size, multiple paths) | 1 | 73 |
| hook_account | max (single size, multiple paths) | 1 | 65 |
| hook_again | max (single size, multiple paths) | 1 | 62 |
| hook_hash | mode: max | 2 | 73 |
| hook_param | max (single size, multiple paths) | 2 | 86 |
| hook_param_set | max (single size, multiple paths) | 1 | 92 |
| hook_pos | max (single size, multiple paths) | 1 | 49 |
| hook_skip | max (single size, multiple paths) | 1 | 73 |
| ledger_keylet | max (single size, multiple paths) | 1 | 110 |
| ledger_last_hash | max (single size, multiple paths) | 1 | 65 |
| ledger_last_time | max (single size, multiple paths) | 1 | 63 |
| ledger_nonce | max (single size, multiple paths) | 1 | 94 |
| ledger_seq | max (single size, multiple paths) | 1 | 63 |
| meta_slot | max (single size, multiple paths) | 1 | 63 |
| otxn_burden | max (single size, multiple paths) | 1 | 80 |
| otxn_field | size: reference (DESIGN §2.4) | 3 | 82 |
| otxn_generation | max (single size, multiple paths) | 1 | 74 |
| otxn_id | mode: max | 2 | 64 |
| otxn_param | mode: max | 2 | 97 |
| otxn_slot | size: reference (DESIGN §2.4) | 3 | 150 |
| otxn_type | max (single size, multiple paths) | 1 | 71 |
| prepare | max (single size, multiple paths) | 2 | 9500 |
| rollback | max (single size, multiple paths) | 1 | 67 |
| slot | size: reference (DESIGN §2.4) | 2 | 150 |
| slot_clear | max (single size, multiple paths) | 1 | 92 |
| slot_count | max (single size, multiple paths) | 1 | 64 |
| slot_float | max (single size, multiple paths) | 1 | 71 |
| slot_set | max (single size, multiple paths) | 1 | 380 |
| slot_size | max (single size, multiple paths) | 1 | 120 |
| slot_subarray | max (single size, multiple paths) | 1 | 65 |
| slot_subfield | max (single size, multiple paths) | 1 | 71 |
| slot_type | mode: max | 2 | 67 |
| state | size: reference (DESIGN §2.4) | 3 | 520 |
| state_foreign | mode: max | 2 | 500 |
| state_foreign_set | mode: max | 2 | 4200 |
| state_set | size: reference (DESIGN §2.4) | 4 | 930 |
| sto_emplace | size: reference (DESIGN §2.4) | 3 | 170 |
| sto_erase | size: reference (DESIGN §2.4) | 3 | 120 |
| sto_subarray | size: reference (DESIGN §2.4) | 2 | 110 |
| sto_subfield | size: reference (DESIGN §2.4) | 3 | 150 |
| sto_validate | size: reference (DESIGN §2.4) | 3 | 200 |
| trace | mode: max | 2 | 270 |
| trace_float | max (single size, multiple paths) | 1 | 210 |
| trace_num | max (single size, multiple paths) | 1 | 170 |
| util_accid | max (single size, multiple paths) | 1 | 140 |
| util_keylet | mode: max | 25 | 110 |
| util_raddr | max (single size, multiple paths) | 1 | 120 |
| util_sha512h | size: geomean(ref, largest) [>10x] | 3 | 759 |
| util_verify | mode: max | 2 | 6900 |
| xpop_slot | max (single size, multiple paths) | 1 | 11000 |
| _g | loop-head guard: fit intercept G / t_instr | 6 | 71 |

## Proposed HOOK_API_COST block

In include/xrpl/hook/hook_api.macro declaration order; amendment column preserved from that file. An API with no measured row this run keeps its current value, annotated `// unmeasured`. `_g` is the baseline fit intercept G over t_instr (not charged by the guard checker today).

```
HOOK_API_COST(_g, 71, uint256{})
HOOK_API_COST(accept, 67, uint256{})
HOOK_API_COST(rollback, 67, uint256{})
HOOK_API_COST(util_raddr, 120, uint256{})
HOOK_API_COST(util_accid, 140, uint256{})
HOOK_API_COST(util_verify, 6900, uint256{})  // ARM SHA-512 hardware acceleration; x86-64 run required before adoption (DESIGN §5)
HOOK_API_COST(util_sha512h, 759, uint256{})  // ARM SHA-512 hardware acceleration; x86-64 run required before adoption (DESIGN §5)
HOOK_API_COST(util_keylet, 110, uint256{})
HOOK_API_COST(sto_validate, 200, uint256{})
HOOK_API_COST(sto_subfield, 150, uint256{})
HOOK_API_COST(sto_subarray, 110, uint256{})
HOOK_API_COST(sto_emplace, 170, uint256{})
HOOK_API_COST(sto_erase, 120, uint256{})
HOOK_API_COST(etxn_burden, 76, uint256{})
HOOK_API_COST(etxn_details, 150, uint256{})
HOOK_API_COST(etxn_fee_base, 1100, uint256{})
HOOK_API_COST(etxn_reserve, 56, uint256{})
HOOK_API_COST(etxn_generation, 59, uint256{})
HOOK_API_COST(etxn_nonce, 120, uint256{})
HOOK_API_COST(emit, 2100, uint256{})
HOOK_API_COST(float_set, 70, uint256{})
HOOK_API_COST(float_multiply, 87, uint256{})
HOOK_API_COST(float_mulratio, 71, uint256{})
HOOK_API_COST(float_negate, 63, uint256{})
HOOK_API_COST(float_compare, 69, uint256{})
HOOK_API_COST(float_sum, 73, uint256{})
HOOK_API_COST(float_sto, 94, uint256{})
HOOK_API_COST(float_sto_set, 70, uint256{})
HOOK_API_COST(float_invert, 63, uint256{})
HOOK_API_COST(float_divide, 86, uint256{})
HOOK_API_COST(float_one, 49, uint256{})
HOOK_API_COST(float_mantissa, 63, uint256{})
HOOK_API_COST(float_sign, 63, uint256{})
HOOK_API_COST(float_int, 63, uint256{})
HOOK_API_COST(float_log, 65, uint256{})
HOOK_API_COST(float_root, 71, uint256{})
HOOK_API_COST(fee_base, 71, uint256{})
HOOK_API_COST(ledger_seq, 63, uint256{})
HOOK_API_COST(ledger_last_time, 63, uint256{})
HOOK_API_COST(ledger_last_hash, 65, uint256{})
HOOK_API_COST(ledger_nonce, 94, uint256{})
HOOK_API_COST(ledger_keylet, 110, uint256{})
HOOK_API_COST(hook_account, 65, uint256{})
HOOK_API_COST(hook_hash, 73, uint256{})
HOOK_API_COST(hook_param_set, 92, uint256{})
HOOK_API_COST(hook_param, 86, uint256{})
HOOK_API_COST(hook_again, 62, uint256{})
HOOK_API_COST(hook_skip, 73, uint256{})
HOOK_API_COST(hook_pos, 49, uint256{})
HOOK_API_COST(slot, 150, uint256{})
HOOK_API_COST(slot_clear, 92, uint256{})
HOOK_API_COST(slot_count, 64, uint256{})
HOOK_API_COST(slot_set, 380, uint256{})
HOOK_API_COST(slot_size, 120, uint256{})
HOOK_API_COST(slot_subarray, 65, uint256{})
HOOK_API_COST(slot_subfield, 71, uint256{})
HOOK_API_COST(slot_type, 67, uint256{})
HOOK_API_COST(slot_float, 71, uint256{})
HOOK_API_COST(state_set, 930, uint256{})
HOOK_API_COST(state_foreign_set, 4200, uint256{})
HOOK_API_COST(state, 520, uint256{})
HOOK_API_COST(state_foreign, 500, uint256{})
HOOK_API_COST(trace, 270, uint256{})
HOOK_API_COST(trace_num, 170, uint256{})
HOOK_API_COST(trace_float, 210, uint256{})
HOOK_API_COST(otxn_burden, 80, uint256{})
HOOK_API_COST(otxn_field, 82, uint256{})
HOOK_API_COST(otxn_generation, 74, uint256{})
HOOK_API_COST(otxn_id, 64, uint256{})
HOOK_API_COST(otxn_type, 71, uint256{})
HOOK_API_COST(otxn_slot, 150, uint256{})
HOOK_API_COST(otxn_param, 97, uint256{})
HOOK_API_COST(meta_slot, 63, uint256{})
HOOK_API_COST(xpop_slot, 11000, uint256{})
HOOK_API_COST(prepare, 9500, uint256{})
```

## Deferred (not measured this run)

* `util_keylet` -- every keylet_type with a dedicated constant in hookapi.h is covered except BRIDGE, XCHAIN_OWNED_CLAIM_ID, XCHAIN_OWNED_CREATE_ACCOUNT_CLAIM_ID, MPTOKEN_ISSUANCE, MPTOKEN, CREDENTIAL, and PERMISSIONED_DOMAIN: applyHook.cpp's util_keylet unconditionally returns INVALID_ARGUMENT for these (not measurable regardless of amendment state, see the comment at applyHook.cpp's keylet_code::BRIDGE case); TICKET (13) has no case in util_keylet's switch at all and is not accepted. AMM and DID are both measured (own Env with featureAMM/featureDID added, since both are Supported::no and so not in supported_amendments()).

## Notes

* HOOK_API_COST(_g) is dead: loop-head guards are consumed by the checker without being counted (design review sec A3). t_call/t_instr above still reflect the real cost of `_g`, reported for completeness.
* HOOK_API_COST is in static worst-case instruction units; t_instr is measured against the runtime instruction count, which is conservative (design review sec A4).
