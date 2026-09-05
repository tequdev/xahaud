# HookAPICost results

## Header

* CPU: Apple M3 Ultra
* OS: Darwin Yu-Mac-Studio-m3.local 25.5.0 Darwin Kernel Version 25.5.0: Mon Apr 27 20:39:42 PDT 2026; root:xnu-12377.121.6~2/RELEASE_ARM64_T6031 arm64 arm Darwin
* Compiler: Apple LLVM 16.0.0 (clang-1600.0.26.6)
* Build type: Release (hook_cost_bench=ON)
* WasmEdge: 0.11.2
* git SHA: 07e2e64c5e0054c7b256078ad856c77e3579f14e
* t_clk (mean nowNs() pair overhead): 14 ns
* clock resolution (smallest non-zero delta, review #4): 41 ns
* hookcost_sha256:
  * accept0: 5bebf48de6b134c278de84ba7aa5b558f7938cb998228f10e9485c4c5c00df56
  * base1: 059466262aeee81918a3fbe2bc6f6d3596ad547f9a2a013b3ae543dcd905d4ac
  * base16: 19951f5e0788da99e08a47e6f6c7041ce48313b1d3ee59fa4f77a0843d3b6b9a
  * base2: 1a9173172b173ff3427a79530e359f4ee0f867d48830beb0187ef1196c5a6d5d
  * base4: 57c21369c5926fe4e4fd940446fac3c1324cda7779a418feaee1deaebd11a49b
  * base64: 6ca80fd062a08a9d413f5155e89e6406be5f08f58bd0968c928a9cee78ca5f18
  * base8: 05a9adb6742a118fd436ae0fa5315836b680700a9c7b662c02fc2ddca2a3c795
  * basei64: 1f90c906e3fe67a8162db24808346cd2b1917286163b89aedd6021bf8ff170c0
  * basemem: 461877c2f07716499c659d744f3046b4dd4c922b75f557f8cadbfba5dfb96154
  * emit_1k_k200: 2d591145b688f0831121a74733a904d83f622f637984804cc696cebf5916756c
  * emit_min_k200: 9f771a94061d8dbe596442f06df2d4304b566e1f5b9c3dad713e154934eb6760
  * etxn_burden: 59d8ae18a5a304ff8a8fd59c774eafd008cf6f6d7497e05696bc295e15ff5ade
  * etxn_fee_base_1k: fad921ba81969cb8e7f72d5b1cddebc286e90fc2778e0e817066e3718b033950
  * etxn_generation: f2c1ebe61c4c5f1dc96531b15edc454316b82e18eedbd81443686b55624c35b9
  * etxn_nonce_k200: abde1519f920fc8e33d1caaec1524251bcf350ab68dcaa9e4a0a05dcaded0799
  * etxn_reserve_once: 4c2b121ac151f8fd1e1e847244e3eca659ffeb98026684ca7115343c58293204
  * fee_base: 01770e98c09418cda2ab099c9041ca138e13eb381bc93c7965da5f55f7bd69d1
  * float_compare: c8839855baf4ed3fca0b89164d385f64b2dd7dc54ad4ce999f7c450f09a5a31c
  * float_compare_le: b2f69a1ca89859cba9ed0e52912129c2b99f60a8284a1b1ecd1a7249704256fc
  * float_divide: 2e32dd3aba4ac099112784a4583a985859920486b10208832e17538e8a9fe188
  * float_int: 80ba4a1c0c17e8f36f177b90e50433ca5f74274a91c2eed0601f3f1251167402
  * float_invert: 739794107f72a7e744051616dfe75fab6d98ea829ed0a70e1c68db7abc18869c
  * float_log: b02546e99ffe4411d5559edcdbaae6826cf15d9ea89ed9ce1f092cf9666956ef
  * float_mantissa: 5c42fe9049ab7a942de11975e97faf581430abf5671c21b01b4e3535ee295723
  * float_mulratio: c12370259e92181a46763403304c40448d9c27d37d1500222fefd902dae2fd04
  * float_multiply: 03dad6843c4e2b52b4a7fd9d5ddf28adc8143d53e99388a9733ee90f17ccf916
  * float_negate: d7b8bd000db1218d512a527dadd53c0bcb25578a6b44e1e212366aec0629c62e
  * float_one: 744a66f697a51b7a7dbeb7cbbd11ba6d28b42796a94e74aebf3cc515c1caedaf
  * float_root: 3b6f59dfff8ffd3cfa21099d3d6444bbe6a57ac69bb6b709bf9ddf12f48eefa3
  * float_set: 10f5b3487edf4730ef0922ed954fedbcf7b80f78ee8f337353f16a2c1733213d
  * float_sign: e8f576e9816c3f63186cccea6bef85043299e061126cf32a27d6649f8c566218
  * float_sto_iou: 22da686c05f373d354f8485f98b90eb50f3fc61c0e04787ecfbc84bd6c016364
  * float_sto_set: b065377382f631de011c958a296d03693c9a767e93d952ed613795fb542af720
  * float_sto_short: 42808b58a22724eb9c36e2d7bf12c3695040467e3f90f2f65f4cbae19e67a0dd
  * float_sto_xrp: 8fdb216ef73823b78c9cc2a318cad1515131fcc5f84c5bbe53170845599f2320
  * float_sum: bae331808cddfafbdfea7672c0d2c0d6d318af353152c63a56cf9891ff1e997b
  * hook_account_api: 08be655c066cce061bb51b1fbb0749015f19f9b31013bc7c33c30a4aaf469299
  * hook_again_once: 52f698839214fe49c58882e7f8979cbc757c18056514a58aee80a80a045002a6
  * hook_hash_0: c7ce10dde88b2f96e56598e755afccb5c2a7f60d60bf0132eb880497f9dfafa5
  * hook_hash_neg1: 29f8e4b0e059c6f4b9ef7fd24484efe207b8502e8105495a15de7dd48e2e0012
  * hook_param_256: 57960e76f1e8e912891daf6569fed60a01e4af2f0e261eeb100c4fa0f842147c
  * hook_param_32: d54fc38aaede5192b69071f3c3c1611664e1d9402e76eb27bb3dfcaae6a34a8b
  * hook_param_set_k16: c5a2f43a6f32cb12ba6ae370d91af09ce6ff148684dc9b955509a8f9863ec225
  * hook_pos: 86a9a96fcea686dd104b13ca52e38440d05b2c182ff005580ee6b36340bd87f5
  * hook_pos_k16: 989c5f9731e54a20c8a62f50ab2ca50371a206e2872a523bb06a547b459c11a8
  * hook_skip_alt: c8003b3350eb6a7dd50283325a5a60e4f10aa8c37afd5a14320582bf0f76da57
  * ledger_keylet: 5799ce209625180b074cfe795d7d54ba4f051ce4dca1f8313a9e7f0722f84299
  * ledger_last_hash: 229f008ea3c8eda168abd2018c577c8feff3acce010bd31362ba5e565e34e84b
  * ledger_last_time: 6a9d5f461bbd91b7122db0aa8be308ee1fe7caf0e13866a8b6d32be6064c12ba
  * ledger_nonce_k200: 8b7d5f6fb4467339807407d1c5c177ddd3e7679ff52b4aa40e19529a4763c0ac
  * ledger_seq: 0c9789ea811479a7832aaae59be8ec0a7d85c4b730863a37ee6557067a7bf844
  * meta_slot_k200: 79f195489127acde050ac91b4b6b27aaf9986d8ddfaaf221d969766e7abdf783
  * noexit: 4d861762c484692e5686da23dc63c4a4444d66b14ba6250bd29f769236cf5cef
  * otxn_burden: e1aab6cbd78e7095886eceaef2ed4d4f4b80dc4e6b116defc6314bc11ee61a23
  * otxn_field_16k: 86feb45180a9746e17f42fecc9edacc230f320d70a3633fa4ccd4d667eb9f639
  * otxn_field_1k: be3746581fc9d52a061d204d5910fdb79507e8db5397de51b7581b8ef05ebdf0
  * otxn_field_acc: 4b711c95b6fccbf186b1e11abfe13b464b79cc208cedf921f5fd66e9be04c097
  * otxn_generation: be31a048c2039efd87edce00f8511963bbf5e1323c81aa602dd64e63bce6086a
  * otxn_id_0: 5cc4c23073dc275f125b333db8450ed6bb93a26c4ff62403fb8f4fb39db188ad
  * otxn_id_1: b76d7c950aab363b783c8260240728e4f8d97eef73c4fcf40ec36985b01fdcc6
  * otxn_param_256: e765dbb713478f311718acd53b29320a60c7ba39008e689c1a78cabc1434cd9d
  * otxn_param_32: 6e1b2dee319832a94c20adeca4ff6beefefbd52bb8a16b5fd57fae1fd684cf1e
  * otxn_slot_16k: 0ca1956bcda294d2e24ef80e95edcf977ded32ca72cd90697a436c1e44baf19f
  * otxn_slot_1k: 8c1dfdb0be3f862dd75e4a98395d3d0c055008b6552cde1a9f85aae83f55f33c
  * otxn_slot_small: c433ede4ca6db0106e9003175d714fd1cb6733e3748a943719efbdeafce1b5a4
  * otxn_type: baeeb3b2d0e43ad314e0c156eb876431579c2023a510f938b736ea97afc18371
  * prepare_1k: 00b8c05ae3c8f44ffd4511b1fe63600f2397e1fc541d4c152fa34969fb431d37
  * prepare_min: 0668eeaafbc20dc326229ebe3d7248ef17acb9712fa2ad2bebb514876312396e
  * rollback0: 2e999489f98a7cdb4306d0767a4a6727ee73ec025717a471aff06e41ba2b3965
  * slot_16k: c162bfbf7a47f6f9e94416503dd96a672438d8cdb6caabe79b552dd99dc12007
  * slot_1k: fd90230410b3ea7eeee30ca021b2980d41fb7e5246a8bc62be621afa040778ce
  * slot_clear: 147ced74396d72a338f12f50691ebb579b737a350df055a5dcfe74a6c03b6b2a
  * slot_count: eeb89f48de6cc961357a597168c467525b691f8096cbf4f924b921b05247a974
  * slot_float: 2cd39f1bec4822b75533cc920e89d565da44125917dcf16a423e7d35ab78c538
  * slot_set_34: 8cb07c748dcd74b40d30450d0f9486c0ece2d1197d5fe62d7a3c357e7d6adb7c
  * slot_size: cb514b8ce1502ce180da8ff5e32fbfbce03f84a5ddb5820500825da9305fd29a
  * slot_subarray: 1581dc845784774a39b32db1b75b62dfd49702bea0e0b55a729725e5e9ccc82d
  * slot_subfield: fb31aed9d49d00c9c43cc19827c1559f93c4d558ba5d6afb128e3789782e0d1e
  * slot_type_0: 545887f1e57a49b0f45a73e956184ee7663b177caedf399af26695399edb2248
  * slot_type_1: a45453e8722d526774381a82aca7e8bbcf9b6200f2cbf81c95b04c9da5cdd509
  * state_foreign_r_256: 39a8c993856c5d92f63129432f265b8a6619d44098d19504a8528f41b918d3a4
  * state_foreign_r_32: 9ef25dfa071686def175928e25b29a03ddbef2b6c163977d96e477e21cf6950d
  * state_foreign_w: ab909c102eb3c8d646a5a48625b8a1ee4f18978ecd21a446cf8733d27aca5170
  * state_r_256: ec054a0751ea613cfbeca61788bc42dec3de7c0be64af0286cb290328dbad6f2
  * state_r_32: c5a9ede70571070c307f05bbd8bad2874e7c726b41e8880cb5165db95d053787
  * state_r_4k: e4ee00ce3672acb9d02ec096771e2c489ed591568ee9129ff278e76419342214
  * state_w_256: e675d18f6d81c53cf1fda7c53a7dcfc2b694d2a7fe4be300813d9d40e68bdf19
  * state_w_32: be83e06386bdc9d6fdcdd8f9ed96c85eafa6f53a75039d8eb12e2cd8ef5cd3b0
  * state_w_4k: 6f171e306c3ac21655a4098b54078429b46af17bd946fcee5a420d978baeebad
  * state_w_create_32: aead4e1f9c84a16ac34b0e087275ff9139ce438b291114f51bb4e6924b918bc2
  * state_w_setup_256: 3997a9102fa0d6f963329378494545cef7d41f756b84a9f2c29065f599f2a1ac
  * state_w_setup_32: a082e542c04a62b37a0850c8877da8e1f653362669216b023245f3094b048605
  * state_w_setup_4k: 291e50a8c07b871f36b9933937271b29629798286284be2bc0cb250a1d6f5282
  * sto_emplace_small: 2c147a509f4df033ce54de63165859360e8d30809d6b5285041403be50103cc2
  * sto_emplace_tx: cb705603ade17742929f6d6d946c629455c22224144d7f0093e6b05f8acb3938
  * sto_erase_small: 7e516be2359ec3bd44b4557ef6e0f81da3e78b593c0bacb226131d418aa1585f
  * sto_erase_tx: 02545a987f92fd98c0b3a0002d10e9977b8c93530f36f80347108c17b06ef74a
  * sto_subarray_tx: a1efe8d7298c41f96491a319131460938db5acbf806557fa9fedd9fba437e7c7
  * sto_subfield_small: 586bf48c8fade55f8c2289a3323c59713878943542f8103baee59023d2483c6c
  * sto_subfield_tx: ca78cfd5b30dd289e94554c3de8ce1eef6d77e08c80ec877d1e1a5c9772ca9e5
  * sto_validate_small: 02abab06ecf9f524ee1c725af43a07141b1d1bf26fe167b6aa7d5f1476ff1c63
  * sto_validate_tx: 31ba5f8bf1f14ac3a634f952fe946c2b9129713f0c93c4607d03e52b0a0c89de
  * trace_1k_hex: d7019591f209c778eac3ea837a94c30790faaf998659dbe0d62aa22c800d99e4
  * trace_32: c5bd8729cbbd783f5dd3851caff05b6343e9271c7d90da735c78ad104b6c7b43
  * trace_float: dfe285b257fa12e0f18bb36b80ea7e1018dde155da2fbadda81c23f2e0591dfd
  * trace_num: 9343491bd271d55a3924cdeb275ebdac32780f5f6d643a99759c40f9290de8d5
  * util_accid: 7d67b454580f15afcd4bc4c854e69efc163412b7e5006a32110fbb086e38bf71
  * util_keylet_account: 64d66281d9188a57f2856d9faeb4ba98df0344ff7c0796b696a9de8620df4ef1
  * util_keylet_amendments: 8fec2840dd0735dadb10e0a97a28c01727dd5aeda2acb7eafc6ec6729908b015
  * util_keylet_amm: 2a11e1b229355051ef91e49359d294a71b5b9f21f2f7594453d80f6bfe7c148b
  * util_keylet_check: a2f246e1da42f02c549f8051db533e6f179f78f7917a5051ecb51196b9004bf5
  * util_keylet_child: 8f816c7ea6b883b53fff4478fdbb5403e657d4142fd23a48fffe1c8661a13cb3
  * util_keylet_cron: f2b0b6228e47101420e9d0c6e11a1d3db87770cc5e6753a42ba249f685747df9
  * util_keylet_deposit_preauth: 0ab07e7f84c22d82c905200c9aa91aa2ffabd70740be7211b3389cac2bc27099
  * util_keylet_did: 356d787e91590720b323a27b0d7357544bae0d828691fe6e174eb12ab89071b2
  * util_keylet_emitted_txn: d162904e89d89762a603780adb6ba33829a3c2e2a51d1a85511417458c9e92a8
  * util_keylet_escrow: c12f9cb9e7539cbff03acdb2283983bd32f71fd63201298e593a378d5c3df283
  * util_keylet_hook: c6596eb2ac76d97c4fc69e6c2f2a1675684468b46bfbd2dc351b7ff03c744e2d
  * util_keylet_hook_definition: 821d2fdeaa5d9c53401ea0bf47dd9554c7142de69728e04bee377d4ed5067cb3
  * util_keylet_hook_state: f2f3423e6d0958bede317c51c27c492b9da3d91a95e86658dda4fbe8d1a93d1d
  * util_keylet_hook_state_dir: 15243f07390f2f2e1b7888b90387bdc6530250ece603a09f8e84333bf23a2d7c
  * util_keylet_line: bbdbbf4138398428efedb307d9c6b3e2b8664c23598ef0b236e4b06f8de3ae5a
  * util_keylet_nft_offer: 6371ef86e168712a16311273bdc6d33aa203996eba5b99f0ce2eb68c18e0a63e
  * util_keylet_offer: 0712fb09e219115bdc5d6d7e919792bf0f9a29b8d8ef45a8d24d8d4b603089b9
  * util_keylet_oracle: 7fc5ee01f0e9c41dc138fa7bcdb7844d29d37e97ac21559cbad1a48e30866a34
  * util_keylet_owner_dir: 07d0e729b2d0ce55020fd910b15449b21727bce77fe9f60eac4f74e4a9416a50
  * util_keylet_page: 5dee35728ff4a5ff2c946ee25cd507a3e3b0043c6c68e6c238aa8b38a6d43fb1
  * util_keylet_paychan: 0fa2d29b589e905b9a73b6f32f7274c73513cc2c9ef4cf6a39c0b7deba478518
  * util_keylet_quality: a5640e70c06dc0f5f2ca8d0ed73d9b9cafab5b4dc907155b055027444745514b
  * util_keylet_signers: 318c4ac941df2b19bf332ef831c073c7d1a366552535b6abbd35b5d4d9a3d2cf
  * util_keylet_skip: a26841ce3a9374b8d0417d7a87e19b69ce653f05870775a59359a82c72a1071f
  * util_keylet_unchecked: ad2131267847603d80b11593b2050c1ee4011a9c0b03fa0b433670983fcda11b
  * util_raddr: 3413102e38ad1b1758bbd7e267764d20517aa46ca8d9693a5847212d07a64a93
  * util_sha512h_16k: cfeb3e1b00816b26e357ed8aa1280c3c0013f2efdc25e5195711c53ccd164b62
  * util_sha512h_1k: 59cf18c33312ce624914a4db253e40db32614bddccea4041ef5993bc8ab0195b
  * util_sha512h_32: 6d464307725e1708e3deec123b573cc666e56eda01eaa1f4b59051f90f0da01f
  * util_verify_ed25519: 434b8342f35fd7df48b7cf36276062e215c78a390444a4fb30e0a858ee06f044
  * util_verify_secp256k1: 0719ea4ce1fd5aa6e9f9a6b8863e3005df068007007a6ba28f19d7b0386a9d18
  * xpop_slot_k100: 0fd0cacef61a769990779006de5a2d85756821a52c6a643a60b78961ff489e7c

## Baseline fit

| baseline | N1 | N2 | I(N1) | I(N2) | dI | dTw env.close (ns) | dTw exec.ns (ns) | static/iter | static/runtime ratio |
|---|---|---|---|---|---|---|---|---|---|
| base1 | 130 | 1300 | 5146 | 50776 | 39 | 347.898 | 385.256 | 41.0469 | 5.68304 |
| base2 | 70 | 700 | 4066 | 39976 | 57 | 470.303 | 470.57 | 65.087 | 4.32224 |
| base4 | 40 | 400 | 4277 | 42077 | 105 | 661.575 | 672.917 | 120.122 | 4.30946 |
| base8 | 25 | 250 | 4902 | 48327 | 193 | 1029.82 | 996.48 | 208.195 | 2.81244 |
| base16 | 5 | 50 | 1922 | 18527 | 369 | 1765.73 | 1663.89 | 384.961 | 2.0129 |
| base64 | 3 | 38 | 4352 | 54227 | 1425 | 5688.11 | 5551.2 | 1441.26 | 1.28919 |

Fitted (env.close() wall-clock, calibration channel): t_instr = 3.8204 ns, G (_g total per-iteration cost) = 267.401 ns, SE(G) = 30.1628 ns, R^2 = 0.999327
Fitted (exec.ns, wasm-window only, comparison): t_instr = 3.71133 ns, G = 269.985 ns, SE(G) = 11.1752 ns, R^2 = 0.999902

### Sensitivity baselines (t_instr alone, using G)

| baseline | dI | dTw env.close (ns) | t_instr alone (ns) |
|---|---|---|---|
| basei64 | 196 | 915.073 | 3.30445 |
| basemem | 118 | 766.943 | 4.23341 |

* t_instr = 3.8204 ns
* G (loop-head _g total per-iteration cost) = 267.401 ns
* R^2 (baseline fit) = 0.999327
* t_call (0-arg boundary, from E2E(hook_pos) - (M_pos - 2*t_clk)) = 208.536 ns
* O_g (the `_g` 2-arg call's own G above) = 267.401 ns vs t_call (0-arg hook_pos) = 208.536 ns -- host-call boundary grows roughly 29.4325 ns per argument

## Per-API results

| api | variant | K | calls | ns/call (M) | E2E (ns) | HF (ns) | used | cost (proposed) | cost (current) | notes |
|---|---|---|---|---|---|---|---|---|---|---|
| hook_pos | K=4 | 4 | 7200 | 13.8474 | 194.382956 | 194.383 | E2E | 51 | 40 |  |
| fee_base | K=4 | 4 | 7200 | 68.2451 | 269.723697 | 248.781 | E2E | 71 | 70 |  |
| ledger_seq | K=4 | 4 | 7200 | 69.0601 | 266.469993 | 249.596 | E2E | 70 | 140 |  |
| float_one | K=4 | 4 | 7200 | 14.6458 | 199.160425 | 195.181 | E2E | 53 | 20 |  |
| otxn_type | K=4 | 4 | 7200 | 66.5524 | 268.270456 | 247.088 | E2E | 71 | 130 |  |
| etxn_generation | K=4 | 4 | 7200 | 59.3099 | 244.897308 | 239.845 | E2E | 65 | 130 |  |
| util_sha512h | 32B | 1 | 1400 | 152.858 | 358.027608 | 333.393 | HF | 88 | 340 | HF (E2E noisy) |
| util_sha512h | 1KiB | 1 | 1400 | 735.544 | 952.505386 | 916.079 | HF | 240 | 340 | HF (E2E noisy) |
| util_sha512h | 16KiB | 1 | 1400 | 9251.1 | 9565.601417 | 9431.64 | E2E | 2600 | 340 |  |
| state | 32B | 1 | 200 | 1665.42 | 2298.523736 | 1845.96 | HF | 490 | 1700 | HF (E2E noisy) |
| state | 256B | 1 | 200 | 1661.46 | 2311.490403 | 1842 | HF | 490 | 1700 | HF (E2E noisy) |
| state_set | 32B, modify (fixed keys) | 1 | 200 | 631.005 | 8326.414446 | 3244.87 | HF | 850 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.566024; review #6: modify path |
| state_set | 32B, create (fresh keys, salt=rep) | 1 | 200 | 564.8 | 22955.575372 | 2142.63 | HF | 570 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 10.713735; review #6: create path |
| state_set | 256B | 1 | 200 | 566.875 | 7947.714446 | 3152.2 | HF | 830 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 2.521323 |
| util_raddr | K=4 | 4 | 1200 | 274.998 | 490.546721 | 455.533 | HF | 120 | 980 | HF (E2E noisy) |
| util_accid | K=4 | 4 | 1200 | 264.406 | 488.386536 | 444.941 | E2E | 130 | 690 |  |
| util_keylet | ACCOUNT | 4 | 1200 | 168.472 | 458.057678 | 349.007 | HF | 92 | 230 | HF (E2E noisy); E2E/HF ratio 1.312459 |
| util_keylet | CHILD | 4 | 1200 | 73.02 | 278.235455 | 253.556 | HF | 67 | 230 | HF (E2E noisy) |
| util_keylet | ESCROW | 4 | 1200 | 190.159 | 465.966011 | 370.695 | HF | 98 | 230 | HF (E2E noisy) |
| util_keylet | LINE | 4 | 1200 | 184.276 | 447.253974 | 364.811 | E2E | 120 | 230 |  |
| util_keylet | AMENDMENTS | 4 | 1200 | 72.0517 | 345.634530 | 252.587 | HF | 67 | 230 | HF (E2E noisy); E2E/HF ratio 1.368377 |
| util_keylet | QUALITY | 4 | 1200 | 75.4208 | 325.920641 | 255.956 | HF | 67 | 230 | HF (E2E noisy); AMENDMENTS's case also covers FEES/NEGATIVE_UNL/EMITTED_DIR (identical switch case); AMM/BRIDGE/XCHAIN_*/MPTOKEN_*/CREDENTIAL/PERMISSIONED_DOMAIN not built (complex multi-part operands -- asset pairs, bridge specs); every other keylet_type is covered below |
| util_keylet | HOOK | 4 | 1200 | 161.2 | 424.416011 | 341.736 | E2E | 120 | 230 |  |
| util_keylet | HOOK_STATE | 4 | 1200 | 173.209 | 423.027122 | 353.745 | HF | 93 | 230 | HF (E2E noisy) |
| util_keylet | SKIP | 4 | 1200 | 69.5083 | 323.218789 | 250.044 | HF | 66 | 230 | HF (E2E noisy) |
| util_keylet | OFFER | 4 | 1200 | 171.278 | 395.866937 | 351.813 | HF | 93 | 230 | HF (E2E noisy) |
| util_keylet | SIGNERS | 4 | 1200 | 167.586 | 443.319715 | 348.121 | HF | 92 | 230 | HF (E2E noisy) |
| util_keylet | CHECK | 4 | 1200 | 168.526 | 435.255826 | 349.061 | HF | 92 | 230 | HF (E2E noisy) |
| util_keylet | DEPOSIT_PREAUTH | 4 | 1200 | 170.807 | 420.365085 | 351.342 | HF | 92 | 230 | HF (E2E noisy) |
| util_keylet | UNCHECKED | 4 | 1200 | 71.3233 | 349.068789 | 251.859 | E2E | 92 | 230 | E2E/HF ratio 1.385969 |
| util_keylet | OWNER_DIR | 4 | 1200 | 161.763 | 432.980826 | 342.299 | E2E | 120 | 230 |  |
| util_keylet | PAGE | 4 | 1200 | 168.847 | 413.998418 | 349.383 | HF | 92 | 230 | HF (E2E noisy) |
| util_keylet | PAYCHAN | 4 | 1200 | 179.35 | 419.863233 | 359.886 | E2E | 110 | 230 |  |
| util_keylet | EMITTED_TXN | 4 | 1200 | 165.312 | 433.442863 | 345.848 | E2E | 120 | 230 |  |
| util_keylet | NFT_OFFER | 4 | 1200 | 177.396 | 439.808604 | 357.931 | E2E | 120 | 230 |  |
| util_keylet | HOOK_DEFINITION | 4 | 1200 | 167.454 | 443.319715 | 347.99 | HF | 92 | 230 | HF (E2E noisy) |
| util_keylet | HOOK_STATE_DIR | 4 | 1200 | 224.581 | 497.255826 | 405.116 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | CRON | 4 | 1200 | 224.052 | 491.237307 | 404.587 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | ORACLE | 4 | 1200 | 210.209 | 420.441011 | 390.745 | HF | 110 | 230 | HF (E2E noisy) |
| etxn_burden | K=4 | 4 | 1200 | 127.607 | 366.707956 | 308.142 | E2E | 96 | 260 |  |
| otxn_burden | K=4 | 4 | 1200 | 111.693 | 302.626474 | 292.229 | HF | 77 | 260 | HF (E2E noisy) |
| otxn_generation | K=4 | 4 | 1200 | 117.433 | 322.379252 | 297.969 | HF | 78 | 280 | HF (E2E noisy) |
| ledger_last_time | K=4 | 4 | 1200 | 66.7742 | 225.388511 | 247.31 | HF | 65 | 110 | HF (E2E noisy) |
| ledger_last_hash | K=4 | 4 | 1200 | 73.0242 | 354.013450 | 253.56 | HF | 67 | 210 | HF (E2E noisy); E2E/HF ratio 1.396174 |
| hook_account | K=4 | 4 | 1200 | 77.35 | 293.327338 | 257.886 | HF | 68 | 140 | HF (E2E noisy) |
| hook_hash | hook_no=0 | 4 | 1200 | 102.888 | 321.411567 | 283.424 | HF | 75 | 340 | HF (E2E noisy) |
| hook_hash | hook_no=-1 | 4 | 1200 | 74.2658 | 294.019900 | 254.801 | HF | 67 | 340 | HF (E2E noisy) |
| otxn_id | flags=0 | 4 | 1200 | 72.7033 | 270.062493 | 253.239 | HF | 67 | 450 | HF (E2E noisy) |
| otxn_id | flags=1 | 4 | 1200 | 71.42 | 306.288419 | 251.956 | HF | 66 | 450 | HF (E2E noisy) |
| float_multiply | K=4 | 4 | 1200 | 122.778 | 320.294005 | 303.313 | HF | 80 | 240 | HF (E2E noisy) |
| float_mulratio | K=4 | 4 | 1200 | 105.076 | 371.719869 | 285.611 | HF | 75 | 390 | HF (E2E noisy); E2E/HF ratio 1.301488 |
| float_negate | K=4 | 4 | 1200 | 66.2017 | 292.633851 | 246.737 | HF | 65 | 160 | HF (E2E noisy) |
| float_compare | COMPARE_EQUAL | 4 | 1200 | 88.295 | 297.222678 | 268.831 | HF | 71 | 140 | HF (E2E noisy) |
| float_compare | COMPARE_LESS|COMPARE_EQUAL | 4 | 1200 | 92.28 | 316.395826 | 272.816 | HF | 72 | 140 | HF (E2E noisy) |
| float_sum | K=4 | 4 | 1200 | 103.998 | 339.120857 | 284.534 | E2E | 89 | 350 |  |
| float_invert | K=4 | 4 | 1200 | 66.8758 | 278.010703 | 247.411 | HF | 65 | 230 | HF (E2E noisy) |
| float_divide | K=4 | 4 | 1200 | 109.453 | 326.042153 | 289.988 | HF | 76 | 280 | HF (E2E noisy) |
| float_mantissa | K=4 | 4 | 1200 | 67.355 | 329.284777 | 247.891 | E2E | 87 | 170 | E2E/HF ratio 1.328347 |
| float_sign | K=4 | 4 | 1200 | 69.9242 | 296.336629 | 250.46 | HF | 66 | 80 | HF (E2E noisy) |
| float_int | K=4 | 4 | 1200 | 69.445 | 297.106937 | 249.981 | HF | 66 | 100 | HF (E2E noisy) |
| float_log | K=4 | 4 | 1200 | 77.3842 | 268.905147 | 257.92 | HF | 68 | 100 | HF (E2E noisy) |
| float_root | K=4 | 4 | 1200 | 109.891 | 356.250487 | 290.426 | E2E | 94 | 190 |  |
| float_set | K=4 | 4 | 1200 | 102.853 | 357.717153 | 283.388 | HF | 75 | 110 | HF (E2E noisy) |
| float_sto | XRP | 4 | 1200 | 92.695 | 311.954931 | 273.231 | HF | 72 | 230 | HF (E2E noisy) |
| float_sto | IOU | 4 | 1200 | 102.834 | 337.147523 | 283.37 | E2E | 89 | 230 |  |
| float_sto | short | 4 | 1200 | 91.3192 | 310.720672 | 271.855 | HF | 72 | 230 | HF (E2E noisy) |
| float_sto_set | K=4 | 4 | 1200 | 85.6317 | 340.741227 | 266.167 | E2E | 90 | 140 |  |
| trace | 32B | 4 | 1200 | 425.06 | 711.109653 | 605.596 | HF | 160 | 100 | HF (E2E noisy); default journal level: early-returns on !j.trace() (design review B) |
| trace | 1KiB hex | 4 | 1200 | 710.14 | 1019.403172 | 890.676 | E2E | 270 | 100 |  |
| trace_num | K=4 | 4 | 1200 | 406.917 | 706.375911 | 587.452 | E2E | 190 | 100 |  |
| trace_float | K=4 | 4 | 1200 | 526.327 | 770.215271 | 706.862 | E2E | 210 | 100 |  |
| otxn_param | 32B | 4 | 1201 | 186.376 | 444.982832 | 366.912 | HF | 97 | 830 | HF (E2E noisy) |
| otxn_param | 256B | 4 | 1201 | 192.11 | 421.141166 | 372.646 | HF | 98 | 830 | HF (E2E noisy) |
| hook_param | 32B | 4 | 1200 | 110.071 | 329.243017 | 290.606 | E2E | 87 | 510 |  |
| hook_param | 256B | 4 | 1200 | 120.104 | 322.337462 | 300.64 | HF | 79 | 510 | HF (E2E noisy) |
| otxn_field | sfAccount(20B) | 1 | 300 | 118.05 | 204.063398 | 298.586 | HF | 79 | 460 | HF (E2E noisy); E2E/HF ratio 0.683433 |
| otxn_field | 1KiB Blob | 1 | 300 | 139.857 | 491.874509 | 320.392 | HF | 84 | 460 | HF (E2E noisy); E2E/HF ratio 1.535226 |
| otxn_field | 16KiB Blob | 1 | 300 | 512.65 | 410.241175 | 693.186 | HF | 190 | 460 | HF (E2E noisy); E2E/HF ratio 0.591820 |
| otxn_slot | small tx | 1 | 300 | 333.48 | 628.526422 | 514.016 | E2E | 170 | 310 |  |
| otxn_slot | 1KiB Blob | 1 | 300 | 375.15 | 639.944941 | 555.686 | HF | 150 | 310 | HF (E2E noisy) |
| otxn_slot | 16KiB Blob | 1 | 300 | 545.653 | 526.826422 | 726.189 | HF | 200 | 310 | HF (E2E noisy); E2E/HF ratio 0.725467 |
| slot | 1KiB Blob | 1 | 300 | 380.56 | 799.589323 | 561.096 | HF | 150 | 1400 | HF (E2E noisy); E2E/HF ratio 1.425050 |
| slot | 16KiB Blob | 1 | 300 | 1170.26 | 1577.985620 | 1350.79 | E2E | 420 | 1400 |  |
| slot_size | K=1 | 1 | 300 | 277.633 | 572.200496 | 458.169 | E2E | 150 | 330 |  |
| slot_type | flags=0 | 1 | 300 | 73.3067 | 255.724540 | 253.842 | HF | 67 | 210 | HF (E2E noisy) |
| slot_type | flags=1 | 1 | 300 | 87.1967 | 258.657873 | 267.732 | HF | 71 | 210 | HF (E2E noisy) |
| slot_count | 3 Memos | 1 | 300 | 71.6767 | 280.993089 | 252.212 | HF | 67 | 230 | HF (E2E noisy) |
| slot_subfield | sfAccount | 1 | 300 | 97.76 | 330.763398 | 278.296 | HF | 73 | 220 | HF (E2E noisy) |
| slot_float | sfAmount (own tx, Payment) | 1 | 300 | 104.497 | 243.804200 | 285.032 | HF | 75 | 150 | HF (E2E noisy) |
| slot_subarray | Memos[0] | 1 | 300 | 75.6967 | 254.837472 | 256.232 | HF | 68 | 330 | HF (E2E noisy) |
| slot_set | 34B keylet | 1 | 300 | 1310.41 | 1602.830064 | 1490.95 | HF | 400 | 350 | HF (E2E noisy) |
| slot_clear | K=1 | 1 | 300 | 187.903 | 404.894352 | 368.439 | HF | 97 | 230 | HF (E2E noisy) |
| sto_validate | ~31B | 1 | 300 | 211.6 | 422.235651 | 392.136 | HF | 110 | 350 | HF (E2E noisy) |
| sto_validate | ~tx (250B) | 1 | 300 | 567.503 | 795.426361 | 748.039 | HF | 200 | 350 | HF (E2E noisy) |
| sto_validate | ~4KiB (Blob) | 1 | 300 | 642.907 | 947.737472 | 823.442 | HF | 220 | 350 | HF (E2E noisy) |
| sto_subfield | ~31B | 1 | 300 | 129.3 | 341.715126 | 309.836 | HF | 82 | 340 | HF (E2E noisy) |
| sto_subfield | ~tx (250B) | 1 | 300 | 370.843 | 657.342996 | 551.379 | HF | 150 | 340 | HF (E2E noisy) |
| sto_subfield | ~4KiB (Blob) | 1 | 300 | 470.293 | 686.202256 | 650.829 | HF | 180 | 340 | HF (E2E noisy) |
| sto_subarray | ~tx (250B) | 1 | 300 | 215.58 | 481.417070 | 396.116 | HF | 110 | 290 | HF (E2E noisy); no small-object point (deferred); single-point table value |
| sto_subarray | 3 Memos, one ~1KiB | 1 | 300 | 247.35 | 447.465219 | 427.886 | HF | 120 | 290 | HF (E2E noisy) |
| sto_emplace | ~31B | 1 | 300 | 300.55 | 509.922410 | 481.086 | HF | 130 | 980 | HF (E2E noisy) |
| sto_emplace | ~tx (250B) | 1 | 300 | 437.207 | 657.957687 | 617.742 | HF | 170 | 980 | HF (E2E noisy) |
| sto_emplace | ~4KiB (Blob) | 1 | 300 | 627.63 | 1035.424354 | 808.166 | HF | 220 | 980 | HF (E2E noisy) |
| sto_erase | ~31B | 1 | 300 | 203.893 | 574.970620 | 384.429 | HF | 110 | 970 | HF (E2E noisy); E2E/HF ratio 1.495649 |
| sto_erase | ~tx (250B) | 1 | 300 | 267.227 | 408.805897 | 447.762 | HF | 120 | 970 | HF (E2E noisy) |
| sto_erase | ~4KiB (Blob) | 1 | 300 | 417.22 | 646.002194 | 597.756 | HF | 160 | 970 | HF (E2E noisy) |
| ledger_nonce | K=200/exec | 1 | 200 | 188.325 | 389.287503 | 368.861 | HF | 97 | 170 | HF (E2E noisy) |
| etxn_nonce | K=200/exec | 1 | 200 | 233.13 | 407.343058 | 413.666 | HF | 110 | 230 | HF (E2E noisy) |
| util_verify | ed25519 (passing) | 1 | 301 | 25099.1 | 26263.131947 | 25279.7 | E2E | 6900 | 24000 |  |
| util_verify | secp256k1 (passing) | 1 | 301 | 20241.4 | 21297.702317 | 20422 | E2E | 5600 | 24000 |  |
| hook_param_set | K=16/exec (cap) | 1 | 16 | 174.375 | 877.865006 | 354.911 | HF | 93 | 370 | HF (E2E noisy); E2E/HF ratio 2.473482 |
| meta_slot | K=200/exec, weak/AAW pass | 1 | 202 | 71.7822 | - | 252.318 | HF | 67 | 220 | HF (capped/one-shot) |
| prepare | min Payment spec | 1 | 300 | 28522.9 | 28937.778735 | 28703.5 | E2E | 7600 | 36000 | reference size (minimal Payment) |
| prepare | 1KiB ttINVOKE+sfBlob | 1 | 301 | 35331.7 | 36256.113490 | 35512.2 | E2E | 9500 | 36000 | 1KiB sfBlob variant (Phase 3 item 3) |
| etxn_fee_base | 1KiB ttINVOKE+sfBlob | 1 | 302 | 3628.23 | 3995.080219 | 3808.76 | HF | 1000 | 4600 | HF (E2E noisy); 1KiB sfBlob variant, direct call (not via emit) -- reference (min Payment) value comes from emit_min_k200's loop, see below |
| ledger_keylet | full range | 1 | 300 | 241.26 | 502.172564 | 421.796 | HF | 120 | 300 | HF (E2E noisy); lower bound: near-empty JTX ledger (design review F3) |
| state | 4KiB (ExtendedHookState) | 1 | 200 | 2348.13 | 3284.175650 | 2528.67 | E2E | 860 | 1700 |  |
| state_set | 4KiB (ExtendedHookState) | 1 | 200 | 725.205 | 12549.558890 | 4039.49 | HF | 1100 | 900 | HF (ledger-write cost reported separately); E2E/HF ratio 3.106718 |
| state_foreign | read 32B (no grant needed) | 1 | 200 | 1699.4 | 2351.532933 | 1879.94 | HF | 500 | 1700 | HF (E2E noisy) |
| state_foreign | read 256B (no grant needed) | 1 | 200 | 1703.7 | 2293.194045 | 1884.24 | HF | 500 | 1700 | HF (E2E noisy) |
| state_foreign_set | write, K=1 (first call, grant scan) | 1 | 1 | 8791 | - | 15637.5 | HF | 4100 | 3400 | HF (capped/one-shot) |
| state_foreign_set | write, K=200 (grant cached after 1st) | 1 | 200 | 631.7 | 7045.977378 | 3263.69 | HF | 860 | 3400 | HF (ledger-write cost reported separately); E2E/HF ratio 2.158899 |
| emit | K=200/exec, min Payment, own nonce+details+fee_base | 1 | 200 | 7902.06 | - | 8082.59 | HF | 2200 | 8700 | HF (undecomposable body) |
| etxn_details | inside emit_min_k200's loop | 1 | 200 | 398.77 | - | 579.306 | HF | 160 | 470 | HF (undecomposable body) |
| etxn_fee_base | inside emit_min_k200's loop | 1 | 200 | 3909.82 | - | 4090.36 | HF | 1100 | 4600 | HF (undecomposable body) |
| emit | K=200/exec, 1KiB ttINVOKE+sfBlob | 1 | 200 | 7501.44 | - | 7681.98 | HF | 2100 | 8700 | HF (undecomposable body) |
| hook_skip | alternating scan/erase (2-hook chain) | 1 | 300 | 106.25 | 408.035527 | 286.786 | HF | 76 | 170 | HF (E2E noisy); E2E/HF ratio 1.422789 |

(`xpop_slot` not observed as a call on fixture `w_regular_key` -- Import tx likely did not reach the hook as ttIMPORT; skipped)

## xpop_slot_k100 (separate Env per rep)

| api | variant | calls | ns/call | t_api (ns) | cost (proposed) | cost (current) | notes |
|---|---|---|---|---|---|---|---|
| xpop_slot | K=100/exec, min over 2 rep(s) (ttIMPORT, one fixture per fresh Env) | 100 | 34859.6 | 35040.1 | 9200 | 37000 | HF (capped/one-shot): anti-replay caps reps to the number of distinct fixtures, no N1/N2 E2E |
| util_keylet | AMM (own Env, featureAMM added) | 4 | 1201 | 236.283 | 521.483604 | 416.819 | HF | 110 | 230 | HF (E2E noisy) |
| util_keylet | DID (own Env, featureDID added) | 4 | 1200 | 210.693 | 527.732678 | 391.229 | HF | 110 | 230 | HF (E2E noisy); E2E/HF ratio 1.348910 |
| etxn_reserve | direct (1st call) | 1 | 1 | 41 | - | 221.536 | HF | 58 | 150 | HF (capped/one-shot): error path after 1st call is trivial (design review B) |
| hook_again | direct (1st call, strong pass) | 1 | 1 | 62 | - | 242.536 | HF | 64 | 260 | HF (capped/one-shot): error path after 1st call is trivial (design review B) |

## Apply-time ledger cost (not charged by HOOK_API_COST)

Per created / modified hook-state entry on this platform; per ledger entry, node-store dependent, not per API call (DESIGN §2.1).

| variant | E2E (ns/call) | HF (ns/call) | (E2E - HF) ns/entry | path |
|---|---|---|---|---|
| state_set: 32B, modify (fixed keys) | 8326.414446 | 3244.87 | 5081.543851 | modify |
| state_set: 32B, create (fresh keys, salt=rep) | 22955.575372 | 2142.63 | 20812.944777 | create |
| state_set: 256B | 7947.714446 | 3152.2 | 4795.513851 | modify |
| state_set: 4KiB (ExtendedHookState) | 12549.558890 | 4039.49 | 8510.068296 | modify |
| state_foreign_set: write, K=1 (first call, grant scan) | - | 15637.5 | - | modify |
| state_foreign_set: write, K=200 (grant cached after 1st) | 7045.977378 | 3263.69 | 3782.286783 | modify |

## Terminal APIs (accept / rollback)

| api | calls | ns/call (min) | ns/call (mean) | t_api (ns, from mean) | cost (proposed) | cost (current) | exec.ns diff vs noexit |
|---|---|---|---|---|---|---|---|

`noexit` (hook returns 0 without calling accept/rollback/exit): mean exec.ns = 24242.7 over 200/200 reps

| accept | 1 | 41 | 82.345 | 262.881 | 69 | 150 | -11178.9 |
| rollback | 1 | 41.5 | 80.07 | 260.606 | 69 | 180 | 1089.17 |

## Table value per API (DESIGN §2.4 rule)

| api | rule | rows | table cost |
|---|---|---|---|
| accept | max (single size, multiple paths) | 1 | 69 |
| emit | max (single size, multiple paths) | 2 | 2100 |
| etxn_burden | max (single size, multiple paths) | 1 | 96 |
| etxn_details | max (single size, multiple paths) | 1 | 160 |
| etxn_fee_base | max (single size, multiple paths) | 2 | 1000 |
| etxn_generation | max (single size, multiple paths) | 1 | 65 |
| etxn_nonce | max (single size, multiple paths) | 1 | 110 |
| etxn_reserve | max (single size, multiple paths) | 1 | 58 |
| fee_base | max (single size, multiple paths) | 1 | 71 |
| float_compare | mode: max | 2 | 72 |
| float_divide | max (single size, multiple paths) | 1 | 76 |
| float_int | max (single size, multiple paths) | 1 | 66 |
| float_invert | max (single size, multiple paths) | 1 | 65 |
| float_log | max (single size, multiple paths) | 1 | 68 |
| float_mantissa | max (single size, multiple paths) | 1 | 87 |
| float_mulratio | max (single size, multiple paths) | 1 | 75 |
| float_multiply | max (single size, multiple paths) | 1 | 80 |
| float_negate | max (single size, multiple paths) | 1 | 65 |
| float_one | max (single size, multiple paths) | 1 | 53 |
| float_root | max (single size, multiple paths) | 1 | 94 |
| float_set | max (single size, multiple paths) | 1 | 75 |
| float_sign | max (single size, multiple paths) | 1 | 66 |
| float_sto | mode: max | 3 | 89 |
| float_sto_set | max (single size, multiple paths) | 1 | 90 |
| float_sum | max (single size, multiple paths) | 1 | 89 |
| hook_account | max (single size, multiple paths) | 1 | 68 |
| hook_again | max (single size, multiple paths) | 1 | 64 |
| hook_hash | mode: max | 2 | 75 |
| hook_param | max (single size, multiple paths) | 2 | 79 |
| hook_param_set | max (single size, multiple paths) | 1 | 93 |
| hook_pos | max (single size, multiple paths) | 1 | 51 |
| hook_skip | max (single size, multiple paths) | 1 | 76 |
| ledger_keylet | max (single size, multiple paths) | 1 | 120 |
| ledger_last_hash | max (single size, multiple paths) | 1 | 67 |
| ledger_last_time | max (single size, multiple paths) | 1 | 65 |
| ledger_nonce | max (single size, multiple paths) | 1 | 97 |
| ledger_seq | max (single size, multiple paths) | 1 | 70 |
| meta_slot | max (single size, multiple paths) | 1 | 67 |
| otxn_burden | max (single size, multiple paths) | 1 | 77 |
| otxn_field | size: reference (DESIGN §2.4) | 3 | 84 |
| otxn_generation | max (single size, multiple paths) | 1 | 78 |
| otxn_id | mode: max | 2 | 67 |
| otxn_param | mode: max | 2 | 98 |
| otxn_slot | size: reference (DESIGN §2.4) | 3 | 150 |
| otxn_type | max (single size, multiple paths) | 1 | 71 |
| prepare | max (single size, multiple paths) | 2 | 9500 |
| rollback | max (single size, multiple paths) | 1 | 69 |
| slot | size: reference (DESIGN §2.4) | 2 | 150 |
| slot_clear | max (single size, multiple paths) | 1 | 97 |
| slot_count | max (single size, multiple paths) | 1 | 67 |
| slot_float | max (single size, multiple paths) | 1 | 75 |
| slot_set | max (single size, multiple paths) | 1 | 400 |
| slot_size | max (single size, multiple paths) | 1 | 150 |
| slot_subarray | max (single size, multiple paths) | 1 | 68 |
| slot_subfield | max (single size, multiple paths) | 1 | 73 |
| slot_type | mode: max | 2 | 71 |
| state | size: reference (DESIGN §2.4) | 3 | 490 |
| state_foreign | mode: max | 2 | 500 |
| state_foreign_set | mode: max | 2 | 4100 |
| state_set | size: reference (DESIGN §2.4) | 4 | 830 |
| sto_emplace | size: reference (DESIGN §2.4) | 3 | 170 |
| sto_erase | size: reference (DESIGN §2.4) | 3 | 120 |
| sto_subarray | size: reference (DESIGN §2.4) | 2 | 110 |
| sto_subfield | size: reference (DESIGN §2.4) | 3 | 150 |
| sto_validate | size: reference (DESIGN §2.4) | 3 | 200 |
| trace | mode: max | 2 | 270 |
| trace_float | max (single size, multiple paths) | 1 | 210 |
| trace_num | max (single size, multiple paths) | 1 | 190 |
| util_accid | max (single size, multiple paths) | 1 | 130 |
| util_keylet | mode: max | 25 | 120 |
| util_raddr | max (single size, multiple paths) | 1 | 120 |
| util_sha512h | size: geomean(ref, largest) [>10x] | 3 | 790 |
| util_verify | mode: max | 2 | 6900 |
| xpop_slot | max (single size, multiple paths) | 1 | 9200 |

## Proposed HOOK_API_COST block

In include/xrpl/hook/hook_api.macro declaration order; amendment column preserved from that file. An API with no measured row this run keeps its current value, annotated `// unmeasured`.

```
HOOK_API_COST(_g, 220, uint256{})  // unmeasured
HOOK_API_COST(accept, 69, uint256{})
HOOK_API_COST(rollback, 69, uint256{})
HOOK_API_COST(util_raddr, 120, uint256{})
HOOK_API_COST(util_accid, 130, uint256{})
HOOK_API_COST(util_verify, 6900, uint256{})  // ARM SHA-512 hardware acceleration; x86-64 run required before adoption (DESIGN §5)
HOOK_API_COST(util_sha512h, 790, uint256{})  // ARM SHA-512 hardware acceleration; x86-64 run required before adoption (DESIGN §5)
HOOK_API_COST(util_keylet, 120, uint256{})
HOOK_API_COST(sto_validate, 200, uint256{})
HOOK_API_COST(sto_subfield, 150, uint256{})
HOOK_API_COST(sto_subarray, 110, uint256{})
HOOK_API_COST(sto_emplace, 170, uint256{})
HOOK_API_COST(sto_erase, 120, uint256{})
HOOK_API_COST(etxn_burden, 96, uint256{})
HOOK_API_COST(etxn_details, 160, uint256{})
HOOK_API_COST(etxn_fee_base, 1000, uint256{})
HOOK_API_COST(etxn_reserve, 58, uint256{})
HOOK_API_COST(etxn_generation, 65, uint256{})
HOOK_API_COST(etxn_nonce, 110, uint256{})
HOOK_API_COST(emit, 2100, uint256{})
HOOK_API_COST(float_set, 75, uint256{})
HOOK_API_COST(float_multiply, 80, uint256{})
HOOK_API_COST(float_mulratio, 75, uint256{})
HOOK_API_COST(float_negate, 65, uint256{})
HOOK_API_COST(float_compare, 72, uint256{})
HOOK_API_COST(float_sum, 89, uint256{})
HOOK_API_COST(float_sto, 89, uint256{})
HOOK_API_COST(float_sto_set, 90, uint256{})
HOOK_API_COST(float_invert, 65, uint256{})
HOOK_API_COST(float_divide, 76, uint256{})
HOOK_API_COST(float_one, 53, uint256{})
HOOK_API_COST(float_mantissa, 87, uint256{})
HOOK_API_COST(float_sign, 66, uint256{})
HOOK_API_COST(float_int, 66, uint256{})
HOOK_API_COST(float_log, 68, uint256{})
HOOK_API_COST(float_root, 94, uint256{})
HOOK_API_COST(fee_base, 71, uint256{})
HOOK_API_COST(ledger_seq, 70, uint256{})
HOOK_API_COST(ledger_last_time, 65, uint256{})
HOOK_API_COST(ledger_last_hash, 67, uint256{})
HOOK_API_COST(ledger_nonce, 97, uint256{})
HOOK_API_COST(ledger_keylet, 120, uint256{})
HOOK_API_COST(hook_account, 68, uint256{})
HOOK_API_COST(hook_hash, 75, uint256{})
HOOK_API_COST(hook_param_set, 93, uint256{})
HOOK_API_COST(hook_param, 79, uint256{})
HOOK_API_COST(hook_again, 64, uint256{})
HOOK_API_COST(hook_skip, 76, uint256{})
HOOK_API_COST(hook_pos, 51, uint256{})
HOOK_API_COST(slot, 150, uint256{})
HOOK_API_COST(slot_clear, 97, uint256{})
HOOK_API_COST(slot_count, 67, uint256{})
HOOK_API_COST(slot_set, 400, uint256{})
HOOK_API_COST(slot_size, 150, uint256{})
HOOK_API_COST(slot_subarray, 68, uint256{})
HOOK_API_COST(slot_subfield, 73, uint256{})
HOOK_API_COST(slot_type, 71, uint256{})
HOOK_API_COST(slot_float, 75, uint256{})
HOOK_API_COST(state_set, 830, uint256{})
HOOK_API_COST(state_foreign_set, 4100, uint256{})
HOOK_API_COST(state, 490, uint256{})
HOOK_API_COST(state_foreign, 500, uint256{})
HOOK_API_COST(trace, 270, uint256{})
HOOK_API_COST(trace_num, 190, uint256{})
HOOK_API_COST(trace_float, 210, uint256{})
HOOK_API_COST(otxn_burden, 77, uint256{})
HOOK_API_COST(otxn_field, 84, uint256{})
HOOK_API_COST(otxn_generation, 78, uint256{})
HOOK_API_COST(otxn_id, 67, uint256{})
HOOK_API_COST(otxn_type, 71, uint256{})
HOOK_API_COST(otxn_slot, 150, uint256{})
HOOK_API_COST(otxn_param, 98, uint256{})
HOOK_API_COST(meta_slot, 67, uint256{})
HOOK_API_COST(xpop_slot, 9200, uint256{})
HOOK_API_COST(prepare, 9500, uint256{})
```

## Deferred (not measured this run)

* `util_keylet` -- every keylet_type with a dedicated constant in hookapi.h is covered except BRIDGE, XCHAIN_OWNED_CLAIM_ID, XCHAIN_OWNED_CREATE_ACCOUNT_CLAIM_ID, MPTOKEN_ISSUANCE, MPTOKEN, CREDENTIAL, and PERMISSIONED_DOMAIN: applyHook.cpp's util_keylet unconditionally returns INVALID_ARGUMENT for these (not measurable regardless of amendment state, see the comment at applyHook.cpp's keylet_code::BRIDGE case); TICKET (13) has no case in util_keylet's switch at all and is not accepted. AMM and DID are both measured (own Env with featureAMM/featureDID added, since both are Supported::no and so not in supported_amendments()).

## Notes

* HOOK_API_COST(_g) is dead: loop-head guards are consumed by the checker without being counted (design review sec A3). t_call/t_instr above still reflect the real cost of `_g`, reported for completeness.
* HOOK_API_COST is in static worst-case instruction units; t_instr is measured against the runtime instruction count, which is conservative (design review sec A4).
