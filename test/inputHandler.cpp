/*
Date: 16/06/2024

Description: This file contains the tests for the inputHandler.cpp module.

Notes: x
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <string>
#include "../include/tools.h"
#include "../src/include/inputHandler.h"

namespace Fetcher
{
        // Test for catching invalid user input in the userInputValidator() function - empty argument
        TEST(InputHandlerTest, inputHandler1)
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
        TEST(InputHandlerTest, inputHandler2)
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
        TEST(InputHandlerTest, inputHandler3)
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

        // Check date validation - incorrect length
        TEST(InputHandlerTest, inputHandler4)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

                // Log
                spdlog::info("{} test started. Checking for invalid date input...", testName);

                // Invalid date format
                std::vector<std::string> args = {"2000-1-1", "2000-01-01"};

                // Argument names
                std::vector<std::string> argNames = {"from", "to"};

                // Catch the invalid user input exception
                ASSERT_THROW(InputHandler::checkValidDateFormat(args, argNames), std::invalid_argument);
        }

        // Check date validation - incorrect day date
        TEST(InputHandlerTest, inputHandler5)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

                // Log
                spdlog::info("{} test started. Checking for invalid date input...", testName);

                // Invalid date format
                std::vector<std::string> args = {"2000-01-32", "2000-01-00"};

                // Argument names
                std::vector<std::string> argNames = {"from", "to"};

                // Catch the invalid user input exception
                ASSERT_THROW(InputHandler::checkValidDateFormat(args, argNames), std::invalid_argument);
        }

        // Correct url created using Polygons API
        TEST(InputHandlerTest, inputHandler6)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                std::string filePath = "../test/data/" + testName + ".txt";

                // Log
                spdlog::info("{} test started. Checking for valid Polygon URL creation...", testName);

                // Expected URL
                Tools::URL expectedURLs = Tools::readFileContents(filePath);

                // Actual URL
                Tools::URL actualURL = InputHandler::createUrl("SPY", "2023-01-09", "2023-01-10", "4", "hour", "polygon", "apiKey");

                // Assert that the actual URL is equal to the expected URL
                ASSERT_EQ(actualURL, expectedURLs);
        }
}