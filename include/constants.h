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
