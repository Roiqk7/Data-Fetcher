/*
Date: 16/06/2024

Description: This is the public entry point for the Fetcher module. It contains the declarations of the functions used to fetch data from an API.

Notes: x
*/

#ifndef FETCHER_H
#define FETCHER_H

#include <json/json.h>
#include <string>

// Project wide namespace
namespace Fetcher
{
        Json::Value fetchHistoricalData(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate,
                const std::string& timeFrame, const std::string& api, const std::string& apiKey);
        Json::Value fetchHistoricalData(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate,
                const std::string& multiplier, const std::string& timeFrame, const std::string& api,
                const std::string& apiKey);
        Json::Value fetchHistoricalData(const std::string& urlString);
        Json::Value fetchHistoricalData(const std::string& urlString, const std::string& apiKey);
        // void runUnitTests();
}

#endif // FETCHER_H