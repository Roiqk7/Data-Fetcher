/*
Date: 16/06/2024

Description: Used to handle user input.

Notes: x
*/

#include <algorithm>
#include <cctype>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string>
#include <vector>
#include "../include/tools.h"
#include "../src/include/constants.h"
#include "../src/include/inputHandler.h"

namespace Fetcher
{
        namespace InputHandler
        {
        // Structs
                RawUserInput::RawUserInput()
                        : url(""), api(""), apiKey(""), tickerSymbol(""), from(""), to(""), timeframe(""), test(false) { }

                RawUserInput::RawUserInput(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate, const std::string& timeFrame, const std::string& api, const std::string& apiKey)
                        : url(""), api(api), apiKey(apiKey), tickerSymbol(tickerSymbol), from(fromDate), to(toDate), timeframe(timeFrame), test(false) { }

                RawUserInput::RawUserInput(const std::string& urlString)
                        : url(urlString), api(""), apiKey(""), tickerSymbol(""), from(""), to(""), timeframe(""), test(false) { }

                RawUserInput::RawUserInput(const std::string& urlString, const std::string& apiKey)
                        : url(urlString), api(""), apiKey(apiKey), tickerSymbol(""), from(""), to(""), timeframe(""), test(false) { }

                void RawUserInput::logRawUserInput() const
                {
                        spdlog::info("Raw user input: URL: {}, API: {}, API key: {}, Ticker symbol: {}, From: {}, To: {}, Time frame: {}, Test: {}", Tools::hideApiKey(url), api, !apiKey.empty(), tickerSymbol, from, to, timeframe, test);
                }

                ProcessedUserInput::ProcessedUserInput()
                        : url(""), test(false) { }

                ProcessedUserInput::ProcessedUserInput(const Tools::URL& url)
                        : url(url), test(false) { }

                ProcessedUserInput::ProcessedUserInput(bool test)
                        : url(""), test(test) { }

                void ProcessedUserInput::logProcessedUserInput() const
                {
                        spdlog::info("Processed user input: URL: {}, Test: {}", Tools::hideApiKey(url), test);
                }
        // Functions
                /*
                Validate the user input.

                @param args: The arguments to validate.
                @param argNames: The names of the arguments to validate.

                TODO Separate into smaller functions
                */
                void userInputValidator(const std::vector<std::string>& args, const std::vector<std::string>& argNames)
                {
                        // Check if any of the arguments are missing
                        if (checkMissingArguments(args, argNames))
                        {
                                spdlog::error("Mismatch between number of arguments and number of argument names.");
                                throw std::invalid_argument("Invalid input. Argument count does not match expected count.");
                        }

                        // Check if the arguments are empty
                        if (checkEmptyArguments(args))
                        {
                                spdlog::error("Invalid input. One or more arguments are empty.");
                                throw std::invalid_argument("Invalid input. Please provide all the required arguments.");
                        }

                        // Verify the URL
                        if (std::find(argNames.begin(), argNames.end(), "url") != argNames.end())
                        {
                                const std::string& url = args[std::find(argNames.begin(), argNames.end(), "url") - argNames.begin()];

                                // Check if the URL is valid
                                if (url.find(Constants::FMP_API_URL) == std::string::npos && url.find(Constants::POLYGON_API_URL) == std::string::npos)
                                {
                                        spdlog::error("Invalid input. URL '{}' is not supported.", url);
                                        throw std::invalid_argument("Invalid input. Please provide a valid URL.");
                                }
                        }

                        // Verify the API
                        // TODO

                        // Verify from and to format
                        // TODO
                }

                /*
                Process the user input.

                @param rawUserInput: The raw user input.
                @param processedUserInput: The processed user input.
                */
                void proccessUserInput(const RawUserInput& rawUserInput, ProcessedUserInput& processedUserInput)
                {
                        // Check if the raw input has a URL
                        if (checkForUrl(rawUserInput))
                        {
                                // Then check for an API key
                                if (checkUrlForApiKey(rawUserInput.url))
                                {
                                        processedUserInput.url = rawUserInput.url;
                                        return;
                                }
                                else
                                {
                                        // Check if the user provided a api key
                                        if (rawUserInput.apiKey != "")
                                        {
                                                processedUserInput.url = createUrl(rawUserInput.url, rawUserInput.apiKey);
                                                return;
                                        }
                                }
                        }

                        // Check if the from, to, and time frame are not empty
                        if (checkFromToTimeFrame(rawUserInput.from, rawUserInput.to, rawUserInput.timeframe))
                        {
                                // Check if the user provided a ticker, api and api key
                                if (rawUserInput.tickerSymbol != "" && rawUserInput.api != "" && rawUserInput.apiKey != "")
                                {
                                        processedUserInput.url = createUrl(rawUserInput.tickerSymbol, rawUserInput.from, rawUserInput.to, rawUserInput.timeframe, rawUserInput.api, rawUserInput.apiKey);
                                        return;
                                }
                        }

                        // If none of the above conditions are met, throw an error
                        spdlog::error("Invalid input. URL could not be created.");
                        throw std::invalid_argument("Invalid input. Please provide enough information to fetch data.");
                }

