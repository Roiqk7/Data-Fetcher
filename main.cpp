/*
Date: 16/06/2024

Description: Used as an entry point when developing and debugging the programme.

Notes: When deleting this file dont forget to delete the main from CMakeLists.txt
*/

#include <json/json.h>
#include "include/dataFetcher.h"

int main()
{
        // Fetch historical data
        Fetcher::fetchHistoricalData("https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=vKoDVGFjjGHf5uWq3O0ztQ0w6CfMfxIa");
        return 0;
}