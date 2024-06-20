/*
Date: 12/06/2024

Description: This file contains the tests for the fetcher.cpp module.

Notes: x
*/

#include <curl/curl.h>
#include <fstream>
#include <gtest/gtest.h>
#include <json/json.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include "../src/include/constants.h"
#include "../src/include/fetcher.h"
#include "tools.h"

namespace Fetcher
{
        // Test for SPY ETF data fetch
        TEST(FetcherTest, fetcherTest1)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                std::string filePath = "../test/data/" + testName + ".json";

                // Log
                spdlog::info("{} test started. Fetching SPY ETF data...", testName);

                // URL for fetching SPY ETF data
                Tools::URL url = "https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=" + Constants::FMP_API_KEY;

                // Fetch the data
                auto actualData = Fetcher::fetchRequestedData(url);

                // Read the expected contents from fetcherTest1.json
                Json::Value expectedData = Tools::readJsonFileContents(filePath);

                // Assert that the fetched data is equal to the expected data
                ASSERT_EQ(*actualData, expectedData);

                if (*actualData != expectedData)
                {
                        spdlog::error("Received data: {}", actualData->toStyledString());
                }
        }

        // Test for SPY ETF data read and write
        TEST(FetcherTest, fetcherTest2)
        {
                // Construct the file path dynamically
                std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                std::string filePath = "../test/data/" + testName + ".txt";

                // Log
                spdlog::info("{} test started. Reading and writing SPY ETF data...", testName);

                // Fetch the data
                Json::Value expectedData = Tools::readJsonFileContents("../test/data/fetcherTest1.json"); // Note: Assuming previous test passed and wrote some data to fetcherTest1.json

                // Write the expected data to a file
                Fetcher::writeRequestedData(std::make_unique<Json::Value>(expectedData), filePath);

                // Read the actual contents from fetcherTest2.json
                Json::Value actualData = Tools::readJsonFileContents(filePath);

                // Assert that the fetched data is equal to the expected data
                ASSERT_EQ(actualData, expectedData);

                if (actualData != expectedData)
                {
                        spdlog::error("Received data: {}", actualData.toStyledString());
                }
        }
}