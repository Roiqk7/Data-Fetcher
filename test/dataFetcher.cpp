/*
Date: 16/06/2024

Description: This file contains the tests for the dataFetcher.cpp module.

Notes: x
*/

#include <curl/curl.h>
#include <fstream>
#include <gtest/gtest.h>
#include <json/json.h>
#include <spdlog/spdlog.h>
#include <string>
#include "../include/dataFetcher.h"
#include "../include/tools.h"
#include "../src/include/constants.h"

namespace Fetcher
{
        // Test for fetching historical data using the URL
        TEST(DataFetcherTest, dataFetcherTest1)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                std::string filePath = "../test/docs/" + testName + ".json";

                // Log
                spdlog::info("{} test started. Fetching historical data using the URL...", testName);

                // URL for fetching SPY ETF data
                std::string urlString = "https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=" + Constants::FMP_API_KEY;

                // Fetch the data
                Json::Value actualData = Fetcher::fetchHistoricalData(urlString);

                // Read the expected contents from dataFetcherTest1.json
                Json::Value expectedData = Tools::readJsonFileContents(filePath);

                // Assert that the fetched data is equal to the expected data
                ASSERT_EQ(actualData, expectedData);

                if (actualData != expectedData)
                {
                        spdlog::error("Received data: {}", actualData.toStyledString());
                }
        }
}