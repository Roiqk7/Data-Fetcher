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
                Constants::URL hide_api_key(const Constants::URL& url);
        }
}

#endif // !TOOLS_H