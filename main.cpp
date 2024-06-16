/*
Date: 16/06/2024

Description: Used as an entry point when developing and debugging the programme.

Notes: When deleting this file dont forget to delete the main from CMakeLists.txt
*/

#include <json/json.h>
#include <dataFetcher/dataFetcher.h>

int main()
{
        // Fetch historical data
        Fetcher::fetchHistoricalData("AAPL", "2021-01-01", "2021-01-05", "4hour", "fmp", "vKoDVGFjjGHf5uWq3O0ztQ0w6CfMfxIa");
        return 0;
}