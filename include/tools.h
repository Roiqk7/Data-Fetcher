/*
Date: 12/06/2024

Description: This file contains the declarations of helper functions used in the Fetcher module.

Notes: x
*/

#ifndef TOOLS_H
#define TOOLS_H


#include <json/json.h>
#include <memory>
#include <string>

namespace Fetcher
{
        namespace Tools
        {
        // Typedefs
                using Flag = int; // Defines the flag data type
                using FilePath = std::string; // File path data type
                using URL = std::string; // URL data type used in communication with the API
        // Functions
                bool checkProgramArguments(const InputHandler::RawUserInput& rawInput);
                bool checkURLArgument(const InputHandler::RawUserInput& rawInput);
                bool checkFromToTimeFrameArguments(const InputHandler::RawUserInput& rawInput);
                URL hideApiKey(const URL& url);
                URL createUrl(const std::string& fromDate, const std::string& toDate, const std::string& timeFrame);
                URL getURL(const InputHandler::RawUserInput& rawInput);
                bool checkValidURL(const URL& url);
                FilePath getOutputFilePath(const InputHandler::RawUserInput& rawInput);
                std::string readFileContents(const FilePath& filePath);
                Json::Value readJsonFileContents(const FilePath& filePath);
                void writeFileContents(const FilePath& filePath, const std::string& contents);
                bool checkHardcodedAPIKey();
        }
}

#endif // !TOOLS_H