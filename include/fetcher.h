/*
Date: 12/06/2024

Description: This file contains the declarations of the functions used to fetch data from an API.

Notes: x
*/

#ifndef FETCHER_H
#define FETCHER_H

#include <curl/curl.h>
#include <json/json.h>
#include <memory>
#include <string>
#include "tools.h"

namespace Fetcher
{
        std::unique_ptr<Json::Value> fetchRequestedData(const Tools::URL& url);
        void writeRequestedData(const std::unique_ptr<Json::Value>& root, const Tools::FilePath& filePath);
        size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
        CURL* init_curl(Tools::URL url, std::string& readBuffer);
        CURLcode perform_request(CURL* curl);
        Tools::Flag checkFMP_APIResponse(const std::unique_ptr<Json::Value>& root);
}

#endif // FETCHER_H