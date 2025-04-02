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

#define HASH_WASM(x)                                                           \
    [[maybe_unused]] uint256 const x##_hash =                                                   \
        ripple::sha512Half_s(ripple::Slice(x##_wasm.data(), x##_wasm.size())); \
    [[maybe_unused]] std::string const x##_hash_str = to_string(x##_hash);                      \
    [[maybe_unused]] Keylet const x##_keylet = keylet::hookDefinition(x##_hash);

class SetHookV3_test : public beast::unit_test::suite
{
private:
    // helper
    void static overrideFlag(Json::Value& jv)
    {
        jv[jss::Flags] = hsfOVERRIDE;
    }

public:
// This is a large fee, large enough that we can set most small test hooks
// without running into fee issues we only want to test fee code specifically in
// fee unit tests, the rest of the time we want to ignore it.
#define HSFEE fee(100'000'000)
#define M(m) memo(m, "", "")

    void
    testRPCCall(jtx::Env& env, Json::Value tx, std::string expected)
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
        env.fund(XRP(10000), alice);
        env.close();

        Json::Value jv = hso(testv3_wasm, overrideFlag);
        jv[jss::HookApiVersion] = 3;

        // HookApiVersion 3 without HookFunctions
        env(ripple::test::jtx::hook(alice, {{jv}}, 0),
            HSFEE,
            ter(temMALFORMED));
        env.close();

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
        // HookApiVersion 1 with HookFunctions
        {
            jv[jss::HookApiVersion] = 1;
            env(ripple::test::jtx::hook(alice, {{jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
            env.close();
            jv[jss::HookApiVersion] = 3;
        }

        // invalid Hook Index
        {
            Json::Value empty;
            empty[jss::CreateCode] = "";
            empty[jss::Flags] = hsfOVERRIDE;
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept2"s);
            jv[jss::HookFunctions][1u][jss::HookFunction] = function;
            env(ripple::test::jtx::hook(alice, {{empty, jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
            env.close();
        }

        // invalid Hookv3 with Hookv1
        {
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept2"s);
            jv[jss::HookFunctions][1u][jss::HookFunction] = function;
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
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_accept3"s);
            jv[jss::HookFunctions][1u][jss::HookFunction] = function;
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
            Json::Value function = Json::Value(Json::objectValue);
            function[jss::FunctionName] = strHex("hook_too_long1234"s);
            jv[jss::HookFunctions][0u][jss::HookFunction] = function;
            env(ripple::test::jtx::hook(alice, {{jv}}, 0),
                HSFEE,
                ter(temMALFORMED));
            env.close();
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

        auto tx = invoke::invoke(alice);
        tx[jss::FunctionName] = strHex("hook_accept"s);
        testRPCCall(env, tx, "21");

        tx[jss::FunctionName] = strHex("hook_accept2"s);
        testRPCCall(env, tx, "19");
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
    testWithFeatures(FeatureBitset features)
    {
        testInvalid(features);
        testFeeRPC(features);
        testSimple(features);
    }

    void
    run() override
    {
        using namespace test::jtx;
        auto const sa = supported_amendments();
        testWithFeatures(sa);
    }

private:
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
