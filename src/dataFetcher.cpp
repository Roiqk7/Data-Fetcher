/*
Date: 16/06/2024

Description: Defines the public functions for this library.

Notes: x
*/

#include <json/json.h>
#include <string>
#include "../include/tools.h"
#include "../include/dataFetcher/dataFetcher.h"
#include "../src/include/flowControl.h"
#include "../src/include/inputHandler.h"

namespace Fetcher
{
        /*
        Fetches historical data from an API.

        @param tickerSymbol: The ticker symbol to fetch data for.
        @param fromDate: The start date in YYYY-MM-DD format.
        @param toDate: The end date in YYYY-MM-DD format.
        @param timeFrame: The time frame for the operation.
        @param api: The API to use. (fmp or polygon)
        @param apiKey: The API key to use.

        @return: The fetched historical data.
        */
        Json::Value fetchHistoricalData(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate, const std::string& timeFrame, const std::string& api, const std::string& apiKey)
        {
                // Validate user input
                InputHandler::userInputValidator({tickerSymbol, fromDate, toDate, timeFrame, api, apiKey},
                        {"tickerSymbol", "fromDate", "toDate", "timeFrame", "api", "apiKey"});

                // Initialize the raw user input
                InputHandler::RawUserInput rawUserInput(tickerSymbol, fromDate, toDate, timeFrame, api, apiKey);

                // Initialize the processed user input
                InputHandler::ProcessedUserInput processedUserInput;

                return FlowControl::handleUserRequest(rawUserInput, processedUserInput);
        }

        /*
        Fetches historical data from an API.

        @param tickerSymbol: The ticker symbol to fetch data for.
        @param fromDate: The start date in YYYY-MM-DD format.
        @param toDate: The end date in YYYY-MM-DD format.
        @param multiplier: The multiplier for the time frame.
        @param timeFrame: The time frame for the operation.
        @param api: The API to use. (fmp or polygon)
        @param apiKey: The API key to use.

        @return: The fetched historical data.
        */
        Json::Value fetchHistoricalData(const std::string& tickerSymbol, const std::string& fromDate,
                const std::string& toDate, const std::string& multiplier, const std::string& timeFrame,
                const std::string& api, const std::string& apiKey)
        {
                // Validate user input
                InputHandler::userInputValidator({tickerSymbol, fromDate, toDate, multiplier, timeFrame, api, apiKey},
                        {"tickerSymbol", "from", "to", "multiplier", "timeFrame", "api", "apiKey"});

                // Initialize the raw user input
                InputHandler::RawUserInput rawUserInput(tickerSymbol, fromDate, toDate, multiplier, timeFrame, api, apiKey);

                // Initialize the processed user input
                InputHandler::ProcessedUserInput processedUserInput;

                return FlowControl::handleUserRequest(rawUserInput, processedUserInput);
        }

        /*
        Fetches historical data from an API.

        @param urlString: The URL to fetch data from.

        @return: The fetched historical data.
        */
        Json::Value fetchHistoricalData(const std::string& urlString)
        {
                // Validate user input
                InputHandler::userInputValidator({urlString}, {"urlString"});

                // Initialize the raw user input
                InputHandler::RawUserInput rawUserInput(urlString);

                // Initialize the processed user input
                InputHandler::ProcessedUserInput processedUserInput;

                return FlowControl::handleUserRequest(rawUserInput, processedUserInput);
        }

        /*
        Fetches historical data from an API.

        @param urlString: The URL to fetch data from.
        @param apiKey: The API key to use.

        @return: The fetched historical data.
        */
        Json::Value fetchHistoricalData(const std::string& urlString, const std::string& apiKey)
        {
                // Validate user input
                InputHandler::userInputValidator({urlString, apiKey}, {"urlString", "apiKey"});

                // Initialize the raw user input
                InputHandler::RawUserInput rawUserInput(urlString, apiKey);

                // Initialize the processed user input
                InputHandler::ProcessedUserInput processedUserInput;

                return FlowControl::handleUserRequest(rawUserInput, processedUserInput);
        }

        /*
        Runs the unit tests for this module.
        */
        /*
        Note: To run tests build the project and run the executable FetcherTests.
        void runUnitTests()
        {
                InputHandler::ProcessedUserInput processedUserInput(true);

                FlowControl::controlFlow(processedUserInput);
        }
        */
}