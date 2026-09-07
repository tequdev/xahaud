# HookAPICost results

## Header

* CPU: Apple M3 Ultra
* OS: Darwin Yu-Mac-Studio-m3.local 25.5.0 Darwin Kernel Version 25.5.0: Mon Apr 27 20:39:42 PDT 2026; root:xnu-12377.121.6~2/RELEASE_ARM64_T6031 arm64 arm Darwin
* Compiler: Apple LLVM 16.0.0 (clang-1600.0.26.6)
* Build type: Release (hook_cost_bench=ON)
* WasmEdge: 0.11.2
* git SHA: 0a2462075dde0e1ae4643b9c82cc86f8f1c08cd0
* t_clk (mean nowNs() pair overhead): 15 ns
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
| base1 | 130 | 1300 | 4625 | 45575 | 35 | 444.48 | 399.892 | 43.0377 | 5.52873 |
| base2 | 70 | 700 | 3855 | 37875 | 54 | 486.641 | 487.83 | 62.0699 | 3.94696 |
| base4 | 40 | 400 | 4075 | 40075 | 100 | 766.553 | 690.281 | 108.122 | 2.60354 |
| base8 | 25 | 250 | 4775 | 47075 | 188 | 966.293 | 1048.33 | 196.195 | 1.86352 |
| base16 | 5 | 50 | 1895 | 18275 | 364 | 1610.18 | 1826.84 | 372.961 | 1.50484 |
| base64 | 3 | 38 | 4335 | 54035 | 1420 | 4919.03 | 6208.34 | 1429.26 | 1.1552 |

Fitted (env.close() wall-clock, calibration channel): t_instr = 3.21127 ns, G (_g total per-iteration cost) = 375.602 ns, SE(G) = 31.5344 ns, R^2 = 0.998948
Fitted (exec.ns, wasm-window only, comparison): t_instr = 4.18809 ns, G = 268.509 ns, SE(G) = 9.97702 ns, R^2 = 0.999938

### Sensitivity baselines (t_instr alone, using G)

| baseline | dI | dTw env.close (ns) | t_instr alone (ns) |
|---|---|---|---|
| basei64 | 194 | 1008.78 | 3.26381 |
| basemem | 118 | 742.513 | 3.10942 |

