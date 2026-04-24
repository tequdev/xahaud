//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2023 XRPL Labs

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

#include <test/jtx.h>
#include <xrpld/app/ledger/LedgerMaster.h>
#include <xrpl/protocol/Feature.h>
#include <xrpl/protocol/jss.h>

namespace ripple {
namespace test {
struct ClaimReward_test : public beast::unit_test::suite
{
    bool
    expectRewards(
        jtx::Env const& env,
        jtx::Account const& acct,
        std::uint32_t ledgerFirst,
        std::uint32_t ledgerLast,
        std::uint64_t accumulator,
        std::uint32_t time)
    {
        auto const sle = env.le(keylet::account(acct));
        if (!sle->isFieldPresent(sfRewardLgrFirst) ||
            sle->getFieldU32(sfRewardLgrFirst) != ledgerFirst)
        {
            return false;
        }
        if (!sle->isFieldPresent(sfRewardLgrLast) ||
            sle->getFieldU32(sfRewardLgrLast) != ledgerLast)
        {
            return false;
        }
        if (!sle->isFieldPresent(sfRewardAccumulator) ||
            sle->getFieldU64(sfRewardAccumulator) != accumulator)
        {
            return false;
        }
        if (!sle->isFieldPresent(sfRewardTime) ||
            sle->getFieldU32(sfRewardTime) != time)
        {
            return false;
        }
        return true;
    }

    bool
    expectRewardsIOU(
        jtx::Env const& env,
        jtx::Account const& acct,
        jtx::IOU const& iou,
        std::uint32_t ledgerFirst,
        std::uint32_t ledgerLast,
        STAmount accumulator,
        std::uint32_t time)
    {
        auto const sle = env.le(keylet::line(acct, iou.account, iou.currency));
        BEAST_EXPECT(!!sle);
        auto const& sfRewardField =
            std::minmax(acct.id(), iou.account.id()).first == acct.id()
            ? sfLowReward
            : sfHighReward;

        if (!sle->isFieldPresent(sfRewardField))
            return false;

        auto const& reward =
            static_cast<STObject const&>(sle->peekAtField(sfRewardField));

        if (!reward.isFieldPresent(sfRewardLgrFirst) ||
            reward.getFieldU32(sfRewardLgrFirst) != ledgerFirst)
        {
            return false;
        }
        if (!reward.isFieldPresent(sfRewardLgrLast) ||
            reward.getFieldU32(sfRewardLgrLast) != ledgerLast)
        {
            return false;
        }
        if (!reward.isFieldPresent(sfTrustLineRewardAccumulator) ||
            reward.getFieldAmount(sfTrustLineRewardAccumulator) != accumulator)
        {
            return false;
        }
        if (!reward.isFieldPresent(sfRewardTime) ||
            reward.getFieldU32(sfRewardTime) != time)
        {
            return false;
        }
        return true;
    }

    bool
    expectNoRewards(jtx::Env const& env, jtx::Account const& acct)
    {
        auto const sle = env.le(keylet::account(acct));
        if (sle->isFieldPresent(sfRewardLgrFirst))
        {
            return false;
        }
        if (sle->isFieldPresent(sfRewardLgrLast))
        {
            return false;
        }
        if (sle->isFieldPresent(sfRewardAccumulator))
        {
            return false;
        }
        if (sle->isFieldPresent(sfRewardTime))
        {
            return false;
        }
        return true;
    }

    bool
    expectNoRewardsIOU(
        jtx::Env const& env,
        jtx::Account const& acct,
        jtx::IOU const& iou)
    {
        auto const sle = env.le(keylet::line(acct, iou.account, iou.currency));
        BEAST_EXPECT(!!sle);
        auto const& sfRewardField =
            std::minmax(acct.id(), iou.account.id()).first == acct.id()
            ? sfLowReward
            : sfHighReward;

        if (sle->isFieldPresent(sfRewardField))
            return false;
        return true;
    }

    void
    testEnabled(FeatureBitset features)
    {
        testcase("enabled");
        using namespace jtx;
        using namespace std::literals::chrono_literals;

        // setup env
        auto const alice = Account("alice");
        auto const issuer = Account("issuer");

        for (bool const withClaimReward : {false, true})
        {
            // If the BalanceRewards amendment is not enabled, you should not be
            // able to claim rewards.
            auto const amend =
                withClaimReward ? features : features - featureBalanceRewards;
            Env env{*this, amend};

            env.fund(XRP(1000), alice, issuer);
            env.close();

            auto const txResult =
                withClaimReward ? ter(tesSUCCESS) : ter(temDISABLED);

            auto const currentLedger = env.current()->seq();
            auto const currentTime =
                std::chrono::duration_cast<std::chrono::seconds>(
                    env.app()
                        .getLedgerMaster()
                        .getValidatedLedger()
                        ->info()
                        .parentCloseTime.time_since_epoch())
                    .count();

            // CLAIM
            env(reward::claim(alice), reward::issuer(issuer), txResult);
            env.close();

            if (withClaimReward)
            {
                BEAST_EXPECT(
                    expectRewards(
                        env,
                        alice,
                        currentLedger,
                        currentLedger,
                        0,
                        currentTime) == true);
            }
            else
            {
                BEAST_EXPECT(expectNoRewards(env, alice) == true);
            }
        }
    }

    void
    testInvalidPreflight(FeatureBitset features)
    {
        testcase("invalid preflight");
        using namespace test::jtx;
        using namespace std::literals;

        //----------------------------------------------------------------------
        // preflight

        // temDISABLED
        // amendment is disabled
        {
            test::jtx::Env env{
                *this,
                network::makeNetworkConfig(21337),
                features - featureBalanceRewards};

            auto const alice = Account("alice");
            auto const issuer = Account("issuer");

            env.fund(XRP(1000), alice, issuer);
            env.close();

            auto tx = reward::claim(alice);
            env(tx, reward::issuer(issuer), ter(temDISABLED));
            env.close();
        }

        // temINVALID_FLAG
        // can have flag 1 set to opt-out of rewards
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");
            auto const issuer = Account("issuer");

            env.fund(XRP(1000), alice, issuer);
            env.close();

            auto tx = reward::claim(alice);
            env(tx,
                reward::issuer(issuer),
                txflags(tfClose),
                ter(temINVALID_FLAG));
            env.close();
        }
        {
            for (bool const withFixFlags : {false, true})
            {
                auto const amend =
                    withFixFlags ? features : features - fixRewardClaimFlags;
                Env env{*this, amend};

                auto const alice = Account("alice");
                auto const issuer = Account("issuer");

                env.fund(XRP(1000), alice, issuer);
                env.close();

                auto tx = reward::claim(alice);
                env(tx,
                    reward::issuer(issuer),
                    txflags(tfFullyCanonicalSig),
                    withFixFlags ? ter(tesSUCCESS) : ter(temINVALID_FLAG));
                env.close();
            }
        }

        // temMALFORMED
        // Issuer cannot be the source account.
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");
            env.fund(XRP(1000), alice);
            env.close();

            env(reward::claim(alice), reward::issuer(alice), ter(temMALFORMED));
            env.close();
        }

        // featureIOURewardClaim

        // temDISABLED
        // featureIOURewardClaim amendment is disabled
        {
            test::jtx::Env env{
                *this,
                network::makeNetworkConfig(21337),
                features - featureIOURewardClaim};

            auto const alice = Account("alice");
            auto const bob = Account("bob");
            auto const gw = Account("gw");
            env.fund(XRP(1000), alice, bob, gw);
            env.close();

            jtx::IOU const USD = gw["USD"];

            env(reward::claim(alice),
                reward::issuer(bob),
                reward::claimCurrency(USD),
                ter(temDISABLED));
            env.close();
        }

        // temMALFORMED
        // ClaimCurrency.account cannot be the source account.
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");
            auto const bob = Account("bob");
            env.fund(XRP(1000), alice);
            env.close();

            jtx::IOU const USD = alice["USD"];

            env(reward::claim(alice),
                reward::issuer(bob),
                reward::claimCurrency(USD),
                ter(temMALFORMED));
            env.close();
        }

        // temMALFORMED
        // Issuer cannot be Genesis account if ClaimCurrency is set.
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");
            auto const gw = Account("gw");
            env.fund(XRP(1000), alice, gw);
            env.close();

            jtx::IOU const USD = gw["USD"];

            env(reward::claim(alice),
                reward::issuer(Account::master),
                reward::claimCurrency(USD),
                ter(temMALFORMED));
        }

        // MPT
        {
            // tested in testMPTInvalidInTx() at MPToken_test.cpp
        }
    }

    void
    testInvalidPreclaim(FeatureBitset features)
    {
        testcase("invalid preclaim");
        using namespace test::jtx;
        using namespace std::literals;

        //----------------------------------------------------------------------
        // preclaim

        // temDISABLED: DA tested in testEnabled() & testInvalidPreflight()
        // amendment is disabled

        // terNO_ACCOUNT
        // otxn account does not exist.
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");
            auto const issuer = Account("issuer");
            env.memoize(alice);

            env.fund(XRP(1000), issuer);
            env.close();

            auto tx = reward::claim(alice);
            tx[jss::Sequence] = 0;
            tx[jss::Fee] = 10;
            env(tx, reward::issuer(issuer), ter(terNO_ACCOUNT));
            env.close();
        }

        // temMALFORMED
        // (issuer && isOptOut)
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");
            auto const issuer = Account("issuer");

            env.fund(XRP(1000), alice, issuer);
            env.close();

            env(reward::claim(alice),
                reward::issuer(issuer),
                txflags(tfOptOut),
                ter(temMALFORMED));
            env.close();
        }
        // (!issuer && !isOptOut)
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");

            env.fund(XRP(1000), alice);
            env.close();

            env(reward::claim(alice), ter(temMALFORMED));
            env.close();
        }

        // tecNO_ISSUER
        // issuer account does not exist.
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");
            auto const issuer = Account("issuer");
            env.memoize(issuer);

            env.fund(XRP(1000), alice);
            env.close();

            auto tx = reward::claim(alice);
            env(tx, reward::issuer(issuer), ter(tecNO_ISSUER));
            env.close();
        }

        // tecNO_LINE
        // trustline does not exist.
        {
            test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

            auto const alice = Account("alice");
            auto const gw = Account("gw");
            env.fund(XRP(1000), alice, gw);
            env.close();

            jtx::IOU const USD = gw["USD"];

            env(reward::claim(alice),
                reward::issuer(gw),
                reward::claimCurrency(USD),
                ter(tecNO_LINE));
        }
    }

    void
    testValidNoHook(FeatureBitset features)
    {
        testcase("valid no hook");
        using namespace test::jtx;
        using namespace std::literals;

        test::jtx::Env env{*this, network::makeNetworkConfig(21337)};

        auto const alice = Account("alice");
        auto const bob = Account("bob");
        auto const gw = Account("gw");
        auto const issuer = Account("issuer");

        env.fund(XRP(1000), alice, bob, gw, issuer);
        env.close();

        // test claim rewards - no opt out
        auto const currentLedger = env.current()->seq();
        auto const currentTime =
            std::chrono::duration_cast<std::chrono::seconds>(
                env.app()
                    .getLedgerMaster()
                    .getValidatedLedger()
                    ->info()
                    .parentCloseTime.time_since_epoch())
                .count();

        auto tx = reward::claim(alice);
        env(tx, reward::issuer(issuer), ter(tesSUCCESS));
        env.close();

        BEAST_EXPECT(
            expectRewards(
                env, alice, currentLedger, currentLedger, 0, currentTime) ==
            true);

        // test claim rewards - opt out
        env(reward::claim(alice), txflags(tfOptOut), ter(tesSUCCESS));
        env.close();

        BEAST_EXPECT(expectNoRewards(env, alice) == true);

        // test iou claim rewards
        {
            // set trustline
            env(trust(bob, gw["USD"](10000)));
            env.close();

            // opt in
            auto const currentLedger = env.current()->seq();
            auto const currentTime =
                std::chrono::duration_cast<std::chrono::seconds>(
                    env.app()
                        .getLedgerMaster()
                        .getValidatedLedger()
                        ->info()
                        .parentCloseTime.time_since_epoch())
                    .count();

            auto tx = reward::claim(bob);
            env(tx,
                reward::issuer(issuer),
                reward::claimCurrency(gw["USD"]),
                ter(tesSUCCESS));
            env.close();

            BEAST_EXPECT(
                expectRewardsIOU(
                    env,
                    bob,
                    gw["USD"],
                    currentLedger,
                    currentLedger,
                    gw["USD"](0),
                    currentTime) == true);

            // opt out
            env(reward::claim(bob),
                reward::claimCurrency(gw["USD"]),
                txflags(tfOptOut),
                ter(tesSUCCESS));
            env.close();

            BEAST_EXPECT(expectNoRewardsIOU(env, bob, gw["USD"]) == true);
        }
    }

    void
    testUsingTickets(FeatureBitset features)
    {
        testcase("using tickets");
        using namespace jtx;
        using namespace std::literals::chrono_literals;
        Env env{*this, features};
        auto const alice = Account("alice");
        auto const issuer = Account("issuer");
        env.fund(XRP(10000), alice, issuer);
        std::uint32_t aliceTicketSeq{env.seq(alice) + 1};
        env(ticket::create(alice, 10));
        std::uint32_t const aliceSeq{env.seq(alice)};
        env.require(owners(alice, 10));

        env(reward::claim(alice),
            reward::issuer(issuer),
            ticket::use(aliceTicketSeq++),
            ter(tesSUCCESS));

        env.require(tickets(alice, env.seq(alice) - aliceTicketSeq));
        BEAST_EXPECT(env.seq(alice) == aliceSeq);
        env.require(owners(alice, 9));
    }

    void
    testBalanceChanges(FeatureBitset features)
    {
        testcase("balance changes");
        using namespace jtx;
        using namespace std::literals::chrono_literals;

        auto const getCurrentTime = [&](Env& env) {
            return std::chrono::duration_cast<std::chrono::seconds>(
                       env.app()
                           .getLedgerMaster()
                           .getValidatedLedger()
                           ->info()
                           .parentCloseTime.time_since_epoch())
                .count();
        };

        // Native Reward Claim
        {
            Env env{*this, features};
            auto const alice = Account("alice");
            auto const gw = Account("gw");

            auto const issuer = Account("issuer");
            env.fund(XRP(10001), alice, gw, issuer);
            env.close();

            auto const currentTime = getCurrentTime(env);
            auto const currentLedger = env.current()->seq();

            env(reward::claim(alice), reward::issuer(gw), fee(XRP(1)));
            env.close();

            env(fset(alice, 0));
            env.close();

            BEAST_EXPECT(
                expectRewards(
                    env,
                    alice,
                    currentLedger,
                    currentLedger + 1,
                    10000,  // 10000 XAH * time 1
                    currentTime) == true);
        }

        // IOU Reward Claim
        for (bool const fromHighAccount : {true, false})
        {
            Env env{*this, features};
            auto const alice = Account("alice");
            auto const bob = Account("bob");
            auto const issuer = Account("issuer");

            auto const user = fromHighAccount ? alice : bob;
            auto const gw = fromHighAccount ? bob : alice;

            if (fromHighAccount)
                BEAST_EXPECT(user.id() < gw.id());
            else
                BEAST_EXPECT(user.id() > gw.id());

            env.fund(XRP(10000), user, gw, issuer);
            env(fset(gw, asfDefaultRipple));

            env(trust(user, gw["USD"](1000000)), fee(XRP(1)));
            env.close();
            env(pay(gw, user, gw["USD"](10000)));
            env.close();

            auto currentTime = getCurrentTime(env);
            auto currentLedger = env.current()->seq();

            env(reward::claim(user),
                reward::issuer(gw),
                reward::claimCurrency(gw["USD"]));
            env.close();

            env(pay(user, gw, gw["USD"](10000)));
            env.close();

            BEAST_EXPECT(
                expectRewardsIOU(
                    env,
                    user,
                    gw["USD"],
                    currentLedger,
                    currentLedger + 1,
                    user["USD"](10000),  // 10000 USD * time 1
                    currentTime) == true);

            env(pay(gw, user, gw["USD"](1)));
            env.close();

            // check Balance == 0
            BEAST_EXPECT(
                expectRewardsIOU(
                    env,
                    user,
                    gw["USD"],
                    currentLedger,
                    currentLedger + 2,
                    user["USD"](10000),  // 10000 USD * time 1 + 0 USD * time 1
                    currentTime) == true);
        }

        // Check Balance minus -> plus, plus -> minus
        for (bool const fromHighAccount : {true, false})
        {
            Env env{*this, features};
            auto const alice = Account("alice");
            auto const bob = Account("bob");
            auto const issuer = Account("issuer");

            auto const user = fromHighAccount ? alice : bob;
            auto const gw = fromHighAccount ? bob : alice;

            if (fromHighAccount)
                BEAST_EXPECT(user.id() < gw.id());
            else
                BEAST_EXPECT(user.id() > gw.id());

            env.fund(XRP(10000), user, gw, issuer);
            env(fset(gw, asfDefaultRipple));
            env.close();

            env(trust(user, gw["USD"](1000000)));
            env.close();
            env(trust(gw, user["USD"](1000000)));
            env(pay(gw, user, gw["USD"](10000)));
            env.close();

            auto currentTime = getCurrentTime(env);
            auto currentLedger = env.current()->seq();

            env(reward::claim(user),
                reward::issuer(gw),
                reward::claimCurrency(gw["USD"]));
            env.close();

            env(pay(user, gw, gw["USD"](20000)));
            env.close();

            env(pay(user, gw, gw["USD"](1)));
            env.close();

            BEAST_EXPECT(
                expectRewardsIOU(
                    env,
                    user,
                    gw["USD"],
                    currentLedger,
                    currentLedger + 2,
                    user["USD"](10000),  // 10000 USD * time 1 + 0 USD * time 1
                    currentTime) == true);
        }

        // STAmount overflow in reward accumulation should not cause
        // transaction failure (tefEXCEPTION). The overflow should be
        // gracefully skipped via try-catch.
        for (bool const fromHighAccount : {true, false})
        {
            Env env{*this, features};
            auto const alice = Account("alice");
            auto const bob = Account("bob");
            auto const issuer = Account("issuer");

            auto const user = fromHighAccount ? alice : bob;
            auto const gw = fromHighAccount ? bob : alice;

            env.fund(XRP(10000), user, gw, issuer);
            env(fset(gw, asfDefaultRipple));
            env.close();

            // Use a near-max IOU balance at exponent 80. When
            // multiply(balance, STAmount(lgrElapsed), issue) is called
            // with lgrElapsed >= 2, the result exponent exceeds
            // cMaxOffset(80), causing IOUAmount::normalize to throw
            // std::overflow_error("value overflow").
            auto const bigUSD = STAmount{
                gw["USD"].issue(), std::uint64_t(5000000000000000ull), 80};
            // Payment amount must be large enough to register a
            // balance change given STAmount's 16-digit precision.
            auto const payBackUSD = STAmount{
                gw["USD"].issue(), std::uint64_t(1000000000000000ull), 80};

            env(trust(user, bigUSD));
            env.close();
            env(pay(gw, user, bigUSD));
            env.close();

            // Claim IOU reward to initialize reward tracking
            env(reward::claim(user),
                reward::issuer(gw),
                reward::claimCurrency(gw["USD"]));
            env.close();

            // Advance ledger so lgrElapsed >= 2. With lgrElapsed=1
            // the multiply result is exactly at cMaxOffset boundary
            // (no overflow). With lgrElapsed >= 2, the result exponent
            // exceeds cMaxOffset and triggers the overflow.
            env.close();

            // This payment modifies the trustline balance, triggering
            // reward accumulation in Transactor. Without the try-catch
            // fix, multiply() throws std::overflow_error("value overflow")
            // and the transaction fails with tefEXCEPTION.
            env(pay(user, gw, payBackUSD), ter(tesSUCCESS));
            env.close();
        }
    }

    void
    testWithFeats(FeatureBitset features)
    {
        testEnabled(features);
        testInvalidPreflight(features);
        testInvalidPreclaim(features);
        testValidNoHook(features);
        testUsingTickets(features);
        testBalanceChanges(features);
    }

public:
    void
    run() override
    {
        using namespace test::jtx;
        auto const sa = supported_amendments();
        testWithFeats(sa);
    }
};

BEAST_DEFINE_TESTSUITE(ClaimReward, app, ripple);

}  // namespace test
}  // namespace ripple
