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
                        : url(""), api(""), apiKey(""), tickerSymbol(""), from(""), to(""), timeFrame(""), test(false) { }

                RawUserInput::RawUserInput(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate, const std::string& timeFrame, const std::string& api, const std::string& apiKey)
                        : url(""), api(api), apiKey(apiKey), tickerSymbol(tickerSymbol), from(fromDate), to(toDate), timeFrame(timeFrame), test(false) { }

                RawUserInput::RawUserInput(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate, const std::string& multiplier, const std::string& timeFrame, const std::string& api, const std::string& apiKey)
                        : url(""), api(api), apiKey(apiKey), tickerSymbol(tickerSymbol), from(fromDate), to(toDate), multiplier(multiplier), timeFrame(timeFrame), test(false) { }

                RawUserInput::RawUserInput(const std::string& urlString)
                        : url(urlString), api(""), apiKey(""), tickerSymbol(""), from(""), to(""), timeFrame(""), test(false) { }

                RawUserInput::RawUserInput(const std::string& urlString, const std::string& apiKey)
                        : url(urlString), api(""), apiKey(apiKey), tickerSymbol(""), from(""), to(""), timeFrame(""), test(false) { }

                void RawUserInput::logRawUserInput() const
                {
                        spdlog::info("Raw user input: URL: {}, API: {}, API key: {}, Ticker symbol: {}, From: {}, To: {}, Time frame: {}, Test: {}", Tools::hideApiKey(url), api, !apiKey.empty(), tickerSymbol, from, to, timeFrame, test);
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
                        if (!checkValidUrl(args, argNames))
                        {
                                spdlog::error("Invalid input. URL '{}' is not supported.", args[std::find(argNames.begin(), argNames.end(), "url") - argNames.begin()]);
                                throw std::invalid_argument("Invalid input. Please provide a valid URL.");
                        }

                        // Verify the API
                        if (!checkValidApi(args, argNames))
                        {
                                spdlog::error("Invalid input. API '{}' is not supported.", args[std::find(argNames.begin(), argNames.end(), "api") - argNames.begin()]);
                                throw std::invalid_argument("Invalid input. Please provide a valid API.");
                        }

                        // Verify from and to format
                        if (!checkValidDateFormat(args, argNames))
                        {
                                spdlog::error("Invalid input. Date format is not valid.");
                                throw std::invalid_argument("Invalid input. Please provide a valid date format.");
                        }
                }

                /*
                Process the user input.

                @param rawUserInput: The raw user input.
                @param processedUserInput: The processed user input.
                */
                void proccessUserInput(const RawUserInput& rawUserInput, ProcessedUserInput& processedUserInput)
                {
                        // Check if the raw input contains an URL
                        if (checkForUrl(rawUserInput))
                        {
                                // Then check if the URL contains ap API key
                                if (checkUrlForApiKey(rawUserInput.url))
                                {
                                        // If it does, use the URL as is
                                        processedUserInput.url = rawUserInput.url;
                                        return;
                                }
                                // If it doesn't, check if the user provided an API key on its own
                                else
                                {
                                        if (rawUserInput.apiKey != "")
                                        {
                                                // If they did, create a new URL with the provided URL and API key
                                                processedUserInput.url = createUrl(rawUserInput.url, rawUserInput.apiKey);
                                                return;
                                        }
                                }
                        }

                        // Check if the from, to, and time frame are not empty
                        if (checkFromToTimeFrame(rawUserInput.from, rawUserInput.to, rawUserInput.timeFrame))
                        {
                                // Check if the user provided a ticker, api and api key
                                if (rawUserInput.tickerSymbol != "" && rawUserInput.api != "" && rawUserInput.apiKey != "")
                                {
                                        // Check for the multiplier
                                        if (rawUserInput.multiplier != "")
                                        {
                                                // If the multiplier is provided, create a URL with the ticker, from, to, multiplier, time frame, API, and API key
                                                processedUserInput.url = createUrl(rawUserInput.tickerSymbol, rawUserInput.from, rawUserInput.to, rawUserInput.multiplier, rawUserInput.timeFrame, rawUserInput.api, rawUserInput.apiKey);
                                                return;
                                        }
                                        else
                                        {
                                                processedUserInput.url = createUrl(rawUserInput.tickerSymbol, rawUserInput.from, rawUserInput.to, rawUserInput.timeFrame, rawUserInput.api, rawUserInput.apiKey);
                                                return;
                                        }
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

                        newUrl = url + Constants::QUESTION_MARK + Constants::FMP_API_KEY_PARAM + apiKey;

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
                                // Eg. https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=vKoDVGFjjGHf5uWq3O0ztQ0w6CfMfxIa
                                url = Constants::FMP_API_URL + Constants::FMP_HISTORICAL_DATA_ENDPOINT + timeFrame + Constants::SLASH + tickerSymbol
                                        + Constants::QUESTION_MARK + "from=" + fromDate + Constants::AND + "to=" + toDate + Constants::AND
                                        + Constants::FMP_API_KEY_PARAM + apiKey;
                        }
                        else if (lowerApi == "polygon")
                        {
                                // Eg. https://api.polygon.io/v2/aggs/ticker/SPY/range/4/hour/2023-01-09/2023-01-10?adjusted=true&sort=asc&apiKey=US3m3PmjA1TXqHpLCl2A9HmH6U5LhPz1
                                url = Constants::POLYGON_API_URL + Constants::POLYGON_HISTORICAL_DATA_ENDPOINT + tickerSymbol + "range" + Constants::SLASH + timeFrame
                                + Constants::SLASH + fromDate + Constants::SLASH + toDate + Constants::QUESTION_MARK + "adjusted=true&sort=asc"
                                        + Constants::AND + Constants::POLYGON_API_KEY_PARAM + apiKey;
                        }
                        else
                        {
                                spdlog::error("Invalid input. API '{}' is not supported.", api);
                                throw std::invalid_argument("Invalid input. Please provide a valid API. Valid API arguments are 'fmp' and 'polygon'.");
                        }

                        return url;
                }

                /*
                Create a URL based on the ticker symbol, from date, to date, multiplier, time frame, API, and API key.

                @param tickerSymbol: The ticker symbol to fetch data for.
                @param fromDate: The start date in YYYY-MM-DD format.
                @param toDate: The end date in YYYY-MM-DD format.
                @param multiplier: The multiplier for the time frame.
                @param timeFrame: The time frame for the operation.
                @param api: The API to use.
                @param apiKey: The API key to use.

                @return: The URL to fetch data from.
                */
                Tools::URL createUrl(const std::string& tickerSymbol, const std::string& fromDate,
                        const std::string& toDate, const std::string& multiplier, const std::string& timeFrame,
                        const std::string& api, const std::string& apiKey)
                {
                        Tools::URL url;

                        // Lowercase the API
                        std::string lowerApi = api;
                        std::transform(api.begin(), api.end(), lowerApi.begin(),
                                [](unsigned char c){ return std::tolower(c); });

                        // New timeFrame
                        std::string newTimeFrame;

                        // We update the timeFrame based on the api
                        if (lowerApi == "fmp")
                        {
                                newTimeFrame = multiplier + timeFrame;
                        }
                        else if (lowerApi == "polygon")
                        {
                                newTimeFrame = multiplier + Constants::SLASH + timeFrame;
                        }
                        else
                        {
                                spdlog::error("Invalid input. API '{}' is not supported.", api);
                                throw std::invalid_argument("Invalid input. Please provide a valid API. Valid API arguments are 'fmp' and 'polygon'.");
                        }

                        // We then call the createUrl function with the new timeFrame
                        url = createUrl(tickerSymbol, fromDate, toDate, newTimeFrame, api, apiKey);

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

                /*
                Check if the URL is valid.

                @param args: The arguments to check.
                @param argNames: The names of the arguments to check.

                @return: True if the URL is valid, false otherwise.
                */
                bool checkValidUrl(const std::vector<std::string>& args, const std::vector<std::string>& argNames)
                {
                        // Check if the URL argument is even demanded
                        if (std::find(argNames.begin(), argNames.end(), "url") != argNames.end())
                        {
                                const std::string& url = args[std::find(argNames.begin(), argNames.end(), "url") - argNames.begin()];

                                // Check if the URL is valid
                                if (url.find(Constants::FMP_API_URL) == std::string::npos && url.find(Constants::POLYGON_API_URL) == std::string::npos)
                                {
                                        spdlog::error("Invalid input. URL '{}' is not supported.", url);
                                        throw std::invalid_argument("Invalid input. Please provide a valid URL. Valid URL needs to link to a supported API.");
                                }
                        }

                        return true;
                }

                /*
                Check if the API is valid.

                @param args: The arguments to check.
                @param argNames: The names of the arguments to check.

                @return: True if the API is valid, false otherwise.
                */
                bool checkValidApi(const std::vector<std::string>& args, const std::vector<std::string>& argNames)
                {
                        // Check if the API argument is even demanded
                        if (std::find(argNames.begin(), argNames.end(), "api") != argNames.end())
                        {
                                const std::string& api = args[std::find(argNames.begin(), argNames.end(), "api") - argNames.begin()];

                                // Check if the API is valid
                                if (api != "fmp" && api != "polygon")
                                {
                                        spdlog::error("Invalid input. API '{}' is not supported.", api);
                                        throw std::invalid_argument("Invalid input. Please provide a valid API. Valid API arguments are 'fmp' and 'polygon'.");
                                }
                        }

                        return true;
                }

                /*
                Check if the date formats are valid.

                @param args: The arguments to check.
                @param argNames: The names of the arguments to check.

                @return: True if the date formats are valid, false otherwise.
                */
                bool checkValidDateFormat(const std::vector<std::string>& args, const std::vector<std::string>& argNames)
                {
                        // Check if the from and to arguments are even demanded
                        if (std::find(argNames.begin(), argNames.end(), "from") != argNames.end() &&
                                std::find(argNames.begin(), argNames.end(), "to") != argNames.end())
                        {
                                const std::string& fromDate = args[std::find(argNames.begin(), argNames.end(), "from") - argNames.begin()];
                                const std::string& toDate = args[std::find(argNames.begin(), argNames.end(), "to") - argNames.begin()];

                                if (!validateDate(fromDate) || !validateDate(toDate))
                                {
                                        spdlog::error("Invalid input. Date format is not valid.");
                                        throw std::invalid_argument("Invalid input. Please provide a valid date format.");
                                }
                        }

                        return true;
                }

                /*
                Validate the date.

                @param date: The date to validate.

                @return: True if the date is valid, false otherwise.
                */
                bool validateDate(const std::string& date)
                {
                        // Check length
                        if (date.length() != 10)
                        {
                                spdlog::error("Invalid input. Date format is not valid. Accepted format is YYYY-MM-DD.");
                                throw std::invalid_argument("Invalid input. Please provide a valid date format. Date format needs to be in YYYY-MM-DD format.");
                        }

                        // Check format (positions of '-')
                        if (date[4] != '-' || date[7] != '-')
                        {
                                spdlog::error("Invalid input. Date format is incorrect.");
                                throw std::invalid_argument("Invalid input. Date format needs to be in YYYY-MM-DD format.");
                        }

                        // Extract year, month, day
                        int year = std::stoi(date.substr(0, 4));
                        int month = std::stoi(date.substr(5, 2));
                        int day = std::stoi(date.substr(8, 2));

                        // Validate year, month, day
                        if (year < 1800 || year > 2100)
                        {
                                spdlog::error("Invalid year. {} is not a valid year.", year);
                                throw std::invalid_argument("Invalid year. Please provide a valid year.");
                        }
                        if (month < 1 || month > 12)
                        {
                                spdlog::error("Invalid month. {} is not a valid month.", month);
                                throw std::invalid_argument("Invalid month. Please provide a valid month.");
                        }

                        // Validate day based on month and leap year
                        auto isLeapYear = [](int y) { return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)); };
                        int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                        if (day < 1 || day > daysInMonth[month - 1])
                        {
                                spdlog::error("Invalid day. Day is not valid for the given month and year.");
                                throw std::invalid_argument("Invalid day. Please provide a valid day.");
                        }

                        return true;
                }
        }
}