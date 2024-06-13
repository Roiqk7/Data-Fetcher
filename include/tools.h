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
                // Function to hide the API key in the URL
                std::string hide_api_key(const std::string& url);
        }
}

#endif // !TOOLS_H