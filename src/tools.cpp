/* 
Date: 13/06/2024

Description: This file contains the implementation of the helper functions used in the Fetcher module.

Notes: x
*/

#include <fstream>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include "../include/constants.h"
#include "../include/tools.h"

namespace Fetcher
{
        namespace Tools
        {
                // Function to hide the API key in the URL
                Constants::URL hideApiKey(const Constants::URL& url)
                {
                        Constants::URL hiddenApiKey = url;
                        size_t pos = hiddenApiKey.find(Constants::API_KEY);
                        if (pos != Constants::URL::npos)
                        {
                                hiddenApiKey.replace(pos, Constants::API_KEY.length(), "********");
                        }

                        return hiddenApiKey;
                }

                // Read contents of a file
                std::string readFileContents(const std::string& filePath)
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

                // Write contents to a file
                void writeFileContents(const std::string& filePath, const std::string& contents)
                {
                        std::ofstream file(filePath);
                        if (!file.is_open())
                        {
                                spdlog::error("Failed to open file at: {}", filePath);
                                return;
                        }

                        file << contents;
                }
        }
}