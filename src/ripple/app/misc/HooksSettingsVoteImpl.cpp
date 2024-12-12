//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

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

#include <ripple/app/ledger/Ledger.h>
#include <ripple/app/main/Application.h>
#include <ripple/app/misc/HooksSettingsVote.h>
#include <ripple/basics/BasicConfig.h>
#include <ripple/beast/utility/Journal.h>
#include <ripple/protocol/STValidation.h>
#include <ripple/protocol/st.h>
#include <ripple/app/misc/VotableValue.h>

namespace ripple {

class HooksSettingsVoteImpl : public HooksSettingsVote
{
private:
    HooksSettingsSetup target_;
    beast::Journal const journal_;

public:
    HooksSettingsVoteImpl(HooksSettingsSetup const& setup, beast::Journal journal);

    void
    doValidation(HooksSettings const& lastHooksSettings, Rules const& rules, STValidation& val)
        override;

    void
    doVoting(
        std::shared_ptr<ReadView const> const& lastClosedLedger,
        std::vector<std::shared_ptr<STValidation>> const& parentValidations,
        std::shared_ptr<SHAMap> const& initialPosition) override;
};

//--------------------------------------------------------------------------

HooksSettingsVoteImpl::HooksSettingsVoteImpl(HooksSettingsSetup const& setup, beast::Journal journal)
    : target_(setup), journal_(journal)
{
}

void
HooksSettingsVoteImpl::doValidation(
    HooksSettings const& lastHooksSettings,
    Rules const& rules,
    STValidation& v)
{
    // Values should always be in a valid range (because the voting process
    // will ignore out-of-range values) but if we detect such a case, we do
    // not send a value.

    auto vote = [&v, this](
                    auto const current,
                    uint16_t target,
                    const char* name,
                    auto const& sfield) {
        if (current != target)
        {
            JLOG(journal_.info())
                << "Voting for " << name << " of " << target;

            v[sfield] = target;
        }
    };
    vote(lastHooksSettings.hook_parameters_size, target_.hook_parameters_size, "hook_parameters_size", sfHookParametersSize);
    vote(lastHooksSettings.hook_parameter_value_size, target_.hook_parameter_value_size, "hook_parameter_value_size", sfHookParameterValueSize);
    vote(lastHooksSettings.hook_state_data_size, target_.hook_state_data_size, "hook_state_data_size", sfHookStateDataSize);
}

void
HooksSettingsVoteImpl::doVoting(
    std::shared_ptr<ReadView const> const& lastClosedLedger,
    std::vector<std::shared_ptr<STValidation>> const& set,
    std::shared_ptr<SHAMap> const& initialPosition)
{
    // LCL must be flag ledger
    assert(lastClosedLedger && isFlagLedger(lastClosedLedger->seq()));

    detail::VotableValue<uint16_t> hook_parameters_size_vote(
        lastClosedLedger->hooksSettings().hook_parameters_size, target_.hook_parameters_size);

    detail::VotableValue<uint16_t> hook_parameter_value_size_vote(
        lastClosedLedger->hooksSettings().hook_parameter_value_size, target_.hook_parameter_value_size);

    detail::VotableValue<uint16_t> hook_state_data_size_vote(
        lastClosedLedger->hooksSettings().hook_state_data_size, target_.hook_state_data_size);

    auto doVote = [](std::shared_ptr<STValidation> const& val,
                        detail::VotableValue<uint16_t>& value,
                        SF_UINT16 const& size) {
        if (auto const vote = ~val->at(~size))
        {
            value.addVote(vote.value());
        }
        else
        {
            value.noVote();
        }
    };

    for (auto const& val : set)
    {
        if (!val->isTrusted())
            continue;
        doVote(val, hook_parameters_size_vote, sfHookParametersSize);
        doVote(val, hook_parameter_value_size_vote, sfHookParameterValueSize);
        doVote(val, hook_state_data_size_vote, sfHookStateDataSize);
    }

    // choose our positions
    // TODO: Use structured binding once LLVM issue
    // https://github.com/llvm/llvm-project/issues/48582
    // is fixed.
    auto const hook_parameters_size = hook_parameters_size_vote.getVotes();
    auto const hook_parameter_value_size = hook_parameter_value_size_vote.getVotes();
    auto const hook_state_data_size = hook_state_data_size_vote.getVotes();

    auto const seq = lastClosedLedger->info().seq + 1;

    // add transactions to our position
    if (hook_parameters_size.second || hook_parameter_value_size.second || hook_state_data_size.second)
    {
        JLOG(journal_.warn())
            << "We are voting for a hooks settings change: " << hook_parameters_size.first << "/"
            << hook_parameter_value_size.first << "/" << hook_state_data_size.first;

        STTx hooksSettingsTx(ttSET_HOOKS_SETTINGS, [=](auto& obj) {
            obj[sfAccount] = AccountID();
            obj[sfLedgerSequence] = seq;

            obj[sfHookParametersSize] = hook_parameters_size.first;
            obj[sfHookParameterValueSize] = hook_parameter_value_size.first;
            obj[sfHookStateDataSize] = hook_state_data_size.first;
        });

        uint256 txID = hooksSettingsTx.getTransactionID();

        JLOG(journal_.warn()) << "Vote: " << txID;

        Serializer s;
        hooksSettingsTx.add(s);

        if (!initialPosition->addGiveItem(
                SHAMapNodeType::tnTRANSACTION_NM,
                make_shamapitem(txID, s.slice())))
        {
            JLOG(journal_.warn()) << "Ledger already had hooks settings change";
        }
    }
}

//------------------------------------------------------------------------------

std::unique_ptr<HooksSettingsVote>
make_HooksSettingsVote(HooksSettingsSetup const& setup, beast::Journal journal)
{
    return std::make_unique<HooksSettingsVoteImpl>(setup, journal);
}

}  // namespace ripple
