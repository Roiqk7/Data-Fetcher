/*
Date: 12/06/2024

Description: This file contains the declarations of the functions used to fetch data from an API.

Notes: x
*/

#ifndef FETCHER_H
#define FETCHER_H

#include <curl/curl.h>
#include <json/json.h>
#include <string>

namespace Fetcher
{
        size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
        CURL* init_curl(std::string url, std::string& readBuffer);
        CURLcode perform_request(CURL* curl);
}

#endif // FETCHER_H