/*
Date: 15/06/2024

Description: This file contains the definitions of the functions used to control the flow of the programme.

Notes: x
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "../include/constants.h"
#include "../include/fetcher.h"
#include "../include/flowControl.h"
#include "../include/parser.h"
#include "../include/tools.h"

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
                Tools::Flag controlFlow(int argc, char **argv)
                {
                        // Initialize the flag
                        Tools::Flag flag(Constants::SUCCESS);

                        // Parse the command line arguments
                        auto vm = Parser::parseArguments(argc, argv, flag);

                        // Handle hardcoded API key
                        handleHardcodeAPIKey();

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
                        if (Tools::checkProgramArguments(vm))
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
                Tools::Flag runTests(int argc, char **argv)
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
                Tools::Flag runProgram(const std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        Tools::URL url = Tools::getURL(vm);

                        // Check if the URL is valid
                        if (!Tools::checkValidURL(url))
                        {
                                // There is no reason to continue if the URL is missing
                                spdlog::error("Invalid URL: {}. The programme must be terminated.", url);
                                return Constants::FAILURE_END;
                        }

                        // Fetch the requested data
                        auto data = Fetcher::fetchRequestedData(Tools::getURL(vm));

                        // Check if the data was fetched successfully
                        if (data == nullptr)
                        {
                                return Constants::FAILURE;
                        }
                        // Check if the response from FMP API is successful
                        else if (!checkFlag(Fetcher::checkAPIResponse(data)))
                        {
                                return Constants::FAILURE;
                        }

                        // Write the fetched data to a file
                        Fetcher::writeRequestedData(data, Tools::getOutputFilePath(vm));

                        return Constants::SUCCESS;
                }

                /*
                End the programme.

                @param flag: The flag to determine if the programme finished successfully.
                */
                Tools::Flag endProgram(const Tools::Flag flag)
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
                bool checkFlag(const Tools::Flag& flag)
                {
                        return flag == Constants::SUCCESS;
                }

                /*
                Handle the hard-coded API key.
                */
                void handleHardcodeAPIKey()
                {
                        // Check if the API key is hard-coded
                        if (Tools::checkHardcodedAPIKey())
                        {
                                spdlog::warn("The API key is hardcoded in the code. Don't forget to remove it before pushing on git or deploying.");
                                return;
                        }

                        // The API key is not hard-coded
                        spdlog::info("The API key is not present in the code.");
                }
        }
}