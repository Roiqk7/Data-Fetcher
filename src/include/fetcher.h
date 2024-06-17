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
        Json::Value parseRequestedData(const std::string& readBuffer);
        void writeRequestedData(const std::unique_ptr<Json::Value>& root, const Tools::FilePath& filePath);
        Tools::Flag handleRequest(const Tools::URL& url, std::string& readBuffer);
        size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
        CURL* initCurl(Tools::URL url, std::string& readBuffer);
        CURLcode performRequest(CURL* curl);
        Tools::Flag checkAPIResponseForError(const std::unique_ptr<Json::Value>& root, std::string& errorMessageBuffer);
        Tools::Flag checkJsonObjectForErrorMessage(const Json::Value& root, std::string& errorMessageBuffer);
}

#endif // FETCHER_H