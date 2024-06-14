/* 
Date: 13/06/2024

Description: This file contains the implementation of the helper functions used in the Fetcher module.

Notes: x
*/

#include "../include/constants.h"
#include "../include/tools.h"

namespace Fetcher
{
        namespace Tools
        {
                // Function to hide the API key in the URL
                Constants::URL hide_api_key(const Constants::URL& url)
                {
                        Constants::URL hiddenApiKey = url;
                        size_t pos = hiddenApiKey.find(Constants::API_KEY);
                        if (pos != Constants::URL::npos)
                        {
                                hiddenApiKey.replace(pos, Constants::API_KEY.length(), "********");
                        }

                        return hiddenApiKey;
                }
        }
}