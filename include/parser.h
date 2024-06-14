/*
Date: 12/06/2024

Description: This file contains the declarations of the parser functions.

Notes: x
*/

#ifndef PARSER_H
#define PARSER_H

#include <boost/program_options.hpp>

namespace Fetcher
{
        namespace Parser
        {
                boost::program_options::options_description createOptionsDescription();
                void parseCommandLineArguments(int argc, char **argv, boost::program_options::options_description& desc, boost::program_options::variables_map& vm);
                void processParsedOptions(const boost::program_options::variables_map& vm, const boost::program_options::options_description& desc);
        }
}

#endif // !PARSER_H