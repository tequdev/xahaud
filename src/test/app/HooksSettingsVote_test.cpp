//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2019 Ripple Labs Inc.

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

#include <ripple/app/misc/HooksSettingsVote.h>
#include <ripple/basics/BasicConfig.h>
#include <test/jtx.h>

namespace ripple {
namespace test {

class HooksSettingsVote_test : public beast::unit_test::suite
{
    void
    testSetup()
    {
        HooksSettingsSetup const defaultSetup;
        {
            // defaults
            Section config;
            auto setup = setup_HooksSettingsVote(config);
            BEAST_EXPECT(setup.hook_parameters_size == defaultSetup.hook_parameters_size);
            BEAST_EXPECT(setup.hook_parameter_value_size == defaultSetup.hook_parameter_value_size);
            BEAST_EXPECT(setup.hook_state_data_size == defaultSetup.hook_state_data_size);
        }
        {
            Section config;
            config.append(
                {"hook_parameters_size = 32",
                 "hook_parameter_value_size = 1024",
                 "hook_state_data_size = 2048"});
            auto setup = setup_HooksSettingsVote(config);
            BEAST_EXPECT(setup.hook_parameters_size == 32);
            BEAST_EXPECT(setup.hook_parameter_value_size == 1024);
            BEAST_EXPECT(setup.hook_state_data_size == 2048);
        }
        {
            Section config;
            config.append(
                {"hook_parameters_size = blah",
                 "hook_parameter_value_size = yada",
                 "hook_state_data_size = foo"});
            // Illegal values are ignored, and the defaults left unchanged
            auto setup = setup_HooksSettingsVote(config);
            BEAST_EXPECT(setup.hook_parameters_size == defaultSetup.hook_parameters_size);
            BEAST_EXPECT(setup.hook_parameter_value_size == defaultSetup.hook_parameter_value_size);
            BEAST_EXPECT(setup.hook_state_data_size == defaultSetup.hook_state_data_size);
        }
        {
            Section config;
            config.append(
                {"hook_parameters_size = -16",
                 "hook_parameter_value_size = -1024",
                 "hook_state_data_size = -2048"});
            // Illegal values are ignored, and the defaults left unchanged
            auto setup = setup_HooksSettingsVote(config);
            BEAST_EXPECT(setup.hook_parameters_size == static_cast<std::uint16_t>(-16));
            BEAST_EXPECT(setup.hook_parameter_value_size == static_cast<std::uint16_t>(-1024));
            BEAST_EXPECT(setup.hook_state_data_size == static_cast<std::uint16_t>(-2048));
        }
        {
            const auto big64 = std::to_string(
                static_cast<std::uint64_t>(
                    std::numeric_limits<XRPAmount::value_type>::max()) +
                1);
            Section config;
            config.append(
                {"hook_parameters_size = " + big64,
                 "hook_parameter_value_size = " + big64,
                 "hook_state_data_size = " + big64});
            // Illegal values are ignored, and the defaults left unchanged
            auto setup = setup_HooksSettingsVote(config);
            BEAST_EXPECT(setup.hook_parameters_size == defaultSetup.hook_parameters_size);
            BEAST_EXPECT(setup.hook_parameter_value_size == defaultSetup.hook_parameter_value_size);
            BEAST_EXPECT(setup.hook_state_data_size == defaultSetup.hook_state_data_size);
        }
    }

    void
    run() override
    {
        testSetup();
    }
};

BEAST_DEFINE_TESTSUITE(HooksSettingsVote, server, ripple);

}  // namespace test
}  // namespace ripple
