/*
Date: 12/06/2024

Description: This file contains the tests for the fetcher.cpp module.

Notes: x
*/

#include <curl/curl.h>
#include <fstream>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include "../include/constants.h"
#include "../src/fetcher.cpp"
#include "../src/tools.cpp"

namespace Fetcher
{
        // Test for SPY ETF data fetch
        TEST(FetcherTest, fetcherTest1)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                std::string filePath = "../tests/" + testName + ".txt";

                // URL for fetching SPY ETF data
                Constants::URL url = Fetcher::Constants::API_URL + Constants::HISTORICAL_DATA_ENDPOINT + Constants::FOUR_HOUR
                        + Constants::SPY + Constants::QUESTION_MARK + "from=2023-08-10&to=2023-09-10" + Constants::AND
                        + Constants::API_KEY_PARAM + Constants::API_KEY;
                std::string readBuffer; // Buffer to store the fetched data

                // Hide the API key in the log
                Constants::URL hiddenApiKey = Tools::hideApiKey(url);
                spdlog::info("URL: {}", hiddenApiKey);

                // Initialize libcurl and set the necessary options
                CURL* curl = init_curl(url, readBuffer);
                ASSERT_TRUE(curl != nullptr);

                // Perform the HTTP request
                CURLcode res = perform_request(curl);
                ASSERT_EQ(res, CURLE_OK);

                // Read the expected contents from fetcherTest1.txt
                std::string expectedContents = Tools::readFileContents(filePath);

                // Assert that readBuffer is equal to the contents of fetcherTest1.txt
                ASSERT_EQ(readBuffer, expectedContents);

                if (readBuffer != expectedContents)
                        spdlog::error("Received data: {}", readBuffer);
        }
}