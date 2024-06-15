/*
Date: 15/06/2024

Description: This file contains the declarations of the functions used to control the flow of the programme.

Notes: x
*/

#ifndef FLOWCONTROL_H
#define FLOWCONTROL_H

#include <boost/program_options.hpp>
#include <string>
#include "../include/constants.h"

namespace Fetcher
{
        namespace FlowControl
        {
                Tools::Flag controlFlow(int argc, char **argv);
                Tools::Flag runTests(int argc, char **argv);
                Tools::Flag runProgram(const std::unique_ptr<boost::program_options::variables_map>& vm);
                Tools::Flag endProgram(const Tools::Flag flag);
                bool checkFlag(const Tools::Flag& flag);
                bool checkProgramArguments(const std::unique_ptr<boost::program_options::variables_map>& vm);
        }
}

#endif // !FLOWCONTROL_H