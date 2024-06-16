/*
Date: 16/06/2024

Description: This file contains the tests for the inputHandler.cpp module.

Notes: x
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <string>
#include "../src/include/inputHandler.h"

namespace Fetcher
{
        // Test for catching invalid user input in the userInputValidator() function - empty argument
        TEST(InputHandlerTest, userInputValidatorTest)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

                // Log
                spdlog::info("{} test started. Catching invalid user input...", testName);

                // Invalid user input - empty time frame argument (invalid eg. in this case: Fetcher::fetchHistoricalData("AAPL", "2021-01-01", "2021-01-05", "", "fmp", "API_KEY");)
                std::vector<std::string> args = {"AAPL", "2021-01-01", "2021-01-05", "", "fmp", "vKoDVGFjjGHf5uWq3O0ztQ0w6CfMfxIa"};

                // Argument names
                std::vector<std::string> argNames = {"tickerSymbol", "fromDate", "toDate", "timeFrame", "api", "apiKey"};

                // Catch the invalid user input exception
                ASSERT_THROW(InputHandler::userInputValidator(args, argNames), std::invalid_argument);
        }

        // Test for catching invalid user input in the userInputValidator() function - missing argument
        TEST(InputHandlerTest, userInputValidatorTest2)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

                // Log
                spdlog::info("{} test started. Catching invalid user input...", testName);

                // Invalid user input - missing time frame argument (invalid eg. in this case: Fetcher::fetchHistoricalData("AAPL", "2021-01-01", "2021-01-05", "fmp", "vKoDVGFjjGHf5uWq3O0ztQ0w6CfMfxIa");)
                std::vector<std::string> args = {"AAPL", "2021-01-01", "2021-01-05", "fmp", "vKoDVGFjjGHf5uWq3O0ztQ0w6CfMfxIa"};

                // Argument names
                std::vector<std::string> argNames = {"tickerSymbol", "fromDate", "toDate", "timeFrame", "api", "apiKey"};

                // Catch the invalid user input exception
                ASSERT_THROW(InputHandler::userInputValidator(args, argNames), std::invalid_argument);
        }

        // Test for catching invalid user input in the userInputValidator() function - unsupported URL
        TEST(InputHandlerTest, userInputValidatorTest3)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

                // Log
                spdlog::info("{} test started. Catching invalid user input...", testName);

                // Invalid user input - unsupported URL
                std::vector<std::string> args = {"google.com"};

                // Argument names
                std::vector<std::string> argNames = {"url"};

                // Catch the invalid user input exception
                ASSERT_THROW(InputHandler::userInputValidator(args, argNames), std::invalid_argument);
        }
}