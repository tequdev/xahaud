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

#include <ripple/beast/unit_test.h>
#include <ripple/protocol/jss.h>
#include <test/jtx.h>

#include <boost/format.hpp>

namespace ripple {

namespace test {

namespace validator_data {
static auto const public_key =
    "nHBt9fsb4849WmZiCds4r5TXyBeQjqnH5kzPtqgMAQMgi39YZRPa";

static auto const token =
    "eyJ2YWxpZGF0aW9uX3NlY3JldF9rZXkiOiI5ZWQ0NWY4NjYyNDFjYzE4YTI3NDdiNT\n"
    "QzODdjMDYyNTkwNzk3MmY0ZTcxOTAyMzFmYWE5Mzc0NTdmYTlkYWY2IiwibWFuaWZl\n"
    "c3QiOiJKQUFBQUFGeEllMUZ0d21pbXZHdEgyaUNjTUpxQzlnVkZLaWxHZncxL3ZDeE\n"
    "hYWExwbGMyR25NaEFrRTFhZ3FYeEJ3RHdEYklENk9NU1l1TTBGREFscEFnTms4U0tG\n"
    "bjdNTzJmZGtjd1JRSWhBT25ndTlzQUtxWFlvdUorbDJWMFcrc0FPa1ZCK1pSUzZQU2\n"
    "hsSkFmVXNYZkFpQnNWSkdlc2FhZE9KYy9hQVpva1MxdnltR21WcmxIUEtXWDNZeXd1\n"
    "NmluOEhBU1FLUHVnQkQ2N2tNYVJGR3ZtcEFUSGxHS0pkdkRGbFdQWXk1QXFEZWRGdj\n"
    "VUSmEydzBpMjFlcTNNWXl3TFZKWm5GT3I3QzBrdzJBaVR6U0NqSXpkaXRROD0ifQ==\n";
}  // namespace validator_data

class ServerInfo_test : public beast::unit_test::suite
{
public:
    static std::unique_ptr<Config>
    makeValidatorConfig()
    {
        auto p = std::make_unique<Config>();
        boost::format toLoad(R"rippleConfig(
[validator_token]
%1%

[validators]
%2%
)rippleConfig");

        p->loadFromString(boost::str(
            toLoad % validator_data::token % validator_data::public_key));

        setupConfigForUnitTests(*p);

        return p;
    }

    void
    testServerInfo()
    {
        testcase("server_info");

        using namespace test::jtx;

        {
            Env env(*this);
            auto const result = env.rpc("server_info");
            BEAST_EXPECT(!result[jss::result].isMember(jss::error));
            BEAST_EXPECT(result[jss::result][jss::status] == "success");
            BEAST_EXPECT(result[jss::result].isMember(jss::info));
        }
        {
            Env env(*this, makeValidatorConfig());
            auto const result = env.rpc("server_info");
            BEAST_EXPECT(!result[jss::result].isMember(jss::error));
            BEAST_EXPECT(result[jss::result][jss::status] == "success");
            BEAST_EXPECT(result[jss::result].isMember(jss::info));
            BEAST_EXPECT(
                result[jss::result][jss::info][jss::pubkey_validator] ==
                validator_data::public_key);
        }
    }

    void
    testServerDefinitions()
    {
        using namespace test::jtx;

        {
            Env env(*this);
            auto const result = env.rpc("server_definitions");
            BEAST_EXPECT(!result[jss::result].isMember(jss::error));
            BEAST_EXPECT(result[jss::result][jss::status] == "success");
        }
    }

