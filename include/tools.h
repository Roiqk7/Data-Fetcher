/*
Date: 12/06/2024

Description: This file contains the declarations of helper functions used in the Fetcher module.

Notes: x
*/

#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include "constants.h"

namespace Fetcher
{
        namespace Tools
        {
                // Function to hide the API key in the URL
                Constants::URL hideApiKey(const Constants::URL& url);

                // Read contents of a file
                std::string readFileContents(const std::string& filePath);

                // Write contents to a file
                void writeFileContents(const std::string& filePath, const std::string& contents);
        }
}

#endif // !TOOLS_H