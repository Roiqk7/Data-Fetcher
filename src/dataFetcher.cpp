/*
Date: 16/06/2024

Description: Defines the public functions for this library.

Notes: x
*/

#include <json/json.h>
#include <string>
#include "../include/tools.h"
#include "../include/dataFetcher.h"
#include "../src/include/inputHandler.h"

namespace Fetcher
{
        /*
        Fetches historical data from an API.

        @param tickerSymbol: The ticker symbol to fetch data for.
        @param fromDate: The start date in YYYY-MM-DD format.
        @param toDate: The end date in YYYY-MM-DD format.
        @param timeFrame: The time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).
        @param api: The API to use. (fmp or polygon)
        @param apiKey: The API key to use.

        @return: The fetched historical data.
        */
        Json::Value fetchHistoricalData(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate, const std::string& timeFrame, const std::string& api, const std::string& apiKey)
        {
                // Initialize the raw user input
                InputHandler::RawUserInput rawUserInput(tickerSymbol, fromDate, toDate, timeFrame, api, apiKey);

                // Initialize the processed user input
                InputHandler::ProcessedUserInput processedUserInput;

                // Process the user input
                InputHandler::proccessUserInput(rawUserInput, processedUserInput);

                // Run the program
                FlowControl::controlFlow(processedUserInput);

                // Read the fetched data
                const Json::Value fetchedData = Tools::readJsonFileContents(Constants::FETCHED_DATA_FILE_PATH);

                return fetchedData;
        }

        /*
        Fetches historical data from an API.

        @param urlString: The URL to fetch data from.

        @return: The fetched historical data.
        */
        Json::Value fetchHistoricalData(const std::string& urlString)
        {
                // Initialize the raw user input
                InputHandler::RawUserInput rawUserInput(urlString);

                // Initialize the processed user input
                InputHandler::ProcessedUserInput processedUserInput;

                // Process the user input
                InputHandler::proccessUserInput(rawUserInput, processedUserInput);

                // Run the program
                FlowControl::controlFlow(processedUserInput);

                // Read the fetched data
                const Json::Value fetchedData = Tools::readJsonFileContents(Constants::FETCHED_DATA_FILE_PATH);

                return fetchedData;
        }

        /*
        Fetches historical data from an API.

        @param urlString: The URL to fetch data from.
        @param apiKey: The API key to use.

        @return: The fetched historical data.
        */
        Json::Value fetchHistoricalData(const std::string& urlString, const std::string& apiKey)
        {
                // Initialize the raw user input
                InputHandler::RawUserInput rawUserInput(urlString, apiKey);

                // Initialize the processed user input
                InputHandler::ProcessedUserInput processedUserInput;

                // Process the user input
                InputHandler::proccessUserInput(rawUserInput, processedUserInput);

                // Run the program
                FlowControl::controlFlow(processedUserInput);

                // Read the fetched data
                const Json::Value fetchedData = Tools::readJsonFileContents(Constants::FETCHED_DATA_FILE_PATH);

                return fetchedData;
        }
}