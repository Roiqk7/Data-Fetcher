/*
Date: 12/06/2024

Description: This file contains the tests for the fetcher.cpp module.

Notes: x
*/

#include <curl/curl.h>
#include <fstream>
#include <gtest/gtest.h>
#include <json/json.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include "../include/constants.h"
#include "../include/fetcher.h"
#include "../include/tools.h"

namespace Fetcher
{
        // Test for SPY ETF data fetch
        TEST(FetcherTest, fetcherTest1)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                std::string filePath = "../test/" + testName + ".txt";

                // Log
                spdlog::info("{} test started. Fetching SPY ETF data...", testName);

                // URL for fetching SPY ETF data
                Tools::URL url = "https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=" + Constants::FMP_API_KEY;

                // Fetch the data
                auto actualData = Fetcher::fetchRequestedData(url);

                // Read the expected contents from fetcherTest1.json
                Json::Value expectedData = Tools::readJsonFileContents("fetcherTest1.json");

                // Assert that the fetched data is equal to the expected data
                ASSERT_EQ(*actualData, expectedData);

                if (*actualData != expectedData)
                        spdlog::error("Received data: {}", actualData->toStyledString());
        }
}