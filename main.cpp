// Debug = delete this file

#include <json/json.h>
#include "include/dataFetcher.h"

int main()
{
        // Fetch historical data
        Fetcher::fetchHistoricalData("AAPL", "2021-01-01", "2021-01-05", "4hour", "fmp", "vKoDVGFjjGHf5uWq3O0ztQ0w6CfMfxIa");
        return 0;
}