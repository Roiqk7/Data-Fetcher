/*
Date: 12/06/2024

Description: This file contains the declarations of the parser functions.

Notes: x
*/

#ifndef PARSER_H
#define PARSER_H

#include <boost/program_options.hpp>
#include <memory>
#include "../src/include/constants.h"

namespace Fetcher
{
        namespace Parser
        {
                std::unique_ptr<boost::program_options::variables_map> parseArguments(int argc, char **argv, Tools::Flag& flag);
                boost::program_options::options_description createOptionsDescription();
                void parseCommandLineArguments(int argc, char **argv, boost::program_options::options_description& desc, std::unique_ptr<boost::program_options::variables_map>& vm);
                void processParsedOptions(const std::unique_ptr<boost::program_options::variables_map>& vm, const boost::program_options::options_description& desc);
                void addArgumentsToVariablesMap(const std::unique_ptr<boost::program_options::variables_map>& vm, const std::string& argument, const std::string& value);
        }
}

#endif // !PARSER_H