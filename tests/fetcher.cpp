/*
Date: 12/06/2024

Description: This file contains the tests for the Fetcher module.

Notes: x
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "../src/fetcher.cpp"
#include "../src/tools.cpp"

namespace Fetcher
{
        // Test for SPY ETF data fetch
        TEST(FetcherTest, FetchData)
        {
                // URL for fetching SPY ETF data
                URL url = Fetcher::Constants::API_URL + Constants::ETF_URL_ENDPOINT + Constants::SPY + Constants::API_KEY_PARAM + Constants::API_KEY;
                std::string readBuffer;

                // Hide the API key in the log
                std::string hiddenApiKey = Tools::hide_api_key(url);
                spdlog::info("URL: {}", hiddenApiKey);

                // Initialize libcurl and set the necessary options
                CURL* curl = init_curl(url, readBuffer);
                ASSERT_TRUE(curl != nullptr);

                // Perform the HTTP request
                CURLcode res = perform_request(curl);
                ASSERT_EQ(res, CURLE_OK);

                spdlog::info("Received data: {}", readBuffer);
        }
}
