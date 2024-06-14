/*
Date: 12/06/2024

Description: This file contains the definitions of the parser functions.

Notes: x
*/

#include "../include/parser.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

namespace Fetcher
{
        namespace Parser
        {
                /*
                Parse the command line arguments and process them.

                @param argc: The number of command line arguments.
                @param argv: The command line arguments.

                @return: 0 if the arguments are parsed successfully.
                */
                int parseArguments(int argc, char **argv)
                {
                        auto desc = createOptionsDescription();
                        boost::program_options::variables_map vm;
                        parseCommandLineArguments(argc, argv, desc, vm);
                        processParsedOptions(vm, desc);
                        return 0;
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
                                ("from,f", boost::program_options::value<std::string>(), "Start date in YYYY-MM-DD format.")
                                ("to,t", boost::program_options::value<std::string>(), "End date in YYYY-MM-DD format.")
                                ("timeframe,tf", boost::program_options::value<std::string>(), "Time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).")
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
                void parseCommandLineArguments(int argc, char **argv, boost::program_options::options_description& desc, boost::program_options::variables_map& vm)
                {
                        try
                        {
                                boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
                                boost::program_options::notify(vm);
                        }
                        catch(std::exception& e)
                        {
                                spdlog::error("Error: {}", e.what());
                                exit(1);
                        }
                        catch(...)
                        {
                                spdlog::error("Unknown error!");
                                exit(1);
                        }
                }

                /*
                Function to process the parsed options.

                @param vm: The variables map.
                @param desc: The options description.
                */
                void processParsedOptions(const boost::program_options::variables_map& vm, const boost::program_options::options_description& desc)
                {
                        if (vm.count("help"))
                        {
                                std::cout << desc << "\n";
                                exit(1);
                        }

                        // Add your logic here based on the parsed arguments
                        spdlog::info("Running with provided arguments.");
                }
        }
}