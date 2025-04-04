//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2023 Ripple Labs Inc.

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

#include <ripple/basics/StringUtilities.h>
#include <ripple/beast/unit_test.h>
#include <ripple/protocol/SField.h>
#include <ripple/protocol/STData.h>

#include <arpa/inet.h>  // For htonl/ntohl (needed for serialization simulation)

namespace ripple {

// Helper function to create a Buffer from hex string
Buffer
buffer_from_hex(std::string const& hex)
{
    auto bytes = strUnHex(hex);
    if (!bytes)
        throw std::runtime_error("Invalid hex string for buffer");
    return Buffer(bytes->data(), bytes->size());
}

struct STData_test : public beast::unit_test::suite
{
    void
    testFields()
    {
        testcase("fields");

        auto const& sf = sfFunctionParameterValue;

        {
            // STI_UINT8
            Serializer s;
            unsigned char u8 = 1;

            STData s1(sf);
            s1.setFieldU8(u8);
            BEAST_EXPECT(s1.getFieldU8() == u8);
            s1.add(s);
            BEAST_EXPECT(strHex(s) == "001001");
            s.erase();

            STData s2(sf, u8);
            BEAST_EXPECT(s2.getFieldU8() == u8);
            s2.add(s);
            BEAST_EXPECT(strHex(s) == "001001");
        }

        {
            // STI_UINT16
            Serializer s;
            uint16_t u16 = 1U;

            STData s1(sf);
            s1.setFieldU16(u16);
            BEAST_EXPECT(s1.getFieldU16() == u16);
            s1.add(s);
            BEAST_EXPECT(strHex(s) == "00010001");
            s.erase();

            STData s2(sf, u16);
            BEAST_EXPECT(s2.getFieldU16() == u16);
            s2.add(s);
            BEAST_EXPECT(strHex(s) == "00010001");
        }

        {
            // STI_UINT32
            Serializer s;
            uint32_t u32 = 1U;

            STData s1(sf);
            s1.setFieldU32(u32);
            BEAST_EXPECT(s1.getFieldU32() == u32);
            s1.add(s);
            BEAST_EXPECT(strHex(s) == "000200000001");
            s.erase();

            STData s2(sf, u32);
            BEAST_EXPECT(s2.getFieldU32() == u32);
            s2.add(s);
            BEAST_EXPECT(strHex(s) == "000200000001");
        }

        {
            // STI_UINT64
            Serializer s;
            uint64_t u64 = 1U;

            STData s1(sf);
            s1.setFieldU64(u64);
            BEAST_EXPECT(s1.getFieldU64() == u64);
            s1.add(s);
            BEAST_EXPECT(strHex(s) == "00030000000000000001");
            s.erase();

            STData s2(sf, u64);
            BEAST_EXPECT(s2.getFieldU64() == u64);
            s2.add(s);
            BEAST_EXPECT(strHex(s) == "00030000000000000001");
        }

        {
            // STI_UINT128
            Serializer s;
            uint128 u128 = uint128(1);

            STData s1(sf);
            s1.setFieldH128(u128);
            BEAST_EXPECT(s1.getFieldH128() == u128);
            s1.add(s);
            BEAST_EXPECT(strHex(s) == "000400000000000000000000000000000001");
            s.erase();

            STData s2(sf, u128);
            BEAST_EXPECT(s2.getFieldH128() == u128);
            s2.add(s);
            BEAST_EXPECT(strHex(s) == "000400000000000000000000000000000001");
        }

        {
            // STI_UINT256
            Serializer s;
            uint256 u256 = uint256(1);

            STData s1(sf);
            s1.setFieldH256(u256);
            BEAST_EXPECT(s1.getFieldH256() == u256);
            s1.add(s);
            BEAST_EXPECT(
                strHex(s) ==
                "00050000000000000000000000000000000000000000000000000000000000"
                "000001");
            s.erase();

            STData s2(sf, u256);
            BEAST_EXPECT(s2.getFieldH256() == u256);
            s2.add(s);
            BEAST_EXPECT(
                strHex(s) ==
                "00050000000000000000000000000000000000000000000000000000000000"
                "000001");
        }
        {
            // TODO: STI_VL
        } {
            // STI_ACCOUNT
            Serializer s;
            AccountID account = AccountID(1);

            STData s1(sf);
            s1.setAccountID(account);
            BEAST_EXPECT(s1.getAccountID() == account);
            s1.add(s);
            BEAST_EXPECT(
                strHex(s) == "0008140000000000000000000000000000000000000001");
            s.erase();

            AccountID account2 = AccountID(2);
            STData s2(sf, account2);
            BEAST_EXPECT(s2.getAccountID() == account2);
            s2.add(s);
            BEAST_EXPECT(
                strHex(s) == "0008140000000000000000000000000000000000000002");
        }
        {
            // TODO: STI_AMOUNT
        }

        // read templated object
        // SOTemplate const sotOuter{
        //     {sf1Outer, soeREQUIRED},
        //     {sf2Outer, soeOPTIONAL},
        //     {sf3Outer, soeDEFAULT},
        //     {sf4, soeOPTIONAL},
        //     {sf5, soeDEFAULT},
        // };

        // {
        //     auto const st = [&]() {
        //         STObject s(sotOuter, sfGeneric);
        //         s.setFieldU32(sf1Outer, 1);
        //         s.setFieldU32(sf2Outer, 2);
        //         return s;
        //     }();

        //     BEAST_EXPECT(st[sf1Outer] == 1);
        //     BEAST_EXPECT(st[sf2Outer] == 2);
        //     BEAST_EXPECT(st[sf3Outer] == 0);
        //     BEAST_EXPECT(*st[~sf1Outer] == 1);
        //     BEAST_EXPECT(*st[~sf2Outer] == 2);
        //     BEAST_EXPECT(*st[~sf3Outer] == 0);
        //     BEAST_EXPECT(!!st[~sf1Outer]);
        //     BEAST_EXPECT(!!st[~sf2Outer]);
        //     BEAST_EXPECT(!!st[~sf3Outer]);
        // }

        // // write free object

        // {
        //     STObject st(sfGeneric);
        //     unexcept([&]() { st[sf1Outer]; });
        //     except([&]() { return st[sf1Outer] == 0; });
        //     BEAST_EXPECT(st[~sf1Outer] == std::nullopt);
        //     BEAST_EXPECT(st[~sf1Outer] == std::optional<std::uint32_t>{});
        //     BEAST_EXPECT(st[~sf1Outer] != std::optional<std::uint32_t>(1));
        //     BEAST_EXPECT(!st[~sf1Outer]);
        //     st[sf1Outer] = 2;
        //     BEAST_EXPECT(st[sf1Outer] == 2);
        //     BEAST_EXPECT(st[~sf1Outer] != std::nullopt);
        //     BEAST_EXPECT(st[~sf1Outer] == std::optional<std::uint32_t>(2));
        //     BEAST_EXPECT(!!st[~sf1Outer]);
        //     st[sf1Outer] = 1;
        //     BEAST_EXPECT(st[sf1Outer] == 1);
        //     BEAST_EXPECT(!!st[sf1Outer]);
        //     BEAST_EXPECT(!!st[~sf1Outer]);
        //     st[sf1Outer] = 0;
        //     BEAST_EXPECT(!st[sf1Outer]);
        //     BEAST_EXPECT(!!st[~sf1Outer]);
        //     st[~sf1Outer] = std::nullopt;
        //     BEAST_EXPECT(!st[~sf1Outer]);
        //     BEAST_EXPECT(st[~sf1Outer] == std::nullopt);
        //     BEAST_EXPECT(st[~sf1Outer] == std::optional<std::uint32_t>{});
        //     st[~sf1Outer] = std::nullopt;
        //     BEAST_EXPECT(!st[~sf1Outer]);
        //     except([&]() { return st[sf1Outer] == 0; });
        //     except([&]() { return *st[~sf1Outer]; });
        //     st[sf1Outer] = 1;
        //     BEAST_EXPECT(st[sf1Outer] == 1);
        //     BEAST_EXPECT(!!st[sf1Outer]);
        //     BEAST_EXPECT(!!st[~sf1Outer]);
        //     st[sf1Outer] = 3;
        //     st[sf2Outer] = st[sf1Outer];
        //     BEAST_EXPECT(st[sf1Outer] == 3);
        //     BEAST_EXPECT(st[sf2Outer] == 3);
        //     BEAST_EXPECT(st[sf2Outer] == st[sf1Outer]);
        //     st[sf1Outer] = 4;
        //     st[sf2Outer] = st[sf1Outer];
        //     BEAST_EXPECT(st[sf1Outer] == 4);
        //     BEAST_EXPECT(st[sf2Outer] == 4);
        //     BEAST_EXPECT(st[sf2Outer] == st[sf1Outer]);
        // }

        // // Write templated object

        // {
        //     STObject st(sotOuter, sfGeneric);
        //     BEAST_EXPECT(!!st[~sf1Outer]);
        //     BEAST_EXPECT(st[~sf1Outer] != std::nullopt);
        //     BEAST_EXPECT(st[sf1Outer] == 0);
        //     BEAST_EXPECT(*st[~sf1Outer] == 0);
        //     BEAST_EXPECT(!st[~sf2Outer]);
        //     BEAST_EXPECT(st[~sf2Outer] == std::nullopt);
        //     except([&]() { return st[sf2Outer] == 0; });
        //     BEAST_EXPECT(!!st[~sf3Outer]);
        //     BEAST_EXPECT(st[~sf3Outer] != std::nullopt);
        //     BEAST_EXPECT(st[sf3Outer] == 0);
        //     except([&]() { st[~sf1Outer] = std::nullopt; });
        //     st[sf1Outer] = 1;
        //     BEAST_EXPECT(st[sf1Outer] == 1);
        //     BEAST_EXPECT(*st[~sf1Outer] == 1);
        //     BEAST_EXPECT(!!st[~sf1Outer]);
        //     st[sf1Outer] = 0;
        //     BEAST_EXPECT(st[sf1Outer] == 0);
        //     BEAST_EXPECT(*st[~sf1Outer] == 0);
        //     BEAST_EXPECT(!!st[~sf1Outer]);
        //     st[sf2Outer] = 2;
        //     BEAST_EXPECT(st[sf2Outer] == 2);
        //     BEAST_EXPECT(*st[~sf2Outer] == 2);
        //     BEAST_EXPECT(!!st[~sf2Outer]);
        //     st[~sf2Outer] = std::nullopt;
        //     except([&]() { return *st[~sf2Outer]; });
        //     BEAST_EXPECT(!st[~sf2Outer]);
        //     st[sf3Outer] = 3;
        //     BEAST_EXPECT(st[sf3Outer] == 3);
        //     BEAST_EXPECT(*st[~sf3Outer] == 3);
        //     BEAST_EXPECT(!!st[~sf3Outer]);
        //     st[sf3Outer] = 2;
        //     BEAST_EXPECT(st[sf3Outer] == 2);
        //     BEAST_EXPECT(*st[~sf3Outer] == 2);
        //     BEAST_EXPECT(!!st[~sf3Outer]);
        //     st[sf3Outer] = 0;
        //     BEAST_EXPECT(st[sf3Outer] == 0);
        //     BEAST_EXPECT(*st[~sf3Outer] == 0);
        //     BEAST_EXPECT(!!st[~sf3Outer]);
        //     except([&]() { st[~sf3Outer] = std::nullopt; });
        //     BEAST_EXPECT(st[sf3Outer] == 0);
        //     BEAST_EXPECT(*st[~sf3Outer] == 0);
        //     BEAST_EXPECT(!!st[~sf3Outer]);
        // }

        // // coercion operator to std::optional

        // {
        //     STObject st(sfGeneric);
        //     auto const v = ~st[~sf1Outer];
        //     static_assert(
        //         std::is_same<
        //             std::decay_t<decltype(v)>,
        //             std::optional<std::uint32_t>>::value,
        //         "");
        // }

        // // UDT scalar fields

        // {
        //     STObject st(sfGeneric);
        //     st[sfAmount] = STAmount{};
        //     st[sfAccount] = AccountID{};
        //     st[sfDigest] = uint256{};
        //     [&](STAmount) {}(st[sfAmount]);
        //     [&](AccountID) {}(st[sfAccount]);
        //     [&](uint256) {}(st[sfDigest]);
        // }

        // // STBlob and slice

        // {
        //     {
        //         STObject st(sfGeneric);
        //         Buffer b(1);
        //         BEAST_EXPECT(!b.empty());
        //         st[sf4] = std::move(b);
        //         BEAST_EXPECT(b.empty());
        //         BEAST_EXPECT(Slice(st[sf4]).size() == 1);
        //         st[~sf4] = std::nullopt;
        //         BEAST_EXPECT(!~st[~sf4]);
        //         b = Buffer{2};
        //         st[sf4] = Slice(b);
        //         BEAST_EXPECT(b.size() == 2);
        //         BEAST_EXPECT(Slice(st[sf4]).size() == 2);
        //         st[sf5] = st[sf4];
        //         BEAST_EXPECT(Slice(st[sf4]).size() == 2);
        //         BEAST_EXPECT(Slice(st[sf5]).size() == 2);
        //     }
        //     {
        //         STObject st(sotOuter, sfGeneric);
        //         BEAST_EXPECT(st[sf5] == Slice{});
        //         BEAST_EXPECT(!!st[~sf5]);
        //         BEAST_EXPECT(!!~st[~sf5]);
        //         Buffer b(1);
        //         st[sf5] = std::move(b);
        //         BEAST_EXPECT(b.empty());
        //         BEAST_EXPECT(Slice(st[sf5]).size() == 1);
        //         st[~sf4] = std::nullopt;
        //         BEAST_EXPECT(!~st[~sf4]);
        //     }
        // }
    }

    void
    run() override
    {
        testFields();
    }
};

BEAST_DEFINE_TESTSUITE(STData, protocol, ripple);

}  // namespace ripple
