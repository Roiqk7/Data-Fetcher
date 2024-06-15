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
                Constants::Flag controlFlow(int argc, char **argv);
                Constants::Flag runTests(int argc, char **argv);
                Constants::Flag runProgram(const boost::program_options::variables_map& vm);
                Constants::Flag endProgram(const Constants::Flag flag);
                bool checkFlag(const Constants::Flag& flag);
        }
}

#endif // !FLOWCONTROL_H