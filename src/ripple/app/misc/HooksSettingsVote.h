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

#ifndef RIPPLE_APP_MISC_HOOKSSETTINGSVOTE_H_INCLUDED
#define RIPPLE_APP_MISC_HOOKSSETTINGSVOTE_H_INCLUDED

#include <ripple/basics/BasicConfig.h>
#include <ripple/ledger/ReadView.h>
#include <ripple/protocol/STValidation.h>
#include <ripple/protocol/SystemParameters.h>
#include <ripple/shamap/SHAMap.h>

namespace ripple {

/** Manager to process hooks settings votes. */
class HooksSettingsVote
{
public:
    virtual ~HooksSettingsVote() = default;

    /** Add local hooks settings preference to validation.

        @param lastClosedLedger
        @param baseValidation
    */
    virtual void
    doValidation(
        HooksSettings const& lastHooksSettings,
        Rules const& rules,
        STValidation& val) = 0;

    /** Cast our local vote on the fee.

        @param lastClosedLedger
        @param initialPosition
    */
    virtual void
    doVoting(
        std::shared_ptr<ReadView const> const& lastClosedLedger,
        std::vector<std::shared_ptr<STValidation>> const& parentValidations,
        std::shared_ptr<SHAMap> const& initialPosition) = 0;
};

struct HooksSettingsSetup;
/** Create an instance of the HooksSettingsVote logic.
    @param setup The hooks settings to vote for.
    @param journal Where to log.
*/
std::unique_ptr<HooksSettingsVote>
make_HooksSettingsVote(HooksSettingsSetup const& setup, beast::Journal journal);

}  // namespace ripple

#endif
