/*
Date: 12/06/2024

Description: This file contains the declarations of helper functions used in the Fetcher module.

Notes: x
*/

#ifndef TOOLS_H
#define TOOLS_H

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
                URL hideApiKey(const URL& url);
                std::string readFileContents(const FilePath& filePath);
                void writeFileContents(const FilePath& filePath, const std::string& contents);
        }
}

#endif // !TOOLS_H