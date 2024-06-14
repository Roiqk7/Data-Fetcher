/*
Date: 12/06/2024

Description: This file contains the main function for this module.

Notes: x
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "../include/fetcher.h"
#include "../include/parser.h"

/*
Main function for the module.

@param argc: The number of command line arguments.
@param argv: The command line arguments.
        - from or f: The start date in YYYY-MM-DD format.
        - to or t: The end date in YYYY-MM-DD format.
        - timeframe or tf: The time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).
        - test: Run unit tests. Use this option without a value.

@return: 0 if the program runs successfully.
*/
int main(int argc, char **argv)
{
        // Create an instance of the options description
        auto desc = Fetcher::Parser::createOptionsDescription();

        // Parse the command line arguments
        boost::program_options::variables_map vm;
        Fetcher::Parser::parseCommandLineArguments(argc, argv, desc, vm);

        // Process the parsed options
        Fetcher::Parser::processParsedOptions(vm, desc);

        // Check if the --test argument was provided
        if (vm.count("test"))
        {
                // Initialize Google Test
                ::testing::InitGoogleTest(&argc, argv);

                // Run all the tests
                return RUN_ALL_TESTS();
        }

        // Check if the required arguments are provided
        if ((vm.count("from") || vm.count("f")) && (vm.count("to") || vm.count("t")) && (vm.count("timeframe") || vm.count("tf")))
        {
                std::string from_date = vm.count("from") ? vm["from"].as<std::string>() : vm["f"].as<std::string>();
                std::string to_date = vm.count("to") ? vm["to"].as<std::string>() : vm["t"].as<std::string>();
                std::string timeframe = vm.count("timeframe") ? vm["timeframe"].as<std::string>() : vm["tf"].as<std::string>();

                // Example of using the parsed arguments
                spdlog::info("Fetching data from {} to {} with timeframe {}", from_date, to_date, timeframe);

                // Fetch the requested data and write them into the ../data/data.json file
                Fetcher::fetchRequestedData(from_date, to_date, timeframe);
        }
        else
        {
                spdlog::error("Missing required arguments: from, to, and/or timeframe");
                return 1; // Exit with error code
        }

        return 0;
}