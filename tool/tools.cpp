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
                /*
                Function to hide the API key in the URL

                @param url: The URL containing the API key

                @return: The URL with the API key replaced by asterisks
                */
                Tools::URL hideApiKey(const Tools::URL& url)
                {
                        Tools::URL hiddenApiKey = url;
                        size_t pos = hiddenApiKey.find(Constants::API_KEY);
                        if (pos != Tools::URL::npos)
                        {
                                hiddenApiKey.replace(pos, Constants::API_KEY.length(), "********");
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
        }
}