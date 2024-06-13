/* 
Date: 13/06/2024

Description:

Notes: x
*/

#include "../include/constants.h"
#include "../include/tools.h"

namespace Fetcher
{
        namespace Tools
        {
                // Function to hide the API key in the URL
                std::string hide_api_key(const std::string& url)
                {
                        std::string hiddenApiKey = url;
                        size_t pos = hiddenApiKey.find(Constants::API_KEY);
                        if (pos != std::string::npos)
                        {
                                hiddenApiKey.replace(pos, Constants::API_KEY.length(), "********");
                        }

                        return hiddenApiKey;
                }
        }
}