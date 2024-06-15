/*
Date: 12/06/2024

Description: This file contains the main function for this module.

Notes: x
*/

#include "../include/constants.h"
#include "../include/flowControl.h"

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
        // Runs the program based on the command line arguments
        const Fetcher::Constants::Flag flag = Fetcher::FlowControl::controlFlow(argc, argv);

        return flag;
}