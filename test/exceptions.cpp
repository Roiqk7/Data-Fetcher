/*
Date: 17/06/2024

Description: This file contains the tests for the exceptions.cpp module.

Notes: x
*/

#include <gtest/gtest.h>
#include <json/json.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include "tools.h"
#include "../src/include/exceptions.h"
#include "../src/include/fetcher.h"
#include "../src/include/flowControl.h"
#include "../src/include/inputHandler.h"

namespace Fetcher
{
        // Test for the HTTPRequestFailed exception
        TEST(ExceptionsTest, exceptionsTest1)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

                // Log
                spdlog::info("{} test started. Catching HTTP Request Failed...", testName);

                // Wrong URL
                std::string url = "wrongUrl";

                // Read buffer
                std::string readBuffer;

                // Catch the HTTPRequestFailed exception
                ASSERT_THROW(Fetcher::handleRequest(url, readBuffer), Exceptions::HTTPRequestFailed);
        }

        // Test for the FailedToParseRequestedData exception
        TEST(ExceptionsTest, exceptionsTest2)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

                // Log
                spdlog::info("{} test started. Catching Failed To Parse Requested Data...", testName);

                // Read buffer
                std::string malformedReadBuffer = "{ \"key\": \"value\""; // Missing closing brace

                // Catch the FailedToParseRequestedData exception
                ASSERT_THROW(Fetcher::parseRequestedData(malformedReadBuffer), Exceptions::FailedToParseRequestedData);
        }

        // Test for the ApiResponseError exception
        TEST(ExceptionsTest, exceptionsTest3)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();

                // Log
                spdlog::info("{} test started. Catching API Response Error...", testName);

                // Invalid URL - invalid API key
                Tools::URL url = "https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=********";
                InputHandler::ProcessedUserInput processedUserInput = InputHandler::ProcessedUserInput(url);

                // Catch the ApiResponseError exception
                ASSERT_THROW(FlowControl::runProgram(processedUserInput), Exceptions::ApiResponseError);
        }
}