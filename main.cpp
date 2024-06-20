/*
Date: 16/06/2024

Description: Used as an entry point when developing and debugging the programme.

Notes:
*/

#include <json/json.h>
#include <dataFetcher/dataFetcher.h>

int main()
{
        // Fetch historical data
        Fetcher::fetchHistoricalData("SPY", "2023-08-10", "2023-08-11", "4", "hour", "polygon", "API_KEY");
        return 0;
}