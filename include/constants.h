/* 
Date: 12/06/2024

Description: This file contains the constants used in the Fetcher module.

Notes: x
*/

#include <string>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Fetcher
{
        namespace Constants
        {
                // API URL Constants - sorted based on the order of use
                const std::string API_URL = "https://financialmodelingprep.com/api/v3/"; // Add the endpoint and the ticker symbol at the end

                const std::string STOCK_URL_ENDPOINT = "stock/"; // Add the ticker symbol at the end
                const std::string ETF_URL_ENDPOINT = "etf/"; // Add the ticker symbol at the end
                const std::string SPY = "SPY"; // S&P 500 ETF

                // Add the API key at the end of the URL
                const std::string API_KEY_PARAM = "?apikey=";
                const std::string API_KEY = "x"; // NOTE: DO NOT SHARE THIS KEY
        }
}


#endif // CONSTANTS_H
