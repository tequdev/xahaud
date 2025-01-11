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

#ifndef RIPPLE_PROTOCOL_TXFLAGS_H_INCLUDED
#define RIPPLE_PROTOCOL_TXFLAGS_H_INCLUDED

#include <cstdint>
#include <map>

#define TO_ENUM(name, value) name = value,
#define TO_MAP(name, value) {#name, value},

#define TxFlags(name, macro)                 \
    enum name : uint32_t { macro(TO_ENUM) }; \
    static std::map<std::string, int> const name##Map = {macro(TO_MAP)};
namespace ripple {

/** Transaction flags.

    These flags are specified in a transaction's 'Flags' field and modify the
    behavior of that transaction.

    There are two types of flags:

        (1) Universal flags: these are flags which apply to, and are interpreted
                             the same way by, all transactions, except, perhaps,
                             to special pseudo-transactions.

        (2) Tx-Specific flags: these are flags which are interpreted according
                               to the type of the transaction being executed.
                               That is, the same numerical flag value may have
                               different effects, depending on the transaction
                               being executed.

    @note The universal transaction flags occupy the high-order 8 bits. The
          tx-specific flags occupy the remaining 24 bits.

    @warning Transaction flags form part of the protocol. **Changing them
             should be avoided because without special handling, this will
             result in a hard fork.**

    @ingroup protocol
*/

// Formatting equals sign aligned 4 spaces after longest prefix, except for
// wrapped lines
// clang-format off
// Universal Transaction flags:
#define UNIVERSAL_XMACRO(ENTRY)\
 ENTRY(tfFullyCanonicalSig, 0x80000000)
TxFlags(UniversalFlags, UNIVERSAL_XMACRO);

constexpr std::uint32_t tfUniversal                        = tfFullyCanonicalSig;
constexpr std::uint32_t tfUniversalMask                    = ~tfUniversal;

// AccountSet flags:
#define ACCOUNT_SET_XMACRO(ENTRY)\
 ENTRY(tfRequireDestTag, 0x00010000) \
 ENTRY(tfOptionalDestTag, 0x00020000) \
 ENTRY(tfRequireAuth, 0x00040000) \
 ENTRY(tfOptionalAuth, 0x00080000) \
 ENTRY(tfDisallowXRP, 0x00100000) \
 ENTRY(tfAllowXRP, 0x00200000)
TxFlags(AccountSetFlags, ACCOUNT_SET_XMACRO);

constexpr std::uint32_t tfAccountSetMask =
    ~(tfUniversal | tfRequireDestTag | tfOptionalDestTag | tfRequireAuth |
      tfOptionalAuth | tfDisallowXRP | tfAllowXRP);

// AccountSet SetFlag/ClearFlag values
#define ACCOUNT_FLAGS_XMACRO(ENTRY)\
 ENTRY(asfRequireDest, 1) \
 ENTRY(asfRequireAuth, 2) \
 ENTRY(asfDisallowXRP, 3) \
 ENTRY(asfDisableMaster, 4) \
 ENTRY(asfAccountTxnID, 5) \
 ENTRY(asfNoFreeze, 6) \
 ENTRY(asfGlobalFreeze, 7) \
 ENTRY(asfDefaultRipple, 8) \
 ENTRY(asfDepositAuth, 9) \
 ENTRY(asfAuthorizedNFTokenMinter, 10) \
 ENTRY(asfTshCollect, 11) \
 ENTRY(asfDisallowIncomingNFTokenOffer, 12) \
 ENTRY(asfDisallowIncomingCheck, 13) \
 ENTRY(asfDisallowIncomingPayChan, 14) \
 ENTRY(asfDisallowIncomingTrustline, 15) \
 ENTRY(asfDisallowIncomingRemit, 16)
TxFlags(AccountFlags, ACCOUNT_FLAGS_XMACRO);

// OfferCreate flags:
#define OFFER_CREATE_XMACRO(ENTRY)\
 ENTRY(tfPassive, 0x00010000) \
 ENTRY(tfImmediateOrCancel, 0x00020000) \
 ENTRY(tfFillOrKill, 0x00040000) \
 ENTRY(tfSell, 0x00080000)
TxFlags(OfferCreateFlags, OFFER_CREATE_XMACRO);

constexpr std::uint32_t tfOfferCreateMask =
    ~(tfUniversal | tfPassive | tfImmediateOrCancel | tfFillOrKill | tfSell);

// Payment flags:
#define PAYMENT_XMACRO(ENTRY)\
 ENTRY(tfNoRippleDirect, 0x00010000) \
 ENTRY(tfPartialPayment, 0x00020000) \
 ENTRY(tfLimitQuality, 0x00040000)
TxFlags(PaymentFlags, PAYMENT_XMACRO);

constexpr std::uint32_t tfPaymentMask =
    ~(tfUniversal | tfPartialPayment | tfLimitQuality | tfNoRippleDirect);

// TrustSet flags:
#define TRUST_SET_XMACRO(ENTRY)\
 ENTRY(tfSetfAuth, 0x00010000) \
 ENTRY(tfSetNoRipple, 0x00020000) \
 ENTRY(tfClearNoRipple, 0x00040000) \
 ENTRY(tfSetFreeze, 0x00100000) \
 ENTRY(tfClearFreeze, 0x00200000)
TxFlags(TrustSetFlags, TRUST_SET_XMACRO);

constexpr std::uint32_t tfTrustSetMask =
    ~(tfUniversal | tfSetfAuth | tfSetNoRipple | tfClearNoRipple | tfSetFreeze |
      tfClearFreeze);

// EnableAmendment flags:
#define ENABLE_AMENDMENT_XMACRO(ENTRY)\
 ENTRY(tfGotMajority, 0x00010000) \
 ENTRY(tfLostMajority, 0x00020000) \
 ENTRY(tfTestSuite, 0x80000000)
TxFlags(EnableAmendmentFlags, ENABLE_AMENDMENT_XMACRO);

// PaymentChannelClaim flags:
#define PAYMENT_CHANNEL_CLAIM_XMACRO(ENTRY)\
 ENTRY(tfRenew, 0x00010000) \
 ENTRY(tfClose, 0x00020000)
TxFlags(PaymentChannelClaimFlags, PAYMENT_CHANNEL_CLAIM_XMACRO);
constexpr std::uint32_t tfPayChanClaimMask = ~(tfUniversal | tfRenew | tfClose);

// NFTokenMint flags:
#define NFTOKEN_MINT_XMACRO(ENTRY)\
 ENTRY(tfBurnable, 0x00000001) \
 ENTRY(tfOnlyXRP, 0x00000002) \
 ENTRY(tfTrustLine, 0x00000004) \
 ENTRY(tfTransferable, 0x00000008) \
 ENTRY(tfStrongTSH, 0x00008000)
TxFlags(NFTokenMintFlags, NFTOKEN_MINT_XMACRO);

constexpr std::uint32_t const tfNFTokenMintOldMask =
    ~(tfUniversal | tfBurnable | tfOnlyXRP | tfTrustLine | tfTransferable | tfStrongTSH);

// Prior to fixRemoveNFTokenAutoTrustLine, transfer of an NFToken between
// accounts allowed a TrustLine to be added to the issuer of that token
// without explicit permission from that issuer.  This was enabled by
// minting the NFToken with the tfTrustLine flag set.
//
// That capability could be used to attack the NFToken issuer.  It
// would be possible for two accounts to trade the NFToken back and forth
// building up any number of TrustLines on the issuer, increasing the
// issuer's reserve without bound.
//
// The fixRemoveNFTokenAutoTrustLine amendment disables minting with the
// tfTrustLine flag as a way to prevent the attack.  But until the
// amendment passes we still need to keep the old behavior available.

constexpr std::uint32_t const tfNFTokenMintMask =
    ~(tfUniversal | tfBurnable | tfOnlyXRP | tfTransferable | tfStrongTSH);

// NFTokenCreateOffer flags:
#define NFTOKEN_CREATE_OFFER_XMACRO(ENTRY)\
 ENTRY(tfSellNFToken, 0x00000001)
TxFlags(NFTokenCreateOfferFlags, NFTOKEN_CREATE_OFFER_XMACRO);

constexpr std::uint32_t const tfNFTokenCreateOfferMask =
    ~(tfUniversal | tfSellNFToken);

// NFTokenCancelOffer flags:
constexpr std::uint32_t const tfNFTokenCancelOfferMask     = ~(tfUniversal);

// NFTokenAcceptOffer flags:
constexpr std::uint32_t const tfNFTokenAcceptOfferMask     = ~tfUniversal;

// URITokenMint flags:
// tfBurnable is duplicate of tfBurnable in NFTokenMintFlags
static std::map<std::string, int> const URITokenMintMap = {
    {"tfBurnable", tfBurnable},
};
constexpr std::uint32_t const tfURITokenMintMask = ~(tfUniversal | tfBurnable);
constexpr std::uint32_t const tfURITokenNonMintMask = ~tfUniversal;

// ClaimReward flags:
#define CLAIM_REWARD_XMACRO(ENTRY)\
 ENTRY(tfOptOut, 0x00000001)
TxFlags(ClaimRewardFlags, CLAIM_REWARD_XMACRO);
constexpr std::uint32_t const tfClaimRewardMask = ~(tfUniversal | tfOptOut);

// clang-format on

}  // namespace ripple

#endif
