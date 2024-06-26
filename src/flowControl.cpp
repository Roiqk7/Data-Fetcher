/*
Date: 15/06/2024

Description: This file contains the definitions of the functions used to control the flow of the programme.

Notes: x
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "tools.h"
#include "constants.h"
#include "exceptions.h"
#include "fetcher.h"
#include "flowControl.h"
#include "inputHandler.h"

namespace Fetcher
{
        namespace FlowControl
        {
                /*
                Handle the user request.

                @param rawUserInput: The raw user input.
                @param processedUserInput: The processed user input.

                @return: The fetched data.
                */
                Json::Value handleUserRequest(const InputHandler::RawUserInput& rawUserInput, InputHandler::ProcessedUserInput& processedUserInput)
                {
                        // Log the raw user input
                        rawUserInput.logRawUserInput();

                        // Process the user input
                        InputHandler::proccessUserInput(rawUserInput, processedUserInput);

                        // Log the processed user input
                        processedUserInput.logProcessedUserInput();

                        // Run the program
                        FlowControl::controlFlow(processedUserInput);

                        // Read the fetched data
                        const Json::Value fetchedData = Tools::readJsonFileContents(Constants::FETCHED_DATA_FILE_PATH);

                        return fetchedData;
                }

                /*
                Runs the program based on the command line arguments.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.

                @return: True if the programme finished successfully, false otherwise.
                */
                Tools::Flag controlFlow(const InputHandler::ProcessedUserInput& processedUserInput)
                {
                        // Initialize the flag optimistically as success by default
                        Tools::Flag flag(Constants::SUCCESS);

                        // Handle hardcoded API key
                        handleHardcodeAPIKey();

                        // Handle the programme based on the command line arguments
                        flag = handleProgramme(processedUserInput);

                        // End the programme
                        return checkFlag(flag);
                }

                /*
                Handle the programme based on the command line arguments.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.
                @param vm: The variables map containing the parsed arguments.

                @return: The flag to determine if the programme ran successfully.
                */
                Tools::Flag handleProgramme(const InputHandler::ProcessedUserInput& processedUserInput)
                {
                        Tools::Flag flag(Constants::SUCCESS);

                        // Check if the test argument was provided
                        if (processedUserInput.test)
                        {
                                flag = runTests();
                                if (!checkSuccessFlag(flag))
                                {
                                        // Handle failed tests
                                        return checkFlag(flag);
                                }
                        }
                        // Check if the required arguments for running the program are provided
                        else if (!processedUserInput.url.empty())
                        {
                                flag = runProgram(processedUserInput);
                                if (!checkSuccessFlag(flag))
                                {
                                        // Handle failed programme
                                        return checkFlag(flag);
                                }
                        }
                        else
                        {
                                spdlog::error("No URL provided.");
                                throw std::invalid_argument("No URL provided.");
                        }

                        return flag;
                }

                /*
                Run the unit tests.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.

                @return: The flag to determine if the tests ran successfully.
                */
                Tools::Flag runTests()
                {
                        // Initialize Google Test
                        ::testing::InitGoogleTest();

                        return RUN_ALL_TESTS();
                }

                /*
                Run the programme.

                @param vm: The variables map containing the parsed arguments.

                @return: The flag to determine if the programme ran successfully.
                */
                Tools::Flag runProgram(const InputHandler::ProcessedUserInput& processedUserInput)
                {
                        std::string errorMessageBuffer;
                        Tools::URL url = processedUserInput.url;

                        // Fetch the requested data
                        auto data = Fetcher::fetchRequestedData(processedUserInput.url);

                        // Check if the data was fetched successfully
                        if (data == nullptr)
                        {
                                spdlog::error("Failed to fetch the requested data.");
                                throw Exceptions::FailedToFetchRequestedData("Failed to fetch the requested data.");
                        }
                        // Check if the response from FMP API is successful
                        else if (!checkSuccessFlag(Fetcher::checkAPIResponseForError(data, errorMessageBuffer)))
                        {
                                spdlog::error("Error in the API response found. {}", errorMessageBuffer);
                                throw Exceptions::ApiResponseError(errorMessageBuffer);
                        }

                        // Write the fetched data to a file
                        Fetcher::writeRequestedData(data, Constants::FETCHED_DATA_FILE_PATH);

                        return Constants::SUCCESS;
                }

                /*
                Check the flag and log the outcome of the programme.
                Exits the programme if the flag indicates that the programme must be terminated.

                @param flag: The flag to determine if the programme finished successfully.
                */
                Tools::Flag checkFlag(const Tools::Flag flag)
                {
                        switch (flag)
                        {
                                case Constants::SUCCESS:
                                        spdlog::info("Success flag received.");
                                        break;
                                case Constants::FAILURE:
                                        spdlog::error("Failure flag received.");
                                        break;
                                case Constants::SUCCESS_END:
                                        spdlog::info("Success flag received and programme must be terminated.");
                                        exit(Constants::SUCCESS);
                                        break;
                                case Constants::FAILURE_END:
                                        spdlog::error("Failure flag received and programme must be terminated.");
                                        exit(Constants::FAILURE);
                                        break;
                                default:
                                        spdlog::error("Unknown flag: {}. The programme must be terminated.", flag);
                                        exit(Constants::FAILURE);
                        }

                        return flag;
                }

                /*
                Check if the flag is successful.

                @param flag: The flag to check.

                @return: True if the flag is successful, false otherwise.
                */
                bool checkSuccessFlag(const Tools::Flag& flag)
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
                        spdlog::trace("The API key is not present in the code.");
                }
        }
}