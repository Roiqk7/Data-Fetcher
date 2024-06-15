/*
Date: 12/06/2024

Description: This file contains the constants used in the Fetcher module.

Notes: Global by nature. The difference between constants and globals is that globals are assigned by the user, while constants are predefined.
*/

#include <string>
#include "../include/tools.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Fetcher
{
        namespace Constants
        {
        // Program flags
                const Tools::Flag SUCCESS = 0; // Used to indicate a successful operation
                const Tools::Flag FAILURE = 1; // Used to indicate a failed operation
                const Tools::Flag SUCCESS_END = 2; // Program must be terminated on purpose
                const Tools::Flag FAILURE_END = 3; // Fatal error, program must be terminated
        // File paths
                const Tools::FilePath DEFAULT_DATA_FILE_PATH = "../data/data.json"; // Default file path for the fetched data
        // URL
                // Ticker Symbols
                const Tools::URL SPY = "SPY"; // SPDR S&P 500 ETF Trust

                // Connectors
                const Tools::URL SLASH = "/"; // Used to separate the URL components
                const Tools::URL QUESTION_MARK = "?"; // Used to begin the query string
                const Tools::URL AND = "&"; // Used to separate the URL components

                // URL Parameters
                const Tools::URL API_KEY_PARAM = "apikey=";
        /// FMP API URL Constants - sorted based on the order of use
                // API URL Constants - sorted based on the order of use
                const Tools::URL FMP_API_URL = "https://financialmodelingprep.com/api/v3/"; // Add the endpoint and the ticker symbol at the end

                // API Endpoint Constants
                const Tools::URL FMP_HISTORICAL_DATA_ENDPOINT = "historical-chart/"; // Add time frame and time period at the end

                // Add the API key at the end of the URL
                const Tools::URL FMP_API_KEY = "x"; // NOTE: DO NOT SHARE THIS KEY
        }
}


#endif // CONSTANTS_H
