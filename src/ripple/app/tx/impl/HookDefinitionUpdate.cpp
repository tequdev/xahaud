//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2025 XRPL-Labs

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

#include <ripple/app/hook/applyHook.h>
#include <ripple/app/tx/impl/HookDefinitionUpdate.h>
#include <ripple/basics/Log.h>
#include <ripple/ledger/View.h>
#include <ripple/protocol/Feature.h>
#include <ripple/protocol/Indexes.h>
#include <ripple/protocol/TxFlags.h>
#include <ripple/protocol/st.h>
#include "ripple/protocol/SField.h"
#include "ripple/protocol/TER.h"

namespace ripple {

NotTEC
HookDefinitionUpdate::preflight(PreflightContext const& ctx)
{
    if (!ctx.rules.enabled(featureHookFeeV2))
        return temDISABLED;

    auto const& tx = ctx.tx;
    auto const& j = ctx.j;

    if (auto const ret = preflight1(ctx); !isTesSuccess(ret))
        return ret;

    // TODO: check flags

    return preflight2(ctx);
}

TER
HookDefinitionUpdate::preclaim(PreclaimContext const& ctx)
{
    auto const& view = ctx.view;
    auto const& tx = ctx.tx;

    auto exists =
        view.exists(keylet::hookDefinition(tx.getFieldH256(sfHookHash)));
    if (!exists)
        return tecNO_ENTRY;

    return tesSUCCESS;
}

TER
HookDefinitionUpdate::doApply()
{
    auto& view = ctx_.view();
    auto const& tx = ctx_.tx;

    auto hookDefSle =
        view.peek(keylet::hookDefinition(tx.getFieldH256(sfHookHash)));
    if (!hookDefSle)
        return tefINTERNAL;

    Blob hook = hookDefSle->getFieldVL(sfCreateCode);

    auto const result =
        hook::doValidateGuards(tx, hook, view.rules(), ctx_.journal);
    if (!result)
        return tecINTERNAL;

    auto const [hookCost, callbackCost] = *result;

    {
        // if result is same as old, don't update sle
        if (hookCost == hookDefSle->getFieldU64(sfHookCost) &&
            callbackCost == hookDefSle->getFieldU64(sfHookCallbackCost))
            return tesSUCCESS;
    }

    {
        // set new cost fields
        hookDefSle->setFieldU64(sfHookCost, hookCost);
        if (callbackCost > 0)
            hookDefSle->setFieldU64(sfHookCallbackCost, callbackCost);
        else if (hookDefSle->isFieldPresent(sfHookCallbackCost))
            hookDefSle->makeFieldAbsent(sfHookCallbackCost);
    }

    {
        // remove old fee fields
        if (hookDefSle->isFieldPresent(sfFee))
            hookDefSle->makeFieldAbsent(sfFee);
        if (hookDefSle->isFieldPresent(sfHookCallbackFee))
            hookDefSle->makeFieldAbsent(sfHookCallbackFee);
    }

    view.update(hookDefSle);

    return tesSUCCESS;
}

XRPAmount
HookDefinitionUpdate::calculateBaseFee(ReadView const& view, STTx const& tx)
{
    auto const baseFee = Transactor::calculateBaseFee(view, tx);

    // TODO: add a cost based on the size of the hook code?

    return baseFee;
}

}  // namespace ripple
