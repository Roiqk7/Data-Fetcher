/*
Date: 13/06/2024

Description: This file contains the implementation of the helper functions used in the Fetcher module.

Notes: x
*/

#include <algorithm>
#include <cctype>
#include <fstream>
#include <json/json.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include "../include/tools.h"
#include "../src/include/constants.h"
#include "../src/include/inputHandler.h"

namespace Fetcher
{
        namespace Tools
        {
                /*
                Function to hide the API key in the URL

                @param url: The URL containing the API key

                @return: The URL with the API key replaced by asterisks
                */
                URL hideApiKey(const Tools::URL& url)
                {
                        Tools::URL hiddenApiKey = url;
                        std::string lowerCaseUrl = hiddenApiKey;
                        // Convert URL to lowercase for case-insensitive search
                        std::transform(lowerCaseUrl.begin(), lowerCaseUrl.end(), lowerCaseUrl.begin(),
                                [](unsigned char c)
                                {
                                        return std::tolower(c);
                                }
                        );
                        std::string apiKeyIndicator = Constants::FMP_API_KEY_PARAM;
                        size_t pos = lowerCaseUrl.find(apiKeyIndicator);
                        if (pos != std::string::npos)
                        {
                                size_t startOfApiKey = pos + apiKeyIndicator.length();
                                size_t endOfApiKey = lowerCaseUrl.find("&", startOfApiKey);
                                if (endOfApiKey == std::string::npos)
                                {
                                        // If the API key is the last parameter, erase until the end of the string
                                        hiddenApiKey.erase(startOfApiKey);
                                }
                                else
                                {
                                        // Erase the API key, keeping subsequent parameters intact
                                        hiddenApiKey.erase(startOfApiKey, endOfApiKey - startOfApiKey);
                                }
                                // Insert the mask at the API key's position
                                hiddenApiKey.insert(startOfApiKey, "********");
                        }

                        return hiddenApiKey;
                }

                /*
                Read contents of a file

                @param filePath: The path to the file

                @return: The contents of the file
                */
                std::string readFileContents(const FilePath& filePath)
                {
                        std::ifstream file(filePath);
                        if (!file.is_open())
                        {
                                spdlog::error("Failed to open file at: {}", filePath);
                                return "";
                        }

                        std::stringstream buffer;
                        buffer << file.rdbuf();
                        return buffer.str();
                }

                /*
                Read contents of a JSON file

                @param filePath: The path to the file

                @return: The contents of the file
                */
                Json::Value readJsonFileContents(const FilePath& filePath)
                {
                        Json::Value root;
                        Json::Reader reader;
                        std::string contents = readFileContents(filePath);
                        if (!reader.parse(contents, root))
                        {
                                spdlog::error("Failed to parse JSON file at: {}", filePath);
                        }

                        return root;
                }

                /*
                Write contents to a file

                @param filePath: The path to the file
                @param contents: The contents to be written
                */
                void writeFileContents(const FilePath& filePath, const std::string& contents)
                {
                        std::ofstream file(filePath);
                        if (!file.is_open())
                        {
                                spdlog::error("Failed to open file at: {}", filePath);
                                return;
                        }

                        file << contents;
                }

                /*
                Checks if the API key is hardcoded in the code
                */
                bool checkHardcodedAPIKey()
                {
                        // Assuming that the API key is valid if it is longer than 5 characters
                        return Constants::FMP_API_KEY.size() > 5;
                }
        }
}