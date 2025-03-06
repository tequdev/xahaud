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
        auto const gw = Account{"gateway"};
        auto const USD = gw["USD"];
        env.fund(XRP(10000), alice, gw);
        env.close();
        env.trust(USD(100000), alice);
        env.close();
        env(pay(gw, alice, USD(10000)));
        env.close();

        TestHook testv3_wasm = wasmv3[
            R"[test.hook](
            #include <stdint.h>
            extern int32_t _g       (uint32_t id, uint32_t maxiter);
            extern int64_t accept   (uint32_t read_ptr, uint32_t read_len, int64_t error_code);
            #define SBUF(x) (uint32_t)x,sizeof(x)

            int64_t hook_accept(uint32_t reserved)
            {
                _g(1,1);
                return accept(SBUF("failed"),0);
            }

            int64_t hook_accept2(uint32_t reserved)
            {
                _g(1,1);
                return accept(SBUF("success"),0);
            }
        )[test.hook]"];

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
            function[jss::FunctionName] = strHex("hook_accept2"s);
            jv[jss::HookFunctions][1u][jss::HookFunction] = function;
        }

        env(ripple::test::jtx::hook(alice, {{jv}}, 0), HSFEE);
        env.close();

        // invoke the hook
        Json::Value iv = invoke::invoke(alice);
        iv[jss::FunctionName] = strHex("hook_accept"s);
        env(iv, fee(XRP(1)));
        env.close();

        Json::Value iv2 = invoke::invoke(alice);
        iv2[jss::FunctionName] = strHex("hook_accept2"s);
        env(iv2, fee(XRP(1)));
        env.close();
    }

    void
    testWithFeatures(FeatureBitset features)
    {
        testSimple(features);
    }

    void
    run() override
    {
        using namespace test::jtx;
        auto const sa = supported_amendments();
        testWithFeatures(sa);
    }
};
BEAST_DEFINE_TESTSUITE(SetHookV3, app, ripple);
}  // namespace test
}  // namespace ripple
#undef M