* t_instr = 3.21127 ns
* G (loop-head _g total per-iteration cost) = 375.602 ns
* R^2 (baseline fit) = 0.998948
* t_call (0-arg boundary, from E2E(hook_pos) - (M_pos - 2*t_clk)) = 181.246 ns
* O_g (the `_g` 2-arg call's own G above) = 375.602 ns vs t_call (0-arg hook_pos) = 181.246 ns -- host-call boundary grows roughly 97.1782 ns per argument

## Per-API results

| api | variant | K | calls | ns/call (M) | E2E (ns) | HF (ns) | used | cost (proposed) | cost (current) | notes |
|---|---|---|---|---|---|---|---|---|---|---|
| hook_pos | K=4 | 4 | 3400 | 14.4794 | 165.724920 | 165.725 | HF | 52 | 40 | HF (E2E noisy) |
| fee_base | K=4 | 4 | 1800 | 69.7339 | 293.853174 | 220.979 | HF | 69 | 70 | HF (E2E noisy); E2E/HF ratio 1.329776 |
| ledger_seq | K=4 | 4 | 1800 | 72.2556 | 241.332186 | 223.501 | HF | 70 | 140 | HF (E2E noisy) |
| float_one | K=4 | 4 | 1800 | 15.0417 | 186.830856 | 166.287 | HF | 52 | 20 | HF (E2E noisy) |
| otxn_type | K=4 | 4 | 1800 | 71.2494 | 215.277865 | 222.495 | HF | 70 | 130 | HF (E2E noisy) |
| etxn_generation | K=4 | 4 | 1800 | 59.9817 | 214.351227 | 211.227 | HF | 66 | 130 | HF (E2E noisy) |
| util_sha512h | 32B | 1 | 1000 | 159.79 | 232.067478 | 311.036 | HF | 97 | 340 | HF (E2E noisy); E2E/HF ratio 0.746112 |
| util_sha512h | 1KiB | 1 | 1000 | 715.249 | 947.991922 | 866.495 | HF | 270 | 340 | HF (E2E noisy) |
| util_sha512h | 16KiB | 1 | 1000 | 9579.49 | 10009.057478 | 9730.73 | E2E | 3200 | 340 |  |
| state | 32B | 1 | 200 | 1777.72 | 2179.838532 | 1928.97 | HF | 610 | 1700 | HF (E2E noisy) |
| state | 256B | 1 | 200 | 1815.83 | 2634.699643 | 1967.07 | E2E | 830 | 1700 | E2E/HF ratio 1.339403 |
| state_set | 32B, modify (fixed keys) | 1 | 200 | 623.335 | 7486.810592 | 3157.29 | HF | 990 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.371281; review #6: modify path |
| state_set | 32B, create (fresh keys, salt=rep) | 1 | 200 | 614.62 | 23885.604059 | 2235.24 | HF | 700 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 10.685921; review #6: create path |
| state_set | 256B | 1 | 200 | 625.62 | 7679.171703 | 3173.95 | HF | 990 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.419436 |
| util_raddr | K=4 | 4 | 1200 | 293.755 | 556.689868 | 445.001 | E2E | 180 | 980 |  |
| util_accid | K=4 | 4 | 1200 | 283.503 | 466.758387 | 434.749 | HF | 140 | 690 | HF (E2E noisy) |
| util_keylet | ACCOUNT | 4 | 1200 | 170.118 | 465.787202 | 321.363 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.449411 |
| util_keylet | CHILD | 4 | 1200 | 80 | 363.741832 | 231.246 | HF | 73 | 230 | HF (E2E noisy); E2E/HF ratio 1.572968 |
| util_keylet | ESCROW | 4 | 1200 | 190.936 | 517.137202 | 342.181 | E2E | 170 | 230 | E2E/HF ratio 1.511296 |
| util_keylet | LINE | 4 | 1200 | 193.157 | 430.602017 | 344.402 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | AMENDMENTS | 4 | 1200 | 80.1175 | 367.060351 | 231.363 | HF | 73 | 230 | HF (E2E noisy); E2E/HF ratio 1.586513 |
| util_keylet | QUALITY | 4 | 1200 | 80.7675 | 406.990906 | 232.013 | HF | 73 | 230 | HF (E2E noisy); E2E/HF ratio 1.754173; AMENDMENTS's case also covers FEES/NEGATIVE_UNL/EMITTED_DIR (identical switch case); AMM/BRIDGE/XCHAIN_*/MPTOKEN_*/CREDENTIAL/PERMISSIONED_DOMAIN not built (complex multi-part operands -- asset pairs, bridge specs); every other keylet_type is covered below |
| util_keylet | HOOK | 4 | 1200 | 174.769 | 394.529795 | 326.015 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | HOOK_STATE | 4 | 1200 | 174.063 | 450.277017 | 325.309 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.384152 |
| util_keylet | SKIP | 4 | 1200 | 77.4983 | 345.339980 | 228.744 | HF | 72 | 230 | HF (E2E noisy); E2E/HF ratio 1.509724 |
| util_keylet | OFFER | 4 | 1200 | 182.775 | 390.054795 | 334.021 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | SIGNERS | 4 | 1200 | 185.647 | 444.104795 | 336.892 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.318240 |
| util_keylet | CHECK | 4 | 1200 | 184.107 | 414.476091 | 335.353 | E2E | 130 | 230 |  |
| util_keylet | DEPOSIT_PREAUTH | 4 | 1200 | 179.739 | 411.928869 | 330.985 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | UNCHECKED | 4 | 1200 | 81.3492 | 339.205721 | 232.595 | HF | 73 | 230 | HF (E2E noisy); E2E/HF ratio 1.458355 |
| util_keylet | OWNER_DIR | 4 | 1200 | 178.632 | 445.146462 | 329.878 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.349428 |
| util_keylet | PAGE | 4 | 1200 | 169.088 | 521.651091 | 320.333 | E2E | 170 | 230 | E2E/HF ratio 1.628465 |
| util_keylet | PAYCHAN | 4 | 1200 | 192.546 | 447.076091 | 343.791 | E2E | 140 | 230 | E2E/HF ratio 1.300429 |
| util_keylet | EMITTED_TXN | 4 | 1200 | 176.961 | 507.763128 | 328.206 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.547085 |
| util_keylet | NFT_OFFER | 4 | 1200 | 184.537 | 397.614980 | 335.783 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | HOOK_DEFINITION | 4 | 1200 | 180.171 | 473.039980 | 331.416 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.427328 |
| util_keylet | HOOK_STATE_DIR | 4 | 1200 | 215.553 | 386.543684 | 366.798 | HF | 120 | 230 | HF (E2E noisy) |
| util_keylet | CRON | 4 | 1200 | 218.366 | 468.526091 | 369.611 | HF | 120 | 230 | HF (E2E noisy) |
| util_keylet | ORACLE | 4 | 1200 | 230.316 | 521.150165 | 381.561 | HF | 120 | 230 | HF (E2E noisy); E2E/HF ratio 1.365836 |
| etxn_burden | K=4 | 4 | 1200 | 123.44 | 329.448853 | 274.686 | HF | 86 | 260 | HF (E2E noisy) |
| otxn_burden | K=4 | 4 | 1200 | 124.859 | 278.818511 | 276.105 | HF | 86 | 260 | HF (E2E noisy) |
| otxn_generation | K=4 | 4 | 1200 | 126.288 | 302.121288 | 277.534 | HF | 87 | 280 | HF (E2E noisy) |
| ledger_last_time | K=4 | 4 | 1200 | 71.8767 | 315.484038 | 223.122 | HF | 70 | 110 | HF (E2E noisy); E2E/HF ratio 1.413952 |
| ledger_last_hash | K=4 | 4 | 1200 | 76.3558 | 251.884638 | 227.601 | HF | 71 | 210 | HF (E2E noisy) |
| hook_account | K=4 | 4 | 1200 | 78.5458 | 262.687416 | 229.791 | HF | 72 | 140 | HF (E2E noisy) |
| hook_hash | hook_no=0 | 4 | 1200 | 105.294 | 284.398364 | 256.54 | HF | 80 | 340 | HF (E2E noisy) |
| hook_hash | hook_no=-1 | 4 | 1200 | 78.8883 | 310.941883 | 230.134 | HF | 72 | 340 | HF (E2E noisy); E2E/HF ratio 1.351135 |
| otxn_id | flags=0 | 4 | 1200 | 78.6733 | 309.899290 | 229.919 | HF | 72 | 450 | HF (E2E noisy); E2E/HF ratio 1.347864 |
| otxn_id | flags=1 | 4 | 1200 | 73.2625 | 313.951142 | 224.508 | HF | 70 | 450 | HF (E2E noisy); E2E/HF ratio 1.398396 |
| float_multiply | K=4 | 4 | 1200 | 131.887 | 247.242259 | 283.132 | HF | 89 | 240 | HF (E2E noisy) |
| float_mulratio | K=4 | 4 | 1200 | 101.043 | 344.099341 | 252.288 | HF | 79 | 390 | HF (E2E noisy); E2E/HF ratio 1.363915 |
| float_negate | K=4 | 4 | 1200 | 72.6383 | 243.085015 | 223.884 | HF | 70 | 160 | HF (E2E noisy) |
| float_compare | COMPARE_EQUAL | 4 | 1200 | 96.0675 | 291.189105 | 247.313 | HF | 78 | 140 | HF (E2E noisy) |
| float_compare | COMPARE_LESS|COMPARE_EQUAL | 4 | 1200 | 97.74 | 309.398364 | 248.986 | HF | 78 | 140 | HF (E2E noisy) |
| float_sum | K=4 | 4 | 1200 | 101.832 | 332.658926 | 253.078 | HF | 79 | 350 | HF (E2E noisy); E2E/HF ratio 1.314452 |
| float_invert | K=4 | 4 | 1200 | 68.0133 | 281.201681 | 219.259 | HF | 69 | 230 | HF (E2E noisy) |
| float_divide | K=4 | 4 | 1200 | 121.426 | 360.745963 | 272.671 | HF | 85 | 280 | HF (E2E noisy); E2E/HF ratio 1.323007 |
| float_mantissa | K=4 | 4 | 1200 | 71.5342 | 332.860941 | 222.78 | E2E | 110 | 170 | E2E/HF ratio 1.494126 |
| float_sign | K=4 | 4 | 1200 | 69.1667 | 274.642422 | 220.412 | HF | 69 | 80 | HF (E2E noisy) |
| float_int | K=4 | 4 | 1200 | 72.1175 | 229.447652 | 223.363 | HF | 70 | 100 | HF (E2E noisy) |
| float_log | K=4 | 4 | 1200 | 81.5083 | 280.815570 | 232.754 | HF | 73 | 100 | HF (E2E noisy) |
| float_root | K=4 | 4 | 1200 | 106.814 | 255.497815 | 258.06 | HF | 81 | 190 | HF (E2E noisy) |
| float_set | K=4 | 4 | 1200 | 97.25 | 291.839481 | 248.496 | HF | 78 | 110 | HF (E2E noisy) |
| float_sto | XRP | 4 | 1200 | 99.7258 | 345.966069 | 250.971 | HF | 79 | 230 | HF (E2E noisy); E2E/HF ratio 1.378508 |
| float_sto | IOU | 4 | 1200 | 108.755 | 322.431810 | 260.001 | HF | 81 | 230 | HF (E2E noisy) |
| float_sto | short | 4 | 1200 | 98.3292 | 269.152180 | 249.575 | HF | 78 | 230 | HF (E2E noisy) |
| float_sto_set | K=4 | 4 | 1200 | 88.1125 | 351.909852 | 239.358 | HF | 75 | 140 | HF (E2E noisy); E2E/HF ratio 1.470224 |
| trace | 32B | 4 | 1200 | 455.758 | 676.172276 | 607.004 | HF | 190 | 100 | HF (E2E noisy); default journal level: early-returns on !j.trace() (design review B) |
| trace | 1KiB hex | 4 | 1200 | 713.495 | 1000.978757 | 864.741 | HF | 270 | 100 | HF (E2E noisy) |
| trace_num | K=4 | 4 | 1200 | 414.767 | 694.870709 | 566.012 | E2E | 220 | 100 |  |
| trace_float | K=4 | 4 | 1200 | 575.228 | 840.272601 | 726.474 | E2E | 270 | 100 |  |
| otxn_param | 32B | 4 | 1201 | 209.113 | 426.325979 | 360.359 | HF | 120 | 830 | HF (E2E noisy) |
| otxn_param | 256B | 4 | 1201 | 204.693 | 390.408387 | 355.938 | HF | 120 | 830 | HF (E2E noisy) |
| hook_param | 32B | 4 | 1200 | 108.335 | 358.116720 | 259.581 | HF | 81 | 510 | HF (E2E noisy); E2E/HF ratio 1.379598 |
| hook_param | 256B | 4 | 1200 | 121.001 | 395.115794 | 272.246 | HF | 85 | 510 | HF (E2E noisy); E2E/HF ratio 1.451317 |
| otxn_field | sfAccount(20B) | 1 | 300 | 116.393 | 414.903713 | 267.639 | HF | 84 | 460 | HF (E2E noisy); E2E/HF ratio 1.550237 |
| otxn_field | 1KiB Blob | 1 | 300 | 153.04 | 292.529639 | 304.286 | HF | 95 | 460 | HF (E2E noisy) |
| otxn_field | 16KiB Blob | 1 | 300 | 576.383 | 781.107417 | 727.629 | HF | 230 | 460 | HF (E2E noisy) |
| otxn_slot | small tx | 1 | 300 | 366.257 | 780.896631 | 517.502 | HF | 170 | 310 | HF (E2E noisy); E2E/HF ratio 1.508973 |
| otxn_slot | 1KiB Blob | 1 | 300 | 417.357 | 458.211446 | 568.602 | HF | 180 | 310 | HF (E2E noisy) |
| otxn_slot | 16KiB Blob | 1 | 300 | 588.46 | 839.537372 | 739.706 | HF | 240 | 310 | HF (E2E noisy) |
| slot | 1KiB Blob | 1 | 300 | 420.403 | 526.325935 | 571.649 | HF | 180 | 1400 | HF (E2E noisy) |
| slot | 16KiB Blob | 1 | 300 | 1227.92 | 1433.425935 | 1379.17 | HF | 430 | 1400 | HF (E2E noisy) |
| slot_size | K=1 | 1 | 300 | 297.36 | 519.789224 | 448.606 | HF | 140 | 330 | HF (E2E noisy) |
| slot_type | flags=0 | 1 | 300 | 78.47 | 148.160571 | 229.716 | HF | 72 | 210 | HF (E2E noisy); E2E/HF ratio 0.644974 |
| slot_type | flags=1 | 1 | 300 | 92.6533 | 345.274246 | 243.899 | HF | 76 | 210 | HF (E2E noisy); E2E/HF ratio 1.415645 |
| slot_count | 3 Memos | 1 | 300 | 78.07 | 212.841075 | 229.316 | HF | 72 | 230 | HF (E2E noisy) |
| slot_subfield | sfAccount | 1 | 300 | 107.63 | 111.355565 | 258.876 | HF | 81 | 220 | HF (E2E noisy); E2E/HF ratio 0.430151 |
| slot_float | sfAmount (own tx, Payment) | 1 | 300 | 107.78 | 230.896631 | 259.026 | HF | 81 | 150 | HF (E2E noisy) |
| slot_subarray | Memos[0] | 1 | 300 | 81.94 | 138.670380 | 233.186 | HF | 73 | 330 | HF (E2E noisy); E2E/HF ratio 0.594678 |
| slot_set | 34B keylet | 1 | 300 | 1426.68 | 1670.155565 | 1577.92 | HF | 500 | 350 | HF (E2E noisy) |
| slot_clear | K=1 | 1 | 300 | 201.127 | 340.825438 | 352.372 | HF | 110 | 230 | HF (E2E noisy) |
| sto_validate | ~31B | 1 | 300 | 187.497 | 357.899521 | 338.742 | HF | 110 | 350 | HF (E2E noisy) |
| sto_validate | ~tx (250B) | 1 | 300 | 546.033 | 797.466676 | 697.279 | HF | 220 | 350 | HF (E2E noisy) |
| sto_validate | ~4KiB (Blob) | 1 | 300 | 668.317 | 1177.096305 | 819.562 | E2E | 370 | 350 | E2E/HF ratio 1.436250 |
| sto_subfield | ~31B | 1 | 300 | 144.16 | 180.303062 | 295.406 | HF | 92 | 340 | HF (E2E noisy); E2E/HF ratio 0.610358 |
| sto_subfield | ~tx (250B) | 1 | 300 | 421.66 | 509.073920 | 572.906 | HF | 180 | 340 | HF (E2E noisy) |
| sto_subfield | ~4KiB (Blob) | 1 | 300 | 511.097 | 781.292439 | 662.342 | HF | 210 | 340 | HF (E2E noisy) |
| sto_subarray | ~tx (250B) | 1 | 300 | 235.43 | 523.114661 | 386.676 | HF | 130 | 290 | HF (E2E noisy); E2E/HF ratio 1.352852; no small-object point (deferred); single-point table value |
| sto_subarray | 3 Memos, one ~1KiB | 1 | 300 | 259.03 | 340.555402 | 410.276 | HF | 130 | 290 | HF (E2E noisy) |
| sto_emplace | ~31B | 1 | 300 | 332.24 | 703.876485 | 483.486 | HF | 160 | 980 | HF (E2E noisy); E2E/HF ratio 1.455838 |
| sto_emplace | ~tx (250B) | 1 | 300 | 450.283 | 673.695492 | 601.529 | HF | 190 | 980 | HF (E2E noisy) |
| sto_emplace | ~4KiB (Blob) | 1 | 300 | 657.8 | 924.002899 | 809.046 | HF | 260 | 980 | HF (E2E noisy) |
| sto_erase | ~31B | 1 | 300 | 209.72 | 446.873107 | 360.966 | HF | 120 | 970 | HF (E2E noisy) |
| sto_erase | ~tx (250B) | 1 | 300 | 290.013 | 338.295817 | 441.259 | HF | 140 | 970 | HF (E2E noisy); E2E/HF ratio 0.766661 |
| sto_erase | ~4KiB (Blob) | 1 | 300 | 442.237 | 585.518039 | 593.482 | HF | 190 | 970 | HF (E2E noisy) |
| ledger_nonce | K=200/exec | 1 | 200 | 198.955 | 168.887209 | 350.201 | HF | 110 | 170 | HF (E2E noisy); E2E/HF ratio 0.482259 |
| etxn_nonce | K=200/exec | 1 | 200 | 251.45 | 374.448320 | 402.696 | HF | 130 | 230 | HF (E2E noisy) |
| util_verify | ed25519 (passing) | 1 | 301 | 25476.3 | 26614.225447 | 25627.6 | E2E | 8300 | 24000 |  |
| util_verify | secp256k1 (passing) | 1 | 301 | 20547.7 | 21040.303225 | 20699 | E2E | 6600 | 24000 |  |
| hook_param_set | K=16/exec (cap) | 1 | 16 | 192.875 | 247.361548 | 344.121 | HF | 110 | 370 | HF (E2E noisy); E2E/HF ratio 0.718822 |
| meta_slot | K=200/exec, weak/AAW pass | 1 | 202 | 79.8267 | - | 231.072 | HF | 72 | 220 | HF (capped/one-shot) |
| prepare | min Payment spec | 1 | 250 | 34771.3 | 35554.170046 | 34922.6 | E2E | 12000 | 36000 | reference size (minimal Payment) |
| prepare | 1KiB ttINVOKE+sfBlob | 1 | 301 | 36126.8 | 36309.225772 | 36278.1 | E2E | 12000 | 36000 | 1KiB sfBlob variant (Phase 3 item 3) |
| etxn_fee_base | 1KiB ttINVOKE+sfBlob | 1 | 302 | 3832.22 | 4322.903876 | 3983.46 | HF | 1300 | 4600 | HF (E2E noisy); 1KiB sfBlob variant, direct call (not via emit) -- reference (min Payment) value comes from emit_min_k200's loop, see below |
| ledger_keylet | full range | 1 | 300 | 270.137 | 537.062484 | 421.382 | HF | 140 | 300 | HF (E2E noisy); lower bound: near-empty JTX ledger (design review F3) |
| state | 4KiB (ExtendedHookState) | 1 | 200 | 2493.53 | 2988.344413 | 2644.78 | HF | 830 | 1700 | HF (E2E noisy) |
| state_set | 4KiB (ExtendedHookState) | 1 | 200 | 813.14 | 12739.366147 | 5000.01 | HF | 1600 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.547870 |
| state_foreign | read 32B (no grant needed) | 1 | 200 | 1806.91 | 2425.960429 | 1958.16 | HF | 610 | 1700 | HF (E2E noisy) |
| state_foreign | read 256B (no grant needed) | 1 | 200 | 1823.54 | 2442.860429 | 1974.79 | HF | 620 | 1700 | HF (E2E noisy) |
| state_foreign_set | write, K=1 (first call, grant scan) | 1 | 1 | 10375 | - | 18151.2 | HF | 5700 | 3400 | HF (capped/one-shot) |
| state_foreign_set | write, K=200 (grant cached after 1st) | 1 | 200 | 703.13 | 7453.971540 | 3580.21 | HF | 1200 | 3400 | HF (ledger-write cost reported separately); E2E/HF ratio 2.081993 |
| emit | K=200/exec, min Payment, own nonce+details+fee_base | 1 | 200 | 7961.66 | - | 8112.91 | HF | 2600 | 8700 | HF (undecomposable body) |
| etxn_details | inside emit_min_k200's loop | 1 | 200 | 367.71 | - | 518.956 | HF | 170 | 470 | HF (undecomposable body) |
| etxn_fee_base | inside emit_min_k200's loop | 1 | 200 | 4101.68 | - | 4252.92 | HF | 1400 | 4600 | HF (undecomposable body) |
| emit | K=200/exec, 1KiB ttINVOKE+sfBlob | 1 | 200 | 7870.43 | - | 8021.67 | HF | 2500 | 8700 | HF (undecomposable body) |
| hook_skip | alternating scan/erase (2-hook chain) | 1 | 300 | 115.547 | 485.055076 | 266.792 | HF | 84 | 170 | HF (E2E noisy); E2E/HF ratio 1.818101 |

(`xpop_slot` not observed as a call on fixture `w_regular_key` -- Import tx likely did not reach the hook as ttIMPORT; skipped)

## xpop_slot_k100 (separate Env per rep)

| api | variant | calls | ns/call | t_api (ns) | cost (proposed) | cost (current) | notes |
|---|---|---|---|---|---|---|---|
| xpop_slot | K=100/exec, min over 2 rep(s) (ttIMPORT, one fixture per fresh Env) | 100 | 30649.6 | 30800.8 | 9600 | 37000 | HF (capped/one-shot): anti-replay caps reps to the number of distinct fixtures, no N1/N2 E2E |
| util_keylet | AMM (own Env, featureAMM added) | 4 | 1201 | 248.58 | 530.988128 | 399.826 | HF | 130 | 230 | HF (E2E noisy); E2E/HF ratio 1.328048 |
| util_keylet | DID (own Env, featureDID added) | 4 | 1200 | 222.119 | 522.306647 | 373.365 | HF | 120 | 230 | HF (E2E noisy); E2E/HF ratio 1.398918 |
| etxn_reserve | direct (1st call) | 1 | 1 | 83 | - | 234.246 | HF | 73 | 150 | HF (capped/one-shot): error path after 1st call is trivial (design review B) |
| hook_again | direct (1st call, strong pass) | 1 | 1 | 62 | - | 213.246 | HF | 67 | 260 | HF (capped/one-shot): error path after 1st call is trivial (design review B) |

## Apply-time ledger cost (not charged by HOOK_API_COST)

Per created / modified hook-state entry on this platform; per ledger entry, node-store dependent, not per API call (DESIGN §2.1).

| variant | E2E (ns/call) | HF (ns/call) | (E2E - HF) ns/entry | path |
|---|---|---|---|---|
| state_set: 32B, modify (fixed keys) | 7486.810592 | 3157.29 | 4329.525084 | modify |
| state_set: 32B, create (fresh keys, salt=rep) | 23885.604059 | 2235.24 | 21650.363551 | create |
| state_set: 256B | 7679.171703 | 3173.95 | 4505.221195 | modify |
| state_set: 4KiB (ExtendedHookState) | 12739.366147 | 5000.01 | 7739.360639 | modify |
| state_foreign_set: write, K=1 (first call, grant scan) | - | 18151.2 | - | modify |
| state_foreign_set: write, K=200 (grant cached after 1st) | 7453.971540 | 3580.21 | 3873.761032 | modify |

## Terminal APIs (accept / rollback)

| api | calls | ns/call (min) | ns/call (mean) | t_api (ns, from mean) | cost (proposed) | cost (current) | exec.ns diff vs noexit |
|---|---|---|---|---|---|---|---|

`noexit` (hook returns 0 without calling accept/rollback/exit): mean exec.ns = 26498.8 over 200/200 reps

| accept | 1 | 41 | 100.76 | 252.006 | 79 | 150 | -9436.92 |
| rollback | 1 | 62 | 92.495 | 243.741 | 76 | 180 | 5314.74 |

## Table value per API (DESIGN §2.4 rule)

| api | rule | rows | table cost |
|---|---|---|---|
| accept | max (single size, multiple paths) | 1 | 79 |
| emit | max (single size, multiple paths) | 2 | 2500 |
| etxn_burden | max (single size, multiple paths) | 1 | 86 |
| etxn_details | max (single size, multiple paths) | 1 | 170 |
| etxn_fee_base | max (single size, multiple paths) | 2 | 1300 |
| etxn_generation | max (single size, multiple paths) | 1 | 66 |
| etxn_nonce | max (single size, multiple paths) | 1 | 130 |
| etxn_reserve | max (single size, multiple paths) | 1 | 73 |
| fee_base | max (single size, multiple paths) | 1 | 69 |
| float_compare | mode: max | 2 | 78 |
| float_divide | max (single size, multiple paths) | 1 | 85 |
| float_int | max (single size, multiple paths) | 1 | 70 |
| float_invert | max (single size, multiple paths) | 1 | 69 |
| float_log | max (single size, multiple paths) | 1 | 73 |
| float_mantissa | max (single size, multiple paths) | 1 | 110 |
| float_mulratio | max (single size, multiple paths) | 1 | 79 |
| float_multiply | max (single size, multiple paths) | 1 | 89 |
| float_negate | max (single size, multiple paths) | 1 | 70 |
| float_one | max (single size, multiple paths) | 1 | 52 |
| float_root | max (single size, multiple paths) | 1 | 81 |
| float_set | max (single size, multiple paths) | 1 | 78 |
| float_sign | max (single size, multiple paths) | 1 | 69 |
| float_sto | mode: max | 3 | 81 |
| float_sto_set | max (single size, multiple paths) | 1 | 75 |
| float_sum | max (single size, multiple paths) | 1 | 79 |
| hook_account | max (single size, multiple paths) | 1 | 72 |
| hook_again | max (single size, multiple paths) | 1 | 67 |
| hook_hash | mode: max | 2 | 80 |
| hook_param | max (single size, multiple paths) | 2 | 85 |
| hook_param_set | max (single size, multiple paths) | 1 | 110 |
| hook_pos | max (single size, multiple paths) | 1 | 52 |
| hook_skip | max (single size, multiple paths) | 1 | 84 |
| ledger_keylet | max (single size, multiple paths) | 1 | 140 |
| ledger_last_hash | max (single size, multiple paths) | 1 | 71 |
| ledger_last_time | max (single size, multiple paths) | 1 | 70 |
| ledger_nonce | max (single size, multiple paths) | 1 | 110 |
| ledger_seq | max (single size, multiple paths) | 1 | 70 |
| meta_slot | max (single size, multiple paths) | 1 | 72 |
| otxn_burden | max (single size, multiple paths) | 1 | 86 |
| otxn_field | size: reference (DESIGN §2.4) | 3 | 95 |
| otxn_generation | max (single size, multiple paths) | 1 | 87 |
| otxn_id | mode: max | 2 | 72 |
| otxn_param | mode: max | 2 | 120 |
| otxn_slot | size: reference (DESIGN §2.4) | 3 | 180 |
| otxn_type | max (single size, multiple paths) | 1 | 70 |
| prepare | max (single size, multiple paths) | 2 | 12000 |
| rollback | max (single size, multiple paths) | 1 | 76 |
| slot | size: reference (DESIGN §2.4) | 2 | 180 |
| slot_clear | max (single size, multiple paths) | 1 | 110 |
| slot_count | max (single size, multiple paths) | 1 | 72 |
| slot_float | max (single size, multiple paths) | 1 | 81 |
| slot_set | max (single size, multiple paths) | 1 | 500 |
| slot_size | max (single size, multiple paths) | 1 | 140 |
| slot_subarray | max (single size, multiple paths) | 1 | 73 |
| slot_subfield | max (single size, multiple paths) | 1 | 81 |
| slot_type | mode: max | 2 | 76 |
| state | size: reference (DESIGN §2.4) | 3 | 830 |
| state_foreign | mode: max | 2 | 620 |
| state_foreign_set | mode: max | 2 | 5700 |
| state_set | size: reference (DESIGN §2.4) | 4 | 990 |
| sto_emplace | size: reference (DESIGN §2.4) | 3 | 190 |
| sto_erase | size: reference (DESIGN §2.4) | 3 | 140 |
| sto_subarray | size: reference (DESIGN §2.4) | 2 | 130 |
| sto_subfield | size: reference (DESIGN §2.4) | 3 | 180 |
| sto_validate | size: reference (DESIGN §2.4) | 3 | 220 |
| trace | mode: max | 2 | 270 |
| trace_float | max (single size, multiple paths) | 1 | 270 |
| trace_num | max (single size, multiple paths) | 1 | 220 |
| util_accid | max (single size, multiple paths) | 1 | 140 |
| util_keylet | mode: max | 25 | 170 |
| util_raddr | max (single size, multiple paths) | 1 | 180 |
| util_sha512h | size: geomean(ref, largest) [>10x] | 3 | 930 |
| util_verify | mode: max | 2 | 8300 |
| xpop_slot | max (single size, multiple paths) | 1 | 9600 |

## Proposed HOOK_API_COST block

In include/xrpl/hook/hook_api.macro declaration order; amendment column preserved from that file. An API with no measured row this run keeps its current value, annotated `// unmeasured`.

```
HOOK_API_COST(_g, 220, uint256{})  // unmeasured
HOOK_API_COST(accept, 79, uint256{})
HOOK_API_COST(rollback, 76, uint256{})
HOOK_API_COST(util_raddr, 180, uint256{})
HOOK_API_COST(util_accid, 140, uint256{})
HOOK_API_COST(util_verify, 8300, uint256{})  // ARM SHA-512 hardware acceleration; x86-64 run required before adoption (DESIGN §5)
HOOK_API_COST(util_sha512h, 930, uint256{})  // ARM SHA-512 hardware acceleration; x86-64 run required before adoption (DESIGN §5)
HOOK_API_COST(util_keylet, 170, uint256{})
HOOK_API_COST(sto_validate, 220, uint256{})
HOOK_API_COST(sto_subfield, 180, uint256{})
HOOK_API_COST(sto_subarray, 130, uint256{})
HOOK_API_COST(sto_emplace, 190, uint256{})
HOOK_API_COST(sto_erase, 140, uint256{})
HOOK_API_COST(etxn_burden, 86, uint256{})
HOOK_API_COST(etxn_details, 170, uint256{})
HOOK_API_COST(etxn_fee_base, 1300, uint256{})
HOOK_API_COST(etxn_reserve, 73, uint256{})
HOOK_API_COST(etxn_generation, 66, uint256{})
HOOK_API_COST(etxn_nonce, 130, uint256{})
HOOK_API_COST(emit, 2500, uint256{})
HOOK_API_COST(float_set, 78, uint256{})
HOOK_API_COST(float_multiply, 89, uint256{})
HOOK_API_COST(float_mulratio, 79, uint256{})
HOOK_API_COST(float_negate, 70, uint256{})
HOOK_API_COST(float_compare, 78, uint256{})
HOOK_API_COST(float_sum, 79, uint256{})
HOOK_API_COST(float_sto, 81, uint256{})
HOOK_API_COST(float_sto_set, 75, uint256{})
HOOK_API_COST(float_invert, 69, uint256{})
HOOK_API_COST(float_divide, 85, uint256{})
HOOK_API_COST(float_one, 52, uint256{})
HOOK_API_COST(float_mantissa, 110, uint256{})
HOOK_API_COST(float_sign, 69, uint256{})
HOOK_API_COST(float_int, 70, uint256{})
HOOK_API_COST(float_log, 73, uint256{})
HOOK_API_COST(float_root, 81, uint256{})
HOOK_API_COST(fee_base, 69, uint256{})
HOOK_API_COST(ledger_seq, 70, uint256{})
HOOK_API_COST(ledger_last_time, 70, uint256{})
HOOK_API_COST(ledger_last_hash, 71, uint256{})
HOOK_API_COST(ledger_nonce, 110, uint256{})
HOOK_API_COST(ledger_keylet, 140, uint256{})
HOOK_API_COST(hook_account, 72, uint256{})
HOOK_API_COST(hook_hash, 80, uint256{})
HOOK_API_COST(hook_param_set, 110, uint256{})
HOOK_API_COST(hook_param, 85, uint256{})
HOOK_API_COST(hook_again, 67, uint256{})
HOOK_API_COST(hook_skip, 84, uint256{})
HOOK_API_COST(hook_pos, 52, uint256{})
HOOK_API_COST(slot, 180, uint256{})
HOOK_API_COST(slot_clear, 110, uint256{})
HOOK_API_COST(slot_count, 72, uint256{})
HOOK_API_COST(slot_set, 500, uint256{})
HOOK_API_COST(slot_size, 140, uint256{})
HOOK_API_COST(slot_subarray, 73, uint256{})
HOOK_API_COST(slot_subfield, 81, uint256{})
HOOK_API_COST(slot_type, 76, uint256{})
HOOK_API_COST(slot_float, 81, uint256{})
HOOK_API_COST(state_set, 990, uint256{})
HOOK_API_COST(state_foreign_set, 5700, uint256{})
HOOK_API_COST(state, 830, uint256{})
HOOK_API_COST(state_foreign, 620, uint256{})
HOOK_API_COST(trace, 270, uint256{})
HOOK_API_COST(trace_num, 220, uint256{})
HOOK_API_COST(trace_float, 270, uint256{})
HOOK_API_COST(otxn_burden, 86, uint256{})
HOOK_API_COST(otxn_field, 95, uint256{})
HOOK_API_COST(otxn_generation, 87, uint256{})
HOOK_API_COST(otxn_id, 72, uint256{})
HOOK_API_COST(otxn_type, 70, uint256{})
HOOK_API_COST(otxn_slot, 180, uint256{})
HOOK_API_COST(otxn_param, 120, uint256{})
HOOK_API_COST(meta_slot, 72, uint256{})
HOOK_API_COST(xpop_slot, 9600, uint256{})
HOOK_API_COST(prepare, 12000, uint256{})
```

## Deferred (not measured this run)

* `util_keylet` -- every keylet_type with a dedicated constant in hookapi.h is covered except BRIDGE, XCHAIN_OWNED_CLAIM_ID, XCHAIN_OWNED_CREATE_ACCOUNT_CLAIM_ID, MPTOKEN_ISSUANCE, MPTOKEN, CREDENTIAL, and PERMISSIONED_DOMAIN: applyHook.cpp's util_keylet unconditionally returns INVALID_ARGUMENT for these (not measurable regardless of amendment state, see the comment at applyHook.cpp's keylet_code::BRIDGE case); TICKET (13) has no case in util_keylet's switch at all and is not accepted. AMM and DID are both measured (own Env with featureAMM/featureDID added, since both are Supported::no and so not in supported_amendments()).

## Notes

* HOOK_API_COST(_g) is dead: loop-head guards are consumed by the checker without being counted (design review sec A3). t_call/t_instr above still reflect the real cost of `_g`, reported for completeness.
* HOOK_API_COST is in static worst-case instruction units; t_instr is measured against the runtime instruction count, which is conservative (design review sec A4).
