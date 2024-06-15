/*
Date: 13/06/2024

Description: This file contains the implementation of the helper functions used in the Fetcher module.

Notes: x
*/

#include <fstream>
#include <json/json.h>
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
                URL hideApiKey(const Tools::URL& url)
                {
                        Tools::URL hiddenApiKey = url;
                        size_t pos = hiddenApiKey.find(Constants::FMP_API_KEY);
                        if (pos != Tools::URL::npos)
                        {
                                hiddenApiKey.replace(pos, Constants::FMP_API_KEY.length(), "********");
                        }

                        return hiddenApiKey;
                }

                /*
                Create a URL for fetching data from the API

                @param fromDate: The start date in YYYY-MM-DD format.
                @param toDate: The end date in YYYY-MM-DD format.
                @param timeframe: The time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).

                @return: The URL for fetching data from the API
                */
                URL createUrl(const std::string& fromDate, const std::string& toDate, const std::string& timeFrame)
                {
                        return Constants::FMP_API_URL + Constants::FMP_HISTORICAL_DATA_ENDPOINT + timeFrame + Constants::SLASH
                                + Constants::SPY + Constants::QUESTION_MARK + "from=" + fromDate + Constants::AND
                                + "to=" + toDate + Constants::AND + Constants::API_KEY_PARAM + Constants::FMP_API_KEY;
                }

                /*
                Gets the URL from the command line arguments

                @param vm: The command line arguments

                @return: The URL for fetching data from the API
                */
                URL getURL(const std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        URL url;

                        if (checkFromToTimeFrameArguments(vm))
                        {
                                std::string fromDate = vm->count("from") ? (*vm)["from"].as<std::string>() : (*vm)["f"].as<std::string>();
                                std::string toDate = vm->count("to") ? (*vm)["to"].as<std::string>() : (*vm)["t"].as<std::string>();
                                std::string timeFrame = vm->count("timeframe") ? (*vm)["timeframe"].as<std::string>() : (*vm)["tf"].as<std::string>();
                                url = createUrl(fromDate, toDate, timeFrame);
                        }
                        else if (checkURLArgument(vm))
                        {
                                // Custom URL provided - may cause unintended behaviour
                                spdlog::warn("Custom URL provided. Be warned that unintended behaviour may occur.");
                                url = vm->count("url") ? (*vm)["url"].as<std::string>() : (*vm)["u"].as<std::string>();
                        }
                        else
                        {
                                // Return an empty string if the URL is not provided
                                return "";
                        }
                        return url;
                }

                FilePath getOutputFilePath(const std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        return vm->count("output") ? (*vm)["output"].as<std::string>() : Constants::DEFAULT_DATA_FILE_PATH;
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
                Check if the required arguments for running the programme are provided.

                @param vm: The variables map.

                @return: True if the required arguments are provided, false otherwise.
                */
                bool checkProgramArguments(const std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        // Note: The program requires the --from, --to, and --timeframe arguments to be provided all at the same time
                        return checkFromToTimeFrameArguments(vm) || checkURLArgument(vm);
                }

                /*
                Check if the URL argument is provided.

                @param vm: The variables map.

                @return: True if the URL argument is provided, false otherwise.
                */
                bool checkURLArgument(const std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        return (vm->count("url") || vm->count("u"));
                }

                /*
                Check if the required arguments for the --from, --to and --timeframe arguments are provided.

                @param vm: The variables map.

                @return: True if the required arguments are provided, false otherwise.
                */
                bool checkFromToTimeFrameArguments(const std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        // Note: The program requires the --from, --to, and --timeframe arguments to be provided all at the same time
                        return ((vm->count("from") || vm->count("f")) && (vm->count("to") || vm->count("t")) && (vm->count("timeframe") || vm->count("tf")));
                }
        }
}