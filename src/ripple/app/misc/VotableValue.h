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
#include <ripple/beast/utility/Journal.h>
#include <ripple/protocol/STValidation.h>
#include <ripple/protocol/st.h>

namespace ripple {

namespace detail {

template <typename T>
class VotableValue
{
private:
    using value_type = T;
    value_type const current_;  // The current setting
    value_type const target_;   // The setting we want
    std::map<value_type, int> voteMap_;

public:
    VotableValue(value_type current, value_type target)
        : current_(current), target_(target)
    {
        // Add our vote
        ++voteMap_[target_];
    }

    void
    addVote(value_type vote)
    {
        ++voteMap_[vote];
    }

    void
    noVote()
    {
        addVote(current_);
    }

    value_type
    current() const
    {
        return current_;
    }

    std::pair<value_type, bool>
    getVotes() const;
};

template <typename T>
auto
VotableValue<T>::getVotes() const -> std::pair<value_type, bool>
{
    value_type ourVote = current_;
    int weight = 0;
    for (auto const& [key, val] : voteMap_)
    {
        // Take most voted value between current and target, inclusive
        if ((key <= std::max(target_, current_)) &&
            (key >= std::min(target_, current_)) && (val > weight))
        {
            ourVote = key;
            weight = val;
        }
    }

    return {ourVote, ourVote != current_};
}

}  // namespace detail
}
