/*
Date: 15/06/2024

Description: This file contains the declarations of the functions used to control the flow of the programme.

Notes: x
*/

#ifndef FLOWCONTROL_H
#define FLOWCONTROL_H

#include <json/json.h>
#include <string>
#include "../src/include/constants.h"
#include "../src/include/inputHandler.h"

namespace Fetcher
{
        namespace FlowControl
        {
                Json::Value handleUserRequest(const InputHandler::RawUserInput& rawUserInput, InputHandler::ProcessedUserInput& processedUserInput);
                Tools::Flag controlFlow(const InputHandler::ProcessedUserInput& processedUserInput);
                Tools::Flag handleProgramme(const InputHandler::ProcessedUserInput& processedUserInput);
                Tools::Flag runTests();
                Tools::Flag runProgram(const InputHandler::ProcessedUserInput& processedUserInput);
                Tools::Flag checkFlag(const Tools::Flag flag);
                bool checkSuccessFlag(const Tools::Flag& flag);
                void handleHardcodeAPIKey();
        }
}

#endif // !FLOWCONTROL_H