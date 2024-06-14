/*
Date: 12/06/2024

Description: This file contains the tests for the tools.cpp module.

Notes: x
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "../include/constants.h"
#include "../include/tools.h"

namespace Fetcher
{
        namespace Tools
        {
                // Test for reading contents of a file
                TEST(ToolsTest, toolsTest1)
                {
                        // Construct the file path dynamically
                        std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                        std::string filePath = "../tests/" + testName + ".txt";

                        // Expected contents of the file
                        std::string expectedContents = "Hello world!";

                        // Read the contents of the file
                        std::string readContents = Tools::readFileContents(filePath);

                        // Assert that the read contents are equal to the expected contents
                        ASSERT_EQ(readContents, expectedContents);

                        if (readContents != expectedContents)
                                spdlog::error("Received contents: {}", readContents);
                }

                // Test for hiding the API key in the URL
                TEST(ToolsTest, toolsTest2)
                {
                        // Construct the file path dynamically
                        std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                        std::string filePath = "../tests/" + testName + ".txt";

                        // URL for fetching SPY ETF data
                        Constants::URL url = Fetcher::Constants::API_URL + Constants::HISTORICAL_DATA_ENDPOINT + Constants::FOUR_HOUR
                                + Constants::SPY + Constants::QUESTION_MARK + "from=2023-08-10&to=2023-09-10" + Constants::AND
                                + Constants::API_KEY_PARAM + Constants::API_KEY;

                        // Hide the API key in the log
                        Constants::URL hiddenApiKey = Tools::hideApiKey(url);
                        spdlog::info("URL: {}", hiddenApiKey);

                        // Expected URL with hidden API key
                        Constants::URL expectedUrl = readFileContents(filePath);

                        // Assert that the API key is hidden
                        ASSERT_EQ(hiddenApiKey, expectedUrl);

                        if (hiddenApiKey != expectedUrl)
                                spdlog::error("Received URL: {}", hiddenApiKey);
                }

                // Test for writing contents to a file
                TEST(ToolsTest, toolsTest3)
                {
                        // Construct the file path dynamically
                        std::string testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
                        std::string filePath = "../tests/" + testName + ".txt";

                        // Contents to write to the file
                        std::string contents = "Hello world!";

                        // Write the contents to the file
                        Tools::writeFileContents(filePath, contents);

                        // Read the contents of the file
                        std::string readContents = Tools::readFileContents(filePath);

                        // Assert that the read contents are equal to the written contents
                        ASSERT_EQ(readContents, contents);

                        if (readContents != contents)
                                spdlog::error("Received contents: {}", readContents);
                }
        }
}