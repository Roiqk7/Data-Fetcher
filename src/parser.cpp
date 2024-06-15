/*
Date: 12/06/2024

Description: This file contains the definitions of the parser functions.

Notes: x
*/

#include <boost/program_options.hpp>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include "../include/constants.h"
#include "../include/parser.h"

namespace Fetcher
{
        namespace Parser
        {
                /*
                Parse the command line arguments and process them.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.
                @param flag: The flag to be set based on the parsed arguments.

                @return: The variables map containing the parsed arguments.
                */
                std::unique_ptr<boost::program_options::variables_map> parseArguments(int argc, char **argv, Tools::Flag& flag)
                {
                        auto desc = createOptionsDescription();
                        auto vm = std::make_unique<boost::program_options::variables_map>();
                        parseCommandLineArguments(argc, argv, desc, vm);
                        processParsedOptions(vm, desc);
                        return vm;
                }

                /*
                Wrapper function to create the options description.

                @return: The options description.
                */
                boost::program_options::options_description createOptionsDescription()
                {
                        boost::program_options::options_description desc("Allowed options");
                        desc.add_options()
                                ("help,h", "Produce help message.")
                                ("url,u", boost::program_options::value<std::string>(), "URL for fetching data from an API.")
                                ("apikey,k", boost::program_options::value<std::string>(), "API key required for authentication.")
                                ("from,f", boost::program_options::value<std::string>(), "Start date in YYYY-MM-DD format.")
                                ("to,t", boost::program_options::value<std::string>(), "End date in YYYY-MM-DD format.")
                                ("timeframe,m", boost::program_options::value<std::string>(), "Time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).")
                                ("output,o", boost::program_options::value<std::string>(), "File in which the fetched data will be stored. (../data/data.json by default)")
                                ("test", "Run unit tests. Use this option without a value.");
                        return desc;
                }

                /*
                Function to parse the command line arguments.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.
                @param desc: The options description.
                @param vm: The variables map.
                */
                void parseCommandLineArguments(int argc, char **argv, boost::program_options::options_description& desc, std::unique_ptr<boost::program_options::variables_map>& vm)
                {
                        try
                        {
                                boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), *vm);
                                boost::program_options::notify(*vm);
                        }
                        catch(std::exception& e)
                        {
                                spdlog::error("Error: {}", e.what());
                                exit(Constants::FAILURE);
                        }
                        catch(...)
                        {
                                spdlog::error("Unknown error!");
                                exit(Constants::FAILURE);
                        }
                }

                /*
                Function to process the parsed options.

                @param vm: The variables map.
                @param desc: The options description.
                */
                void processParsedOptions(const std::unique_ptr<boost::program_options::variables_map>& vm, const boost::program_options::options_description& desc)
                {
                        if (vm->count("help"))
                        {
                                std::cout << desc << "\n";
                                exit(Constants::SUCCESS);
                        }

                        spdlog::info("Running with provided arguments.");
                }
        }
}