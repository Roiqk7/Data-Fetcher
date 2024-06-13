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
        Json::Value parse_data(std::string readBuffer);
        void print_option_data(const Json::Value& jsonData);
        void fetch_option_data(const std::string& ticker_symbol);
}

#endif // FETCHER_H