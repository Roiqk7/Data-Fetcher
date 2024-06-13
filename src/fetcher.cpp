/*
Date: 12/06/2024

Description:

Notes: x
*/

#include <curl/curl.h>
#include <iostream>
#include <json/json.h>
#include <sstream>
#include "constants.h"

namespace Fetcher
{
        /*
        Callback function to write received data to a string.

        @param contents: The received data

        @param size: The size of the data
        */
        size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp)
        {
                userp->append((char*)contents, size * nmemb);
                return size * nmemb;
        }

        /*
        Initializes libcurl and sets the necessary options.

        @param url: The URL to which the HTTP request is to be made
        @param readBuffer: The string to which the received data is to be appended

        @return CURL*: The initialized CURL handle
        */
        CURL* init_curl(std::string url, std::string& readBuffer)
        {
                CURL* curl = curl_easy_init();
                if(curl)
                {
                        // Append the API key to the URL
                        url += Constants::API_KEY;
                        // Set the URL and callback function
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                }
                return curl;
        }

        /*
        Performs the HTTP request and cleans up the CURL handle.

        @param curl: The CURL handle

        @return CURLcode: The result of the HTTP request
        */
        CURLcode perform_request(CURL* curl)
        {
                CURLcode res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                return res;
        }
}
