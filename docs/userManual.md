# Welcome to [Data Fetcher](https://github.com/Roiqk7/Data-Fetcher)!

In this short document I will explain how to use this library to fetch the desired data from supported APIs. First of all,
I assume you have already read the [README](https://github.com/Roiqk7/Data-Fetcher/blob/main/README.md) file and have
installed the library. provided with this library. If you haven't, please do so before continuing.

## Table of contents
- [Welcome to Data Fetcher!](#welcome-to-data-fetcher)
  - [Table of contents](#table-of-contents)
  - [Documentation](#documentation)
  - [Functions defined in header \<dataFetcher/dataFetcher.h\>](#functions-defined-in-header-datafetcherdatafetcherh)
    - [fetchHistoricalData()](#fetchhistoricaldata)
      - [Declarations](#declarations)
      - [Parameters](#parameters)
      - [Return value](#return-value)
      - [Complexity](#complexity)
      - [Exceptions](#exceptions)
      - [Examples](#examples)
  - [Exceptions defined in header "src/include/exceptions.h"](#exceptions-defined-in-header-srcincludeexceptionsh)
    - [HTTPRequestFailed](#httprequestfailed)
    - [FailedToParseRequestedData](#failedtoparserequesteddata)
    - [FailedToFetchRequestedData](#failedtofetchrequesteddata)
    - [ApiResponseError](#apiresponseerror)
    - [UnexpectedJsonType](#unexpectedjsontype)

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

* `urlString` - The URL of the API endpoint. Example: `https://financialmodelingprep.com/api/v3/historical-chart/4hour/SPY?from=2023-08-10&to=2023-09-10&apikey=YOUR_API_KEY`. **Note:** You can also leave out API key parameter and provide it separately.
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

The function's behavior in response to various errors is as follows:

- Throws [std::invalid_argument](https://en.cppreference.com/w/cpp/error/invalid_argument) for invalid user-provided arguments.
- Throws Fetcher::Exceptions::HTTPRequestFailed for HTTP request failures.
- Throws Fetcher::Exceptions::FailedToParseRequestedData if the fetched data cannot be parsed.
- Triggers Fetcher::Exceptions::ApiResponseError for all errors thrown by the API.
- Throws Fetcher::Exceptions::FailedToFetchRequestedData when fetching of the requested data fails.
- Triggers Fetcher::Exceptions::UnexpectedJsonType for unexpected Json types in the fetched data.

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

## Exceptions defined in header "src/include/exceptions.h"

This section documents the exceptions defined in `src/include/exceptions.h`. These exceptions are designed to handle various error conditions that can occur during the fetching process.

### HTTPRequestFailed

This exception is thrown when an HTTP request fails to complete successfully. It could be due to network issues, server errors, or invalid URLs.

### FailedToParseRequestedData

Thrown when the program encounters an error while trying to parse data. This could happen if the data format is not as expected, or if the data is corrupted.

### FailedToFetchRequestedData

This exception is raised when the application is unable to fetch the requested data. This could be due to issues with the data source, such as unavailability or access restrictions.

### ApiResponseError

Raised when an API response indicates an error. This exception is used to handle error responses from APIs, including those with error codes and messages.

### UnexpectedJsonType

This exception is thrown when the type of a JSON element does not match the expected type. It is useful for catching type mismatches during JSON parsing.