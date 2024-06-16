# Welcome to [Data Fetcher](https://github.com/Roiqk7/Data-Fetcher)!

In this short document I will explain how to use this library to fetch the desired data from supported APIs. First of all,
I assume you have already read the [README](https://github.com/Roiqk7/Data-Fetcher/blob/main/README.md) file and have
installed the library. provided with this library. If you haven't, please do so before continuing.

## Documentation

After including the library in your project, you can start using the provided functions. I will now go over all the various
functions and provide you with examples on how to use them.

## Functions defined in header <dataFetcher/dataFetcher.h>

### fetchHistoricalData()

Return a `Json::Value` object that contains the fetched data.

#### Declarations

```cpp
Json::Value fetchHistoricalData(const std::string& urlString);
Json::Value fetchHistoricalData(const std::string& urlString, const std::string& apiKey);
Json::Value fetchHistoricalData(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate, const std::string& timeFrame, const std::string& api, const std::string& apiKey);
```

#### Parameters

* `urlString` - The URL of the API endpoint. Example: `https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=YOUR_API_KEY`.
* `apiKey` - The API key to access the API. Example: `YOUR_API_KEY`.
* `tickerSymbol` - The symbol of the stock/ETF. Example: `SPY`.
* `fromDate` - The start date of the historical data. Example: `2023-08-10`. (YYYY-MM-DD)
* `toDate` - The end date of the historical data. Example: `2023-09-10`. (YYYY-MM-DD)
* `timeFrame` - The time frame of the historical data. Example: `4hour`. (Each API supports different time frames)
* `api` - The API to use for fetching the data. Example: `fml`. (Supported APIs: `fml`, `polygon`)

#### Return value

A `Json::Value` object that contains the fetched data. The type of the `Json::Value` may differ but generally it will be an array.

#### Complexity

The complexity of this function is `O(N)` where `N` is the size of the fetched data.

#### Exceptions

* If the user provided arguments are invalid, the function will throw [std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument).

#### Examples

```cpp
// Example using just URL
// Note: You need to provide your own API key otherwise the function will fail
Fetcher::fetchHistoricalData("https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=YOUR_API_KEY");

// Example using URL and API key
Fetcher::fetchHistoricalData("https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10", "YOUR_API_KEY");

// Example using ticker symbol, from date, to date, time frame, API and API key
Fetcher::fetchHistoricalData("SPY", "2023-08-10", "2023-09-10", "4hour", "fml", "YOUR_API_KEY");
```