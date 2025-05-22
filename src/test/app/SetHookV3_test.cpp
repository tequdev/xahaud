//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012-2016 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================
#include <ripple/app/hook/Enum.h>
#include <ripple/app/ledger/LedgerMaster.h>
#include <ripple/app/tx/impl/SetHook.h>
#include <ripple/basics/StringUtilities.h>
#include <ripple/json/json_reader.h>
#include <ripple/json/json_writer.h>
#include <ripple/protocol/TxFlags.h>
#include <ripple/protocol/jss.h>
#include <iostream>
#include <test/app/SetHookV3_wasm.h>
#include <test/jtx.h>
#include <test/jtx/hook.h>
#include <unordered_map>

namespace ripple {

namespace test {

using TestHook = std::vector<uint8_t> const&;

// Identical to BEAST_EXPECT except it returns from the function
// if the condition isn't met (and would otherwise therefore cause a crash)
#define BEAST_REQUIRE(x)     \
    {                        \
        BEAST_EXPECT(!!(x)); \
        if (!(x))            \
            return;          \
    }

#define HASH_WASM(x)                                                           \
    [[maybe_unused]] uint256 const x##_hash =                                  \
        ripple::sha512Half_s(ripple::Slice(x##_wasm.data(), x##_wasm.size())); \
    [[maybe_unused]] std::string const x##_hash_str = to_string(x##_hash);     \
    [[maybe_unused]] Keylet const x##_keylet = keylet::hookDefinition(x##_hash);

class SetHookV3_test : public beast::unit_test::suite
{
private:
    // helper
    void static overrideFlag(Json::Value& jv)
    {
        jv[jss::Flags] = hsfOVERRIDE;
    }

    Json::Value
    addFuncParam(const std::string& name, const std::string& typeName)
    {
        Json::Value param = Json::Value(Json::objectValue);
        param[jss::FunctionParameter][jss::FunctionParameterName] =
            strHex(name);
        param[jss::FunctionParameter][jss::FunctionParameterType][jss::type] =
            typeName;
        return param;
    };

    template <typename T>
    Json::Value
    addFuncParamValue(const std::string& typeName, T value)
    {
        Json::Value param = Json::Value(Json::objectValue);
        param[jss::FunctionParameter][jss::FunctionParameterValue][jss::type] =
            typeName;
        param[jss::FunctionParameter][jss::FunctionParameterValue][jss::value] =
            value;
        return param;
    };

    Json::Value
    addFunc(const std::map<
            std::string,
            std::vector<std::pair<std::string, std::string>>>& args)
    {
        Json::Value params = Json::Value(Json::arrayValue);
        int i = 0;
        for (auto const& [a_name, a_params] : args)
        {
            Json::Value param = Json::Value(Json::objectValue);
            param[jss::HookFunction][jss::FunctionName] = strHex(a_name);
            for (auto const& [p_name, p_type] : a_params)
                param[jss::HookFunction][jss::FunctionParameters].append(
                    addFuncParam(p_name, p_type));
            params[i++] = param;
        }
        return params;
    }

public:
// This is a large fee, large enough that we can set most small test hooks
// without running into fee issues we only want to test fee code specifically in
// fee unit tests, the rest of the time we want to ignore it.
#define HSFEE fee(100'000'000)
#define M(m) memo(m, "", "")

    void
    testFeeRPCCall(jtx::Env& env, Json::Value tx, std::string expected)
    {
        auto const jtx = env.jt(tx);

        auto const feeDrops = env.current()->fees().base;

        // build tx_blob
        Json::Value params;
        params[jss::tx_blob] = strHex(jtx.stx->getSerializer().slice());

        // fee request
        auto const jrr = env.rpc("json", "fee", to_string(params));
        // std::cout << "RESULT: " << jrr << "\n";

        // verify base fee & open ledger fee
        auto const drops = jrr[jss::result][jss::drops];
        auto const baseFee = drops[jss::base_fee_no_hooks];
        BEAST_EXPECT(baseFee == to_string(feeDrops));
        auto const openLedgerFee = drops[jss::open_ledger_fee];
        BEAST_EXPECT(openLedgerFee == expected);

        // verify hooks fee
        auto const hooksFee = jrr[jss::result][jss::fee_hooks_feeunits];
        BEAST_EXPECT(hooksFee == expected);
        if (hooksFee != expected)
        {
            std::cout << "hooksFee: " << hooksFee << "";
            std::cout << "expected: " << expected << "\n";
        }
    }

    void
    testQueryRPCCall(
        jtx::Env& env,
        jtx::Account const& hookAccount,
        jtx::Account const& sourceAccount,
        std::string functionName,
        Json::Value funcParams,
        std::string expected)
    {
        Json::Value params;
        params[jss::hook_account] = hookAccount.human();
        params[jss::source_account] = sourceAccount.human();
        params[jss::function_name] = functionName;
        params[jss::function_params] = funcParams;

        // hook_query request
        auto const jrr = env.rpc("json", "hook_query", to_string(params));
        std::cout << "RESULT: " << jrr << "\n";
    }

    void
    testInvalid(FeatureBitset features)
    {
        testcase("Test invalid");
        using namespace jtx;
        using namespace std::string_literals;

        // Env env{*this, features};
        Env env{
            *this, envconfig(), features, nullptr,
            // beast::severities::kTrace
        };

        auto const alice = Account{"alice"};
        auto const bob = Account{"bob"};
        env.fund(XRP(10000), alice);
        env.fund(XRP(10000), bob);
        env.close();

        Json::Value jv = hso(testv3_wasm, overrideFlag);
        jv[jss::HookApiVersion] = 3;

        // HookApiVersion 3 without HookFunctions
        env(ripple::test::jtx::hook(alice, {{jv}}, 0),
            HSFEE,
            ter(temMALFORMED));
        env.close();

        jv[jss::HookFunctions] = addFunc(
            {{"hook_accept", {}}, {"hook_rollback", {}}, {"hook_accept2", {}}});
        // HookApiVersion 1 with HookFunctions
        {
            Json::Value jv = hso(testv3_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 1;
            env(ripple::test::jtx::hook(alice, {{jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
            env.close();
        }

        // invalid Hook Index
        {
            Json::Value empty;
            empty[jss::CreateCode] = "";
            empty[jss::Flags] = hsfOVERRIDE;
            empty[jss::HookFunctions] = addFunc({{}, {"hook_accept2", {}}});
            env(ripple::test::jtx::hook(alice, {{empty, jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
            env.close();
        }

        // invalid Hookv3 with Hookv1
        {
            Json::Value jv = hso(testv3_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 3;
            jv[jss::HookFunctions] = addFunc({{"hook_accept2", {}}});
            env(ripple::test::jtx::hook(
                    alice, {{jv, hso(accept_wasm, overrideFlag)}}, 0),
                HSFEE,
                ter(temMALFORMED));
            env.close();

            // TOOD: Should error when deploy v3 after deplyed v1 (by 2
            // txns)
        }

        // invalid FunctionName
        {
            Json::Value jv = hso(testv3_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 3;
            jv[jss::HookFunctions] = addFunc({{"hook_accept3", {}}});
            env(ripple::test::jtx::hook(alice, {{jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
            env.close();
        }

        // FunctionName size is too long
        {
            TestHook testLongFunctionName_wasm = wasmv3[
                R"[test.hook](
                #include <stdint.h>
                extern int32_t _g       (uint32_t id, uint32_t maxiter);
                extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
                #define SBUF(x) (uint32_t)x,sizeof(x)

                int64_t hook_too_long1234(uint32_t reserved)
                {
                    _g(1,1);
                    return accept(SBUF("success"),0);
                }
            )[test.hook]"];
            Json::Value jv = hso(testLongFunctionName_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 3;
            jv[jss::HookFunctions] = addFunc({{"hook_too_long1234", {}}});
            env(ripple::test::jtx::hook(alice, {{jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
            env.close();
        }

        // Prepare: Create to Alice
        Json::Value jvCreate = hso(testv3_simple_wasm, overrideFlag);
        jvCreate[jss::HookApiVersion] = 3;
        jvCreate[jss::HookFunctions] =
            addFunc({{"hook_accept", {{"account", "ACCOUNT"}}}});
        env(ripple::test::jtx::hook(alice, {{jvCreate}}, 0), HSFEE);
        env.close();

        // Test Install (bob)
        {
            Json::Value jvInstall = hso(testv3_simple_wasm, overrideFlag);
            jvInstall[jss::HookApiVersion] = 3;
            jvInstall[jss::HookFunctions] = addFunc({{"hook_accept2", {}}});
            env(ripple::test::jtx::hook(bob, {{jvInstall}}, 0),
                HSFEE,
                ter(temMALFORMED));

            jvInstall[jss::HookFunctions] =
                addFunc({{"hook_accept", {}}, {"hook_accept2", {}}});
            env(ripple::test::jtx::hook(bob, {{jvInstall}}, 0),
                HSFEE,
                ter(temMALFORMED));
        }
        // TestUpdate (alice)
        {
            Json::Value jvUpdate = hso(testv3_simple_wasm, overrideFlag);
            jvUpdate[jss::HookApiVersion] = 3;
            jvUpdate[jss::HookFunctions] = addFunc({{"hook_accept2", {}}});
            env(ripple::test::jtx::hook(alice, {{jvUpdate}}, 0),
                HSFEE,
                ter(temMALFORMED));

            jvUpdate[jss::HookFunctions] =
                addFunc({{"hook_accept", {}}, {"hook_accept2", {}}});
            env(ripple::test::jtx::hook(alice, {{jvUpdate}}, 0),
                HSFEE,
                ter(temMALFORMED));
        }
        // Test: Execulte
        {
            // Invalid Parameter Size
            {
                // size == 0
                Json::Value jv = invoke::invoke(bob);
                jv[jss::Destination] = alice.human();
                jv[jss::FunctionName] = strHex("hook_accept"s);
                env(jv, fee(XRP(1)), ter(tecHOOK_REJECTED));
            }
            {
                // size == 2
                Json::Value jv = invoke::invoke(bob);
                jv[jss::Destination] = alice.human();
                jv[jss::FunctionName] = strHex("hook_accept"s);
                jv[jss::FunctionParameters][0u] =
                    addFuncParamValue("ACCOUNT", Account{"bob"}.human());
                jv[jss::FunctionParameters][1u] =
                    addFuncParamValue("ACCOUNT", Account{"bob"}.human());
                env(jv, fee(XRP(1)), ter(tecHOOK_REJECTED));
            }
            // Invalid ParemeterType
            {
                Json::Value jv = invoke::invoke(bob);
                jv[jss::Destination] = alice.human();
                jv[jss::FunctionName] = strHex("hook_accept"s);
                jv[jss::FunctionParameters][0u] =
                    addFuncParamValue("VL", "1234567890");
                env(jv, fee(XRP(1)), ter(tecHOOK_REJECTED));
            }
        }
    }

    void
    testFeeRPC(FeatureBitset features)
    {
        testcase("Test fee RPC");
        using namespace jtx;
        using namespace std::string_literals;

        // Env env{*this, features};
        Env env{
            *this, envconfig(), features, nullptr,
            // beast::severities::kTrace
        };

        auto const alice = Account{"alice"};
        auto const bob = Account{"bob"};
        auto const charlie = Account{"charlie"};
        auto const dave = Account{"dave"};
        env.fund(XRP(10000), alice);
        env.fund(XRP(10000), bob);
        env.fund(XRP(10000), charlie);
        env.fund(XRP(10000), dave);
        env.close();

        // install the hook on alice
        Json::Value jv = hso(testv3_wasm, overrideFlag);
        jv[jss::HookApiVersion] = 3;
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept"s);
            jv[jss::HookFunctions][0u][jss::HookFunction] = function;
        }
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_rollback"s);
            jv[jss::HookFunctions][1u][jss::HookFunction] = function;
        }
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept2"s);
            jv[jss::HookFunctions][2u][jss::HookFunction] = function;
        }

        env(ripple::test::jtx::hook(alice, {{jv}}, 0), HSFEE);
        env.close();

        auto tx = invoke::invoke(alice);
        tx[jss::FunctionName] = strHex("hook_accept"s);
        testFeeRPCCall(env, tx, "21");

        tx[jss::FunctionName] = strHex("hook_accept2"s);
        testFeeRPCCall(env, tx, "19");

        {
            // Function Parameter Fee
            Json::Value jv = hso(testv3_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 3;
            {
                jv[jss::HookFunctions] = addFunc(
                    {{"hook_accept", {{"account", "ACCOUNT"}}},
                     {"hook_rollback", {}},
                     {"hook_accept2", {}}});
            }
            env(ripple::test::jtx::hook(bob, {{jv}}, 0), HSFEE);
            env.close();

            auto tx = invoke::invoke(bob);
            tx[jss::FunctionName] = strHex("hook_accept"s);
            tx[jss::FunctionParameters][0u] =
                addFuncParamValue("ACCOUNT", Account{"bob"}.human());
            // basefee 21 + 20byte(AccountID)
            testFeeRPCCall(env, tx, "41");
        }
        
        // Initialize Hook
        {
            TestHook initialize_wasm = wasmv3[
                R"[test.hook](
                #include <stdint.h>
                extern int32_t _g       (uint32_t id, uint32_t maxiter);
                extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
                int64_t hook_initialize(uint32_t reserved)
                {
                    _g(1,1);
                    return accept(0,0,0);
                }
            )[test.hook]"];
            HASH_WASM(initialize);

            auto makeTx = [&](uint32_t flags) {
                Json::Value jv = hso(initialize_wasm, overrideFlag);
                jv[jss::HookApiVersion] = 3;
                Json::Value function = Json::Value(Json::objectValue);
                function[jss::FunctionName] = strHex("hook_initialize"s);
                function[jss::Flags] = flags;
                jv[jss::HookFunctions][0u][jss::HookFunction] = function;
                return jv;
            };

            Json::Value jv = makeTx(0);
            // No Definition, without initialize flag
            testFeeRPCCall(
                env, ripple::test::jtx::hook(charlie, {{jv}}, 0), "76010");

            // No Definition,with initialize flag
            jv = makeTx(hffINITIALIZE);
            testFeeRPCCall(
                env, ripple::test::jtx::hook(charlie, {{jv}}, 0), "76019");

            // With Definition, without initialize flag
            jv = makeTx(0);
            env(ripple::test::jtx::hook(charlie, {{jv}}, 0), HSFEE);
            
            jv = Json::Value(Json::objectValue);
            jv[jss::HookHash] = initialize_hash_str;
            testFeeRPCCall(
                env, ripple::test::jtx::hook(dave, {{jv}}, 0), "10");

            // remove the hook
            env(ripple::test::jtx::hook(charlie, {{hso_delete()}}, 0), HSFEE);
            env.close();

            // With Definition, with initialize flag
            jv = makeTx(hffINITIALIZE);
            env(ripple::test::jtx::hook(charlie, {{jv}}, 0), HSFEE);

            jv = Json::Value(Json::objectValue);
            jv[jss::HookHash] = initialize_hash_str;
            testFeeRPCCall(env, ripple::test::jtx::hook(dave, {{jv}}, 0), "19");
        }
    }

    void
    testSimple(FeatureBitset features)
    {
        testcase("Test simple");

        using namespace jtx;
        using namespace std::string_literals;

        // Env env{*this, features};
        Env env{
            *this, envconfig(), features, nullptr,
            // beast::severities::kTrace
        };

        auto const alice = Account{"alice"};
        env.fund(XRP(10000), alice);
        env.close();

        // install the hook on alice
        Json::Value jv = hso(testv3_wasm, overrideFlag);
        jv[jss::HookApiVersion] = 3;
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept"s);
            jv[jss::HookFunctions][0u][jss::HookFunction] = function;
        }
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_rollback"s);
            jv[jss::HookFunctions][1u][jss::HookFunction] = function;
        }
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept2"s);
            jv[jss::HookFunctions][2u][jss::HookFunction] = function;
        }

        env(ripple::test::jtx::hook(alice, {{jv}}, 0), HSFEE);
        env.close();

        // invoke the hook
        Json::Value iv = invoke::invoke(alice);
        iv[jss::FunctionName] = strHex("hook_accept"s);
        env(iv, fee(XRP(1)));
        env.close();

        Json::Value iv2 = invoke::invoke(alice);
        iv2[jss::FunctionName] = strHex("hook_rollback"s);
        env(iv2, fee(XRP(1)), ter(tecHOOK_REJECTED));
        env.close();

        Json::Value iv3 = invoke::invoke(alice);
        iv3[jss::FunctionName] = strHex("hook_accept2"s);
        env(iv3, fee(XRP(1)));
        env.close();
    }

    void
    testFunctionParameters(FeatureBitset features)
    {
        testcase("Test function parameters");

        using namespace jtx;
        using namespace std::string_literals;

        // Env env{*this, features};
        Env env{
            *this, envconfig(), features, nullptr,
            // beast::severities::kTrace
        };

        auto const alice = Account{"alice"};
        env.fund(XRP(10000), alice);
        env.close();

        TestHook testv3_wasm = wasmv3[
            R"[test.hook](
            #include <stdint.h>
            extern int32_t _g       (uint32_t id, uint32_t maxiter);
            #define GUARD(maxiter) _g((1ULL << 31U) + __LINE__, (maxiter)+1)
            extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            extern int64_t rollback (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            extern int64_t util_accid (uint32_t, uint32_t, uint32_t, uint32_t);
            extern int64_t otxn_func_param (uint32_t write_ptr, uint32_t write_len, uint32_t index, uint32_t serialized_type_id);
            #define UINT8 16
            #define UINT16 1
            #define UINT32 2
            #define UINT64 3
            #define UINT128 4
            #define UINT256 5
            #define AMOUNT 6
            #define VL 7
            #define ACCOUNT 8
            #define INVALID_ARGUMENT -7
            #define DOESNT_EXIST -5
            #define SBUF(x) (uint32_t)x,sizeof(x)
            #define SVAR(x) (uint32_t)&x,sizeof(x)
            #define ASSERT_EQUAL(x, y) if (!(x == y)) rollback((uint32_t)#x,sizeof(#x), x);
            int64_t hook_accept(uint32_t reserved)
            {
                _g(1,1);
                ASSERT_EQUAL(otxn_func_param(0, 0, 10, UINT16), DOESNT_EXIST);
                ASSERT_EQUAL(otxn_func_param(0, 2, 0, UINT8), INVALID_ARGUMENT);
                ASSERT_EQUAL(otxn_func_param(0, 2, 0, 99), INVALID_ARGUMENT);
                
                uint16_t data16;
                ASSERT_EQUAL(otxn_func_param(SVAR(data16), 0, UINT16), 2);
                ASSERT_EQUAL(data16, 0);
                
                uint32_t data32;
                ASSERT_EQUAL(otxn_func_param(SVAR(data32), 1, UINT32), 4);
                ASSERT_EQUAL(data32, 1);
                
                uint64_t data64;
                ASSERT_EQUAL(otxn_func_param(SVAR(data64), 2, UINT64), 8);
                ASSERT_EQUAL(data64, 2);
                
                uint8_t data128[16];
                ASSERT_EQUAL(otxn_func_param(SBUF(data128), 3, UINT128), 16);
                for (int i = 0; GUARD(15), i < 15; i++)
                    ASSERT_EQUAL(data128[i], 0);
                ASSERT_EQUAL(data128[15], 3);

                uint8_t data256[32];
                ASSERT_EQUAL(otxn_func_param(SBUF(data256), 4, UINT256), 32);
                for (int i = 0; GUARD(31), i < 31; i++)
                    ASSERT_EQUAL(data256[i], 0);
                ASSERT_EQUAL(data256[31], 4);

                ASSERT_EQUAL(otxn_func_param(0, 8, 5, AMOUNT), 8);
                
                uint8_t data_vl[6];
                ASSERT_EQUAL(otxn_func_param(SBUF(data_vl), 6, VL), 6);
                for (int i = 0; GUARD(6), i < 6; i++)
                    ASSERT_EQUAL(data_vl[i], i);

                uint8_t data_account[20];
                uint8_t expected_account[20];
                const char addr[] = "rPMh7Pi9ct699iZUTWaytJUoHcJ7cgyziK"; // bob
                ASSERT_EQUAL(util_accid(SBUF(expected_account), SBUF(addr)), 20);
                ASSERT_EQUAL(otxn_func_param(SBUF(data_account), 7, ACCOUNT), 20);
                for (int i = 0; GUARD(20), i < 20; i++)
                    ASSERT_EQUAL(data_account[i], expected_account[i]);

                uint8_t data8;
                ASSERT_EQUAL(otxn_func_param(SVAR(data8), 8, UINT8), 1);
                ASSERT_EQUAL(data8, 8);

                return accept(SBUF("success"),0);
            }
            
            int64_t hook_rollback(uint32_t reserved)
            {
                _g(1,1);
                return rollback(SBUF("rollback"),0);
            }

            int64_t hook_accept2(uint32_t reserved)
            {
                _g(1,1);
                return accept(SBUF("success2"),0);
            }
        )[test.hook]"];

        // install the hook on alice
        Json::Value jv = hso(testv3_wasm, overrideFlag);
        jv[jss::HookApiVersion] = 3;
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept"s);
            Json::Value hookFunctions = Json::Value(Json::arrayValue);
            hookFunctions[0u] = addFuncParam("uint16", "UINT16");
            hookFunctions[1u] = addFuncParam("uint32", "UINT32");
            hookFunctions[2u] = addFuncParam("uint64", "UINT64");
            hookFunctions[3u] = addFuncParam("uint128", "UINT128");
            hookFunctions[4u] = addFuncParam("uint256", "UINT256");
            hookFunctions[5u] = addFuncParam("amount", "AMOUNT");
            hookFunctions[6u] = addFuncParam("vl", "VL");
            hookFunctions[7u] = addFuncParam("account", "ACCOUNT");
            hookFunctions[8u] = addFuncParam("uint8", "UINT8");
            function[jss::FunctionParameters] = hookFunctions;
            jv[jss::HookFunctions][0u][jss::HookFunction] = function;
        }
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_rollback"s);
            Json::Value hookFunctions = Json::Value(Json::arrayValue);
            jv[jss::HookFunctions][1u][jss::HookFunction] = function;
        }
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept2"s);
            jv[jss::HookFunctions][2u][jss::HookFunction] = function;
        }

        env(ripple::test::jtx::hook(alice, {{jv}}, 0), HSFEE);
        env.close();

        // invoke the hook
        Json::Value iv = invoke::invoke(alice);
        iv[jss::FunctionName] = strHex("hook_accept"s);
        iv[jss::FunctionParameters][0u] =
            addFuncParamValue<uint16_t>("UINT16", 0);
        iv[jss::FunctionParameters][1u] =
            addFuncParamValue<uint32_t>("UINT32", 1);
        iv[jss::FunctionParameters][2u] =
            addFuncParamValue<std::string>("UINT64", "02");
        iv[jss::FunctionParameters][3u] =
            addFuncParamValue<std::string>("UINT128", "03");
        iv[jss::FunctionParameters][4u] =
            addFuncParamValue<std::string>("UINT256", "04");
        iv[jss::FunctionParameters][5u] =
            addFuncParamValue<std::string>("AMOUNT", "10");
        iv[jss::FunctionParameters][6u] =
            addFuncParamValue<std::string>("VL", "000102030405");
        iv[jss::FunctionParameters][7u] =
            addFuncParamValue<std::string>("ACCOUNT", Account{"bob"}.human());
        iv[jss::FunctionParameters][8u] =
            addFuncParamValue<uint8_t>("UINT8", 8);

        env(iv, fee(XRP(1)));
        env.close();
        return;

        Json::Value iv2 = invoke::invoke(alice);
        iv2[jss::FunctionName] = strHex("hook_rollback"s);
        env(iv2, fee(XRP(1)), ter(tecHOOK_REJECTED));
        env.close();

        Json::Value iv3 = invoke::invoke(alice);
        iv3[jss::FunctionName] = strHex("hook_accept2"s);
        env(iv3, fee(XRP(1)));
        env.close();
    }

    void
    testInitialize(FeatureBitset features)
    {
        testcase("Test initialize");

        using namespace jtx;
        using namespace std::string_literals;

        // Env env{*this, features};
        Env env{
            *this, envconfig(), features, nullptr,
            // beast::severities::kInfo
        };

        auto const alice = Account{"alice"};
        env.fund(XRP(10000), alice);
        env.close();

        // invalid HookFunction flag
        {
            Json::Value jv = hso(testv3_simple_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 3;
            {
                Json::Value function = Json::Value(Json::objectValue);
                function[jss::FunctionName] = strHex("hook_accept"s);
                function[jss::Flags] = 0x1000;
                jv[jss::HookFunctions][0u][jss::HookFunction] = function;
            }
            env(ripple::test::jtx::hook(alice, {{jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
        }

        TestHook testv3_wasm = wasmv3[
            R"[test.hook](
            #include <stdint.h>
            extern int32_t _g       (uint32_t id, uint32_t maxiter);
            #define GUARD(maxiter) _g((1ULL << 31U) + __LINE__, (maxiter)+1)
            extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            extern int64_t rollback (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            extern int64_t state_set(uint32_t,uint32_t,uint32_t, uint32_t);
            #define SBUF(x) (uint32_t)x,sizeof(x)
            #define SVAR(x) (uint32_t)&x,sizeof(x)
            #define ASSERT(x) if (!(x)) rollback((uint32_t)#x,sizeof(#x), __LINE__);
            int64_t init(uint32_t reserved)
            {
                _g(1,1);
                ASSERT(state_set(SBUF("ABC"),SBUF("DEF")) > 0);
                return accept(SBUF("success"),0);
            }
            int64_t init2(uint32_t reserved)
            {
                _g(1,1);
                return accept(SBUF("success2"),0);
            }
        )[test.hook]"];

        // duplicate hffINITIALIZE flag
        {
            Json::Value jv = hso(testv3_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 3;
            {
                Json::Value function = Json::Value(Json::objectValue);
                function[jss::FunctionName] = strHex("init"s);
                function[jss::Flags] = FunctionalHookFlags::hffINITIALIZE;
                jv[jss::HookFunctions][0u][jss::HookFunction] = function;
                function[jss::FunctionName] = strHex("init2"s);
                function[jss::Flags] = FunctionalHookFlags::hffINITIALIZE;
                jv[jss::HookFunctions][1u][jss::HookFunction] = function;
            }
            env(ripple::test::jtx::hook(alice, {{jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
        }

        // flag on off
        for (int i = 0; i < 2; i++)
        {
            bool init = i == 0;
            uint32_t flag = init ? FunctionalHookFlags::hffINITIALIZE : 0;
            // install the hook on alice
            Json::Value jv = hso(testv3_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 3;
            {
                Json::Value function = Json::Value(Json::objectValue);
                function[jss::FunctionName] = strHex("init"s);
                function[jss::Flags] = flag;
                jv[jss::HookFunctions][0u][jss::HookFunction] = function;
                function[jss::FunctionName] = strHex("init2"s);
                function[jss::Flags] = 0;
                jv[jss::HookFunctions][1u][jss::HookFunction] = function;
            }

            env(ripple::test::jtx::hook(alice, {{jv}}, 0), HSFEE);
            env.close();

            auto meta = env.meta();
            BEAST_REQUIRE(meta);
            BEAST_REQUIRE(meta->isFieldPresent(sfHookExecutions) == init);
        }
    }

    void
    testHookQuery(FeatureBitset features)
    {
        testcase("Test hook query");

        using namespace jtx;
        using namespace std::string_literals;

        // Env env{*this, features};
        Env env{
            *this, envconfig(), features, nullptr,
            // beast::severities::kInfo
        };

        auto const alice = Account{"alice"};
        env.fund(XRP(10000), alice);
        env.close();

        // invalid HookFunction flag
        {
            Json::Value jv = hso(testv3_simple_wasm, overrideFlag);
            jv[jss::HookApiVersion] = 3;
            {
                Json::Value function = Json::Value(Json::objectValue);
                function[jss::FunctionName] = strHex("hook_accept"s);
                function[jss::Flags] = 0x1000;
                jv[jss::HookFunctions][0u][jss::HookFunction] = function;
            }
            env(ripple::test::jtx::hook(alice, {{jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
        }

        TestHook testv3_wasm = wasmv3[
            R"[test.hook](
            #include <stdint.h>
            extern int32_t _g       (uint32_t id, uint32_t maxiter);
            #define GUARD(maxiter) _g((1ULL << 31U) + __LINE__, (maxiter)+1)
            extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            extern int64_t rollback (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            extern int64_t trace_num(uint32_t, uint32_t, uint64_t);
            extern int64_t state(uint32_t,uint32_t,uint32_t,uint32_t);
            extern int64_t hook_account(uint32_t,uint32_t);
            extern int64_t otxn_func_param (uint32_t write_ptr, uint32_t write_len, uint32_t index, uint32_t serialized_type_id);
            extern int64_t query_result_set(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
            #define STI_ACCOUNT 8
            #define STI_VL 7
            #define SBUF(x) (uint32_t)x,sizeof(x)
            #define SVAR(x) (uint32_t)&x,sizeof(x)
            #define ASSERT(x) if (!(x)) rollback((uint32_t)#x,sizeof(#x), __LINE__);
            int64_t query(uint32_t reserved)
            {
                _g(1,1);
                uint8_t account[20];
                ASSERT(hook_account(SBUF(account)) == 20);
                state(0,0,0,0);
                uint8_t buf[256];
                ASSERT(otxn_func_param(SBUF(buf), 0, STI_VL) > 0);
                ASSERT(query_result_set(SBUF("some_target_account"),SBUF(account),STI_ACCOUNT) > 0);
                return accept(SBUF("success"),0);
            }
            int64_t init(uint32_t reserved)
            {
                _g(1,1);
                return accept(SBUF("success2"),0);
            }
        )[test.hook]"];

        // install the hook on alice
        Json::Value jv = hso(testv3_wasm, overrideFlag);
        jv[jss::HookApiVersion] = 3;
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("init"s);
            function[jss::Flags] = 0;
            jv[jss::HookFunctions][0u][jss::HookFunction] = function;
            function[jss::FunctionName] = strHex("query"s);
            function[jss::Flags] = FunctionalHookFlags::hffQUERY;
            jv[jss::HookFunctions][1u][jss::HookFunction] = function;
            jv[jss::HookFunctions][1u][jss::HookFunction]
              [jss::FunctionParameters][0u] = addFuncParam("hook", "VL");
        }

        env(ripple::test::jtx::hook(alice, {{jv}}, 0), HSFEE);
        env.close();

        Json::Value params = Json::objectValue;
        params["hook"][jss::type] = "VL";
        params["hook"][jss::value] = "DEADBEEF";

        testQueryRPCCall(env, alice, alice, "query", params, "success");
    }

    void
    testWithFeatures(FeatureBitset features)
    {
        testInvalid(features);
        testFeeRPC(features);
        testSimple(features);
        testFunctionParameters(features);
        testInitialize(features);
        testHookQuery(features);
    }

    void
    run() override
    {
        using namespace test::jtx;
        auto const sa = supported_amendments();
        testWithFeatures(sa);
    }

private:
    TestHook testv3_simple_wasm = wasmv3[
        R"[test.hook](
            #include <stdint.h>
            extern int32_t _g       (uint32_t id, uint32_t maxiter);
            extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            #define SBUF(x) (uint32_t)x,sizeof(x)
            int64_t hook_accept(uint32_t reserved)
            {
                _g(1,1);
                return accept(SBUF("success"),0);
            }
        )[test.hook]"];
    HASH_WASM(testv3_simple);

    TestHook testv3_wasm = wasmv3[
        R"[test.hook](
            #include <stdint.h>
            extern int32_t _g       (uint32_t id, uint32_t maxiter);
            extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            extern int64_t rollback (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            extern int64_t hook_pos (void);
            #define SBUF(x) (uint32_t)x,sizeof(x)

            int64_t hook_accept(uint32_t reserved)
            {
                _g(1,1);
                hook_pos();
                return accept(SBUF("success"),0);
            }
            
            int64_t hook_rollback(uint32_t reserved)
            {
                _g(1,1);
                return rollback(SBUF("rollback"),0);
            }

            int64_t hook_accept2(uint32_t reserved)
            {
                _g(1,1);
                return accept(SBUF("success2"),0);
            }
        )[test.hook]"];
    HASH_WASM(testv3);

    TestHook accept_wasm =  // WASM: 0
        wasmv3[
            R"[test.hook](
            #include <stdint.h>
            extern int32_t _g       (uint32_t id, uint32_t maxiter);
            extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            int64_t hook(uint32_t reserved )
            {
                _g(1,1);
                return accept(0,0,0);
            }
        )[test.hook]"];

    HASH_WASM(accept);
};
BEAST_DEFINE_TESTSUITE(SetHookV3, app, ripple);
}  // namespace test
}  // namespace ripple
#undef M
