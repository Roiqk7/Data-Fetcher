/*
Date: 12/06/2024

Description: This file contains the constants used in the Fetcher module.

Notes: Changes may be made to the data types. Just simple renaming to URL and Ticker perhaps...
*/

#include <string>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Fetcher
{
        namespace Constants
        {
        // Program flags
                using Flag = int; // Used for easier readability
                const Flag SUCCESS = 0; // Used to indicate a successful operation
                const Flag FAILURE = 1; // Used to indicate a failed operation
                const Flag SUCCESS_END = 2; // Program must be terminated on purpose
                const Flag FAILURE_END = 3; // Fatal error, program must be terminated
        // File paths
                using FilePath = std::string; // Used for easier readability
                const FilePath DEFAULT_DATA_FILE_PATH = "../data/data.json"; // Default file path for the fetched data
        // URL
                // Used for easier readability
                using URL = std::string; // URL data type used in communication with the API

                // API URL Constants - sorted based on the order of use
                const URL API_URL = "https://financialmodelingprep.com/api/v3/"; // Add the endpoint and the ticker symbol at the end

                // API Endpoint Constants
                const URL STOCK_URL_ENDPOINT = "stock/"; // Add the ticker symbol at the end
                const URL ETF_URL_ENDPOINT = "etf/"; // Add the ticker symbol at the end
                const URL HISTORICAL_DATA_ENDPOINT = "historical-chart/"; // Add time frame and time period at the end

                // Ticker Symbols
                const URL SPY = "SPY"; // SPDR S&P 500 ETF Trust

                // Connectors
                const URL SLASH = "/"; // Used to separate the URL components
                const URL QUESTION_MARK = "?"; // Used to begin the query string
                const URL AND = "&"; // Used to separate the URL components

                // Add the API key at the end of the URL
                const URL API_KEY_PARAM = "apikey=";
                const URL API_KEY = "x"; // NOTE: DO NOT SHARE THIS KEY
        }
}


#endif // CONSTANTS_H
