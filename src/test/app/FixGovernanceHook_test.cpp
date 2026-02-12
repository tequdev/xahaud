//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2024 Ripple Labs Inc.

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

#include <ripple/app/ledger/LedgerMaster.h>
#include <ripple/app/misc/HashRouter.h>
#include <ripple/app/tx/impl/XahauGenesis.h>
#include <ripple/protocol/Feature.h>
#include <ripple/protocol/Indexes.h>
#include <ripple/protocol/digest.h>
#include <test/jtx.h>
#include <test/jtx/Env.h>

#define BEAST_REQUIRE(x)     \
    {                        \
        BEAST_EXPECT(!!(x)); \
        if (!(x))            \
            return;          \
    }

namespace ripple {
namespace test {

inline std::unique_ptr<Config>
makeNetworkConfig(uint32_t networkID)
{
    using namespace test::jtx;
    return envconfig([&](std::unique_ptr<Config> cfg) {
        cfg->NETWORK_ID = networkID;
        return cfg;
    });
}

struct FixGovernanceHook_test : public beast::unit_test::suite
{
    uint256 const governHookHash = ripple::sha512Half_s(ripple::Slice(
        XahauGenesis::GovernanceHook.data(),
        XahauGenesis::GovernanceHook.size()));

    uint256 const rewardHookHash = ripple::sha512Half_s(ripple::Slice(
        XahauGenesis::RewardHook.data(),
        XahauGenesis::RewardHook.size()));

    void
    activateAmendment(jtx::Env& env, uint256 const& amendment)
    {
        auto const startLgr = env.current()->seq();
        env.app().openLedger().modify(
            [&](OpenView& view, beast::Journal j) -> bool {
                STTx tx(ttAMENDMENT, [&](auto& obj) {
                    obj.setAccountID(sfAccount, AccountID());
                    obj.setFieldH256(sfAmendment, amendment);
                    obj.setFieldU32(sfLedgerSequence, startLgr);
                    obj.setFieldU32(sfFlags, tfTestSuite);
                });

                uint256 txID = tx.getTransactionID();
                auto s = std::make_shared<ripple::Serializer>();
                tx.add(*s);
                env.app().getHashRouter().setFlags(txID, SF_PRIVATE2);
                view.rawTxInsert(txID, std::move(s), nullptr);

                return true;
            });

        env.close();
    }

    void
    testNormalUpdate(FeatureBitset features)
    {
        testcase("Normal update after genesis");
        using namespace jtx;
        using namespace XahauGenesis;

        Env env{
            *this,
            makeNetworkConfig(21337),
            features - featureXahauGenesis - fixGovernanceHook};

        // activate XahauGenesis first
        activateAmendment(env, featureXahauGenesis);

        // compute genesis account
        auto const genesisAccID = calcAccountID(
            generateKeyPair(
                KeyType::secp256k1, generateSeed("masterpassphrase"))
                .first);

        // verify genesis account hooks exist
        auto const genesisHookKL = keylet::hook(genesisAccID);
        auto genesisHookSLE = env.le(genesisHookKL);
        BEAST_REQUIRE(genesisHookSLE);

        auto const& genesisHooks = genesisHookSLE->getFieldArray(sfHooks);
        BEAST_REQUIRE(genesisHooks.size() >= 2);

        // record old governance hook hash
        uint256 const oldGovHash = genesisHooks[0].getFieldH256(sfHookHash);

        // record old reward hook hash
        uint256 const oldRewardHash = genesisHooks[1].getFieldH256(sfHookHash);

        // check if genesis hook[0] has HookParameters
        bool const hadParams = genesisHooks[0].isFieldPresent(sfHookParameters);
        STArray oldParams;
        if (hadParams)
            oldParams = genesisHooks[0].getFieldArray(sfHookParameters);

        // collect L1Membership account IDs and their old hashes
        // L1Membership includes all 9 accounts (5 independent L1 seats
        // + 4 L2 table accounts)
        struct MemberInfo
        {
            AccountID id;
            uint256 oldHash;
            bool hadParams;
            STArray oldParams;
        };
        std::vector<MemberInfo> memberInfos;

        auto const& l1src = TestL1Membership;
        for (auto const& [key, amount] : l1src)
        {
            auto const pk = parseBase58<PublicKey>(TokenType::NodePublic, key);
            if (!pk)
                continue;
            auto const accID = calcAccountID(*pk);
            auto const hookKL = keylet::hook(accID);
            auto hookSLE = env.le(hookKL);
            if (hookSLE)
            {
                auto const& hooks = hookSLE->getFieldArray(sfHooks);
                if (!hooks.empty() && hooks[0].isFieldPresent(sfHookHash))
                {
                    MemberInfo info;
                    info.id = accID;
                    info.oldHash = hooks[0].getFieldH256(sfHookHash);
                    info.hadParams = hooks[0].isFieldPresent(sfHookParameters);
                    if (info.hadParams)
                        info.oldParams =
                            hooks[0].getFieldArray(sfHookParameters);
                    memberInfos.push_back(std::move(info));
                }
            }
        }

        // get old hook definition ref count
        auto const oldGovDefKL = keylet::hookDefinition(oldGovHash);
        auto oldGovDefBefore = env.le(oldGovDefKL);
        BEAST_REQUIRE(oldGovDefBefore);

        // activate fixGovernanceHook
        activateAmendment(env, fixGovernanceHook);

        // compute expected new hash
        uint256 const newGovHash = ripple::sha512Half_s(
            ripple::Slice(GovernanceHook.data(), GovernanceHook.size()));

        // verify genesis account
        genesisHookSLE = env.le(genesisHookKL);
        BEAST_REQUIRE(genesisHookSLE);
        auto const& updatedGenesisHooks =
            genesisHookSLE->getFieldArray(sfHooks);
        BEAST_REQUIRE(updatedGenesisHooks.size() >= 2);

        // hook[0] should have the new hash (or same if unchanged)
        BEAST_EXPECT(
            updatedGenesisHooks[0].getFieldH256(sfHookHash) == newGovHash);

        // hook[1] (RewardHook) should be unchanged
        BEAST_EXPECT(
            updatedGenesisHooks[1].getFieldH256(sfHookHash) == oldRewardHash);

        // HookParameters on hook[0] should be preserved
        if (hadParams)
        {
            BEAST_EXPECT(
                updatedGenesisHooks[0].isFieldPresent(sfHookParameters));
            if (updatedGenesisHooks[0].isFieldPresent(sfHookParameters))
            {
                auto const& newParams =
                    updatedGenesisHooks[0].getFieldArray(sfHookParameters);
                BEAST_EXPECT(newParams.size() == oldParams.size());
            }
        }

        // verify L1Membership accounts
        for (auto const& info : memberInfos)
        {
            auto const hookKL = keylet::hook(info.id);
            auto hookSLE = env.le(hookKL);
            BEAST_REQUIRE(hookSLE);

            auto const& hooks = hookSLE->getFieldArray(sfHooks);
            BEAST_REQUIRE(!hooks.empty());
            BEAST_EXPECT(hooks[0].getFieldH256(sfHookHash) == newGovHash);

            // HookParameters should be preserved
            if (info.hadParams)
            {
                BEAST_EXPECT(hooks[0].isFieldPresent(sfHookParameters));
                if (hooks[0].isFieldPresent(sfHookParameters))
                {
                    auto const& newParams =
                        hooks[0].getFieldArray(sfHookParameters);
                    BEAST_EXPECT(newParams.size() == info.oldParams.size());
                }
            }
        }

        // verify new hook definition exists with correct ref count
        auto const newGovDefKL = keylet::hookDefinition(newGovHash);
        auto newGovDef = env.le(newGovDefKL);

        if (oldGovHash != newGovHash)
        {
            BEAST_REQUIRE(newGovDef);
            // ref count should be: 1 (genesis) + number of member accounts
            // updated
            uint64_t expectedRefCount = 1 + memberInfos.size();
            BEAST_EXPECT(
                newGovDef->getFieldU64(sfReferenceCount) == expectedRefCount);

            // old hook definition should be erased if ref count went to 0
            auto oldGovDefAfter = env.le(oldGovDefKL);
            BEAST_EXPECT(!oldGovDefAfter);
        }
        else
        {
            // if hashes are the same, nothing should have changed
            BEAST_EXPECT(!!newGovDef);
        }

        auto oldGovDefAfter = env.le(oldGovDefKL);
        BEAST_REQUIRE(!oldGovDefAfter);
    }

    void
    testNoExistingHook(FeatureBitset features)
    {
        testcase("No existing hook (genesis not activated)");
        using namespace jtx;

        Env env{
            *this,
            makeNetworkConfig(21337),
            features - featureXahauGenesis - fixGovernanceHook};

        // Do NOT activate XahauGenesis
        // Activate fixGovernanceHook directly
        activateAmendment(env, fixGovernanceHook);

        // verify genesis account has no hooks (should not crash)
        auto const genesisAccID = calcAccountID(
            generateKeyPair(
                KeyType::secp256k1, generateSeed("masterpassphrase"))
                .first);

        auto const genesisHookKL = keylet::hook(genesisAccID);
        auto genesisHookSLE = env.le(genesisHookKL);
        // Should not exist since genesis was never activated
        BEAST_EXPECT(!genesisHookSLE);
    }

    void
    run() override
    {
        using namespace test::jtx;
        auto const sa = supported_amendments();
        testNormalUpdate(sa);
        testNoExistingHook(sa);
    }
};

BEAST_DEFINE_TESTSUITE_PRIO(FixGovernanceHook, app, ripple, 2);

}  // namespace test
}  // namespace ripple