    void
    testServerDefinitions()
    {
        testcase("server_definitions");

        using namespace test::jtx;

        {
            Env env(*this);
            auto const result = env.rpc("server_definitions");
            BEAST_EXPECT(!result[jss::result].isMember(jss::error));
            BEAST_EXPECT(result[jss::result][jss::status] == "success");
            BEAST_EXPECT(result[jss::result].isMember(jss::FIELDS));
            BEAST_EXPECT(result[jss::result].isMember(jss::LEDGER_ENTRY_TYPES));
            BEAST_EXPECT(
                result[jss::result].isMember(jss::TRANSACTION_RESULTS));
            BEAST_EXPECT(result[jss::result].isMember(jss::TRANSACTION_TYPES));
            BEAST_EXPECT(result[jss::result].isMember(jss::TYPES));
            BEAST_EXPECT(result[jss::result].isMember(jss::hash));

            // test a random element of each result
            // (testing the whole output would be difficult to maintain)

            {
                auto const firstField = result[jss::result][jss::FIELDS][0u];
                BEAST_EXPECT(firstField[0u].asString() == "Generic");
                BEAST_EXPECT(
                    firstField[1][jss::isSerialized].asBool() == false);
                BEAST_EXPECT(
                    firstField[1][jss::isSigningField].asBool() == false);
                BEAST_EXPECT(firstField[1][jss::isVLEncoded].asBool() == false);
                BEAST_EXPECT(firstField[1][jss::nth].asUInt() == 0);
                BEAST_EXPECT(firstField[1][jss::type].asString() == "Unknown");
            }

            BEAST_EXPECT(
                result[jss::result][jss::LEDGER_ENTRY_TYPES]["AccountRoot"]
                    .asUInt() == 97);
            BEAST_EXPECT(
                result[jss::result][jss::TRANSACTION_RESULTS]["tecDIR_FULL"]
                    .asUInt() == 121);
            BEAST_EXPECT(
                result[jss::result][jss::TRANSACTION_TYPES]["Payment"]
                    .asUInt() == 0);
            BEAST_EXPECT(
                result[jss::result][jss::TYPES]["AccountID"].asUInt() == 8);
        }

        // test providing the same hash
        {
            Env env(*this);
            auto const firstResult = env.rpc("server_definitions");
            auto const hash = firstResult[jss::result][jss::hash].asString();
            auto const hashParam =
                std::string("{ ") + "\"hash\": \"" + hash + "\"}";

            auto const result =
                env.rpc("json", "server_definitions", hashParam);
            BEAST_EXPECT(!result[jss::result].isMember(jss::error));
            BEAST_EXPECT(result[jss::result][jss::status] == "success");
            BEAST_EXPECT(!result[jss::result].isMember(jss::FIELDS));
            BEAST_EXPECT(
                !result[jss::result].isMember(jss::LEDGER_ENTRY_TYPES));
            BEAST_EXPECT(
                !result[jss::result].isMember(jss::TRANSACTION_RESULTS));
            BEAST_EXPECT(!result[jss::result].isMember(jss::TRANSACTION_TYPES));
            BEAST_EXPECT(!result[jss::result].isMember(jss::TYPES));
            BEAST_EXPECT(result[jss::result].isMember(jss::hash));
        }

        // test providing a different hash
        {
            Env env(*this);
            std::string const hash =
                "54296160385A27154BFA70A239DD8E8FD4CC2DB7BA32D970BA3A5B132CF749"
                "D1";
            auto const hashParam =
                std::string("{ ") + "\"hash\": \"" + hash + "\"}";

            auto const result =
                env.rpc("json", "server_definitions", hashParam);
            BEAST_EXPECT(!result[jss::result].isMember(jss::error));
            BEAST_EXPECT(result[jss::result][jss::status] == "success");
            BEAST_EXPECT(result[jss::result].isMember(jss::FIELDS));
            BEAST_EXPECT(result[jss::result].isMember(jss::LEDGER_ENTRY_TYPES));
            BEAST_EXPECT(
                result[jss::result].isMember(jss::TRANSACTION_RESULTS));
            BEAST_EXPECT(result[jss::result].isMember(jss::TRANSACTION_TYPES));
            BEAST_EXPECT(result[jss::result].isMember(jss::TYPES));
            BEAST_EXPECT(result[jss::result].isMember(jss::hash));
        }
    }

    void
    run() override
    {
        testServerInfo();
        testServerDefinitions();
    }
};

BEAST_DEFINE_TESTSUITE(ServerInfo, app, ripple);

}  // namespace test
}  // namespace ripple