                /*
                Create a URL based on the URL.

                @param url: The URL to fetch data from.

                @return: The URL to fetch data from.
                */
                Tools::URL createUrl(const std::string& url)
                {
                        Tools::URL newUrl;

                        newUrl = url;

                        return newUrl;
                }

                /*
                Create a URL based on the URL and API key.

                @param url: The URL to fetch data from.
                @param apiKey: The API key to use.

                @return: The URL to fetch data from.
                */
                Tools::URL createUrl(const std::string& url, const std::string& apiKey)
                {
                        Tools::URL newUrl;

                        newUrl = url + Constants::QUESTION_MARK + Constants::API_KEY_PARAM + apiKey;

                        return newUrl;
                }

                /*
                Create a URL based on the ticker symbol, from date, to date, time frame, API, and API key.

                @param tickerSymbol: The ticker symbol to fetch data for.
                @param fromDate: The start date in YYYY-MM-DD format.
                @param toDate: The end date in YYYY-MM-DD format.
                @param timeFrame: The time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).
                @param api: The API to use.
                @param apiKey: The API key to use.

                @return: The URL to fetch data from.
                */
                Tools::URL createUrl(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate, const std::string& timeFrame, const std::string& api, const std::string& apiKey)
                {
                        Tools::URL url;

                        // Lowercase the API
                        std::string lowerApi = api;
                        std::transform(api.begin(), api.end(), lowerApi.begin(),
                                [](unsigned char c){ return std::tolower(c); });

                        // Determine the URL based on the API
                        if (lowerApi == "fmp")
                        {
                                url = Constants::FMP_API_URL + Constants::FMP_HISTORICAL_DATA_ENDPOINT + timeFrame + Constants::SLASH + tickerSymbol
                                        + Constants::QUESTION_MARK + "from=" + fromDate + Constants::AND + "to=" + toDate + Constants::AND
                                        + Constants::API_KEY_PARAM + apiKey;
                        }
                        else if (lowerApi == "polygon")
                        {
                                url = "TODO"; // TODO: Implement Polygon API
                        }

                        return url;
                }

                /*
                Check if the raw input has a URL.
                */
                bool checkForUrl(const RawUserInput& rawInput)
                {
                        return rawInput.url != "";
                }

                /*
                Check if the URL has an API key.

                @param url: The URL to check.

                @return: True if the URL has an API key, false otherwise.
                */
                bool checkUrlForApiKey(const Tools::URL& url)
                {
                        return url.find("apikey") != std::string::npos;
                }

                /*
                Check if the from, to, and time frame are not empty.

                @param fromDate: The start date in YYYY-MM-DD format.
                @param toDate: The end date in YYYY-MM-DD format.
                @param timeFrame: The time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).

                @return: True if the from, to, and time frame are not empty, false otherwise.
                */
                bool checkFromToTimeFrame(const std::string& fromDate, const std::string& toDate, const std::string& timeFrame)
                {
                        return fromDate != "" && toDate != "" && timeFrame != "";
                }

                /*
                Check if any of the arguments are missing.

                @param args: The arguments to check.
                @param argNames: The names of the arguments to check.

                @return: True if any of the arguments are missing, false otherwise.
                */
                bool checkMissingArguments(const std::vector<std::string>& args, const std::vector<std::string>& argNames)
                {
                        return args.size() != argNames.size();
                }

                /*
                Check if any of the arguments are empty.

                @param args: The arguments to check.

                @return: True if any of the arguments are empty, false otherwise.
                */
                bool checkEmptyArguments(const std::vector<std::string>& args)
                {
                        return std::any_of(args.begin(), args.end(), [](const std::string& arg){ return arg == ""; });
                }
        }
}