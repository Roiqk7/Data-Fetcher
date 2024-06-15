/*
Date: 15/06/2024

Description: This file contains the definitions of the functions used to control the flow of the programme.

Notes: x
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "../include/fetcher.h"
#include "../include/flowControl.h"
#include "../include/parser.h"

namespace Fetcher
{
        namespace FlowControl
        {
                /*
                Runs the program based on the command line arguments.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.

                @return: True if the programme finished successfully, false otherwise.
                */
                Constants::Flag controlFlow(int argc, char **argv)
                {
                        // Initialize the flag
                        Constants::Flag flag;

                        // Parse the command line arguments
                        auto vm = Parser::parseArguments(argc, argv, flag);

                        // Check if the --test argument was provided
                        if (vm->count("test"))
                        {
                                flag = runTests(argc, argv);
                                if (!checkFlag(flag))
                                {
                                        // End the programme if the tests failed
                                        return endProgram(flag);
                                }
                        }

                        // Check if the required arguments for running the program are provided
                        if (checkProgramArguments(vm))
                        {
                                flag = runProgram(vm);
                                if (!checkFlag(flag))
                                {
                                        // End the programme if the program failed
                                        return endProgram(flag);
                                }
                        }

                        // End the programme
                        return endProgram(flag);
                }

                /*
                Run the unit tests.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.

                @return: The flag to determine if the tests ran successfully.
                */
                Constants::Flag runTests(int argc, char **argv)
                {
                        // Initialize Google Test
                        ::testing::InitGoogleTest(&argc, argv);

                        // Run all the tests
                        return RUN_ALL_TESTS();
                }

                /*
                Run the programme.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.

                @return: The flag to determine if the programme ran successfully.
                */
                Constants::Flag runProgram(const std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        // Get the start date, end date, and timeframe
                        std::string from_date = vm->count("from") ? (*vm)["from"].as<std::string>() : (*vm)["f"].as<std::string>();
                        std::string to_date = vm->count("to") ? (*vm)["to"].as<std::string>() : (*vm)["t"].as<std::string>();
                        std::string timeframe = vm->count("timeframe") ? (*vm)["timeframe"].as<std::string>() : (*vm)["tf"].as<std::string>();

                        // Example of using the parsed arguments
                        spdlog::info("Fetching data from {} to {} with timeframe {}", from_date, to_date, timeframe);

                        // Fetch the requested data and write them into the ../data/data.json file
                        Fetcher::fetchRequestedData(from_date, to_date, timeframe);

                        return Constants::SUCCESS;
                }

                /*
                End the programme.

                @param flag: The flag to determine if the programme finished successfully.
                */
                Constants::Flag endProgram(const Constants::Flag flag)
                {
                        if (flag == Constants::FAILURE)
                        {
                                spdlog::error("The programme failed.");
                        }
                        else if (flag == Constants::FAILURE_END)
                        {
                                spdlog::error("The programme failed and must be terminated.");
                        }
                        else if (flag == Constants::SUCCESS_END)
                        {
                                spdlog::info("The programme finished successfully and must be terminated.");
                        }
                        else
                        spdlog::info("The programme finished successfully.");

                        return flag;
                }

                /*
                Check if the flag is successful.

                @param flag: The flag to check.

                @return: True if the flag is successful, false otherwise.
                */
                bool checkFlag(const Constants::Flag& flag)
                {
                        return flag == Constants::SUCCESS;
                }

                /*
                Check if the required arguments for running the programme are provided.

                @param vm: The variables map.

                @return: True if the required arguments are provided, false otherwise.
                */
                bool checkProgramArguments(const std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        // Note: The program requires the --from, --to, and --timeframe arguments to be provided all at the same time
                        return (vm->count("from") || vm->count("f")) && (vm->count("to") || vm->count("t")) && (vm->count("timeframe") || vm->count("tf"));
                }
        }
}