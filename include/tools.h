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