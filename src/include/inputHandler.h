/*
Date: 16/06/2024

Description: Used to handle user input.

Notes: x
*/

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
#include "../../include/tools.h"

namespace Fetcher
{
        namespace InputHandler
        {
        // Structs
                /*
                Stores raw user input.
                */
                struct RawUserInput
                {
                public:
                        std::string url; // The URL to fetch data from.
                        std::string api; // The API to use.
                        std::string apiKey; // The API key to use.
                        std::string tickerSymbol; // The ticker symbol to fetch data for.
                        std::string from; // The start date in YYYY-MM-DD format.
                        std::string to; // The end date in YYYY-MM-DD format.
                        std::string timeframe; // The time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).
                        bool test; // Run unit tests.
                public:
                // Constructors
                        RawUserInput();
                        RawUserInput(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate,
                                const std::string& timeFrame, const std::string& api, const std::string& apiKey);
                        RawUserInput(const std::string& urlString);
                        RawUserInput(const std::string& urlString, const std::string& apiKey);
                // Functions
                        void logRawUserInput() const; // Log the raw user input.
                };

                /*
                Stores processed user input.
                */
                struct ProcessedUserInput
                {
                public:
                        Tools::URL url; // The URL to fetch data from.
                        bool test; // Run unit tests.
                public:
                // Constructors
                        ProcessedUserInput(); // Default constructor.
                        ProcessedUserInput(bool test); // Constructor.
                // Functions
                        void logProcessedUserInput() const; // Log the processed user input.
                };

        // Functions
                void userInputValidator(const std::vector<std::string>& args, const std::vector<std::string>& argNames);
                void proccessUserInput(const RawUserInput& rawUserInput, ProcessedUserInput& processedUserInput);
                Tools::URL createUrl(const std::string& url);
                Tools::URL createUrl(const std::string& url, const std::string& apiKey);
                Tools::URL createUrl(const std::string& tickerSymbol, const std::string& fromDate,
                        const std::string& toDate, const std::string& timeFrame, const std::string& api, const std::string& apiKey);
                bool checkForUrl(const RawUserInput& rawInput);
                bool checkFromToTimeFrame(const std::string& fromDate, const std::string& toDate, const std::string& timeFrame);
                bool checkUrlForApiKey(const Tools::URL& url);
        }
}


#endif // !INPUTHANDLER_H