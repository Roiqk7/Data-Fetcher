/*
Date: 12/06/2024

Description: This file contains the definitions of the functions used to fetch data from an API.

Notes: x
*/

#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include "../include/constants.h"
#include "../include/fetcher.h"
#include "../include/flowControl.h"
#include "../include/tools.h"

namespace Fetcher
{
        /*
        Fetches the requested data from the API and returns it

        @param fromDate: The start date in YYYY-MM-DD format.
        @param toDate: The end date in YYYY-MM-DD format.
        @param timeframe: The time frame for the operation (1min, 5min, 15min, 30min, 1hour, 4hour).

        @return: A unique pointer to the Json::Value object containing the fetched data.
        */
        std::unique_ptr<Json::Value> fetchRequestedData(const Tools::URL& url)
        {
                std::string readBuffer; // Buffer to store the fetched data

                // Hide the API key in the log
                Tools::URL hiddenApiKey = Tools::hideApiKey(url);
                spdlog::info("URL: {}", hiddenApiKey);

                // Fetch the data and check if the request was successful
                if(!FlowControl::checkFlag(handleRequest(url, readBuffer)))
                {
                        return nullptr;
                }

                // Parse the fetched data
                std::unique_ptr<Json::Value> root(std::make_unique<Json::Value>(parseRequestedData(readBuffer)));

                return root;
        }

        /*
        Parses the requested data from the API.

        @param readBuffer: The string containing the fetched data

        @return: The Json::Value object containing the parsed data
        */
        Json::Value parseRequestedData(const std::string& readBuffer)
        {
                Json::Value root; // This will store the parsed JSON data
                std::istringstream stream(readBuffer); // Convert string to stream for parsing
                Json::CharReaderBuilder builder; // Use the builder to create a reader
                JSONCPP_STRING errs; // This will store any parsing errors

                bool parsingSuccessful = Json::parseFromStream(builder, stream, &root, &errs);

                if (!parsingSuccessful)
                {
                        // If parsing fails, log the error and return an empty Json::Value
                        spdlog::error("Failed to parse JSON: {}", errs);
                        return Json::Value(); // Return an empty Json::Value object
                }

                return root; // Return the parsed JSON data
        }

        /*
        Writes the requested data to specified file.

        @param root: The Json::Value object containing the data
        @param filePath: The path to the file
        */
        void writeRequestedData(const std::unique_ptr<Json::Value>& root, const Tools::FilePath& filePath)
        {
                std::ofstream file(filePath);
                if(file.is_open())
                {
                        Json::StreamWriterBuilder builder;
                        const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                        writer->write(*root, &file);
                        file.close();
                        spdlog::info("Data written to {}", filePath);
                }
                else
                {
                        spdlog::warn("Failed to open file: {}. Writing data to ../data/data.json", filePath);
                        writeRequestedData(root, Constants::DEFAULT_DATA_FILE_PATH);
                }
        }

        /*
        Performs an HTTP request to a specified URL and appends the received data to a provided string.

        @param url: The URL to which the HTTP request is to be made
        @param readBuffer: The string to which the received data is to be appended

        @return: The flag to determine if the request was successful
        */
        Tools::Flag handleRequest(const Tools::URL& url, std::string& readBuffer)
        {
                // Initialize libcurl
                CURL* curl = initCurl(url, readBuffer);

                // Perform the HTTP request
                CURLcode res = performRequest(curl);

                // Check if the request was successful
                if(res != CURLE_OK)
                {
                        spdlog::error("Failed to fetch data: {}", curl_easy_strerror(res));
                        return Constants::FAILURE_END;
                }

                // Log the raw response data
                spdlog::trace("Raw response data: {}", readBuffer);

                return Constants::SUCCESS;
        }

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
        CURL* initCurl(Tools::URL url, std::string& readBuffer)
        {
                CURL* curl = curl_easy_init();
                if(curl)
                {
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
        CURLcode performRequest(CURL* curl)
        {
                CURLcode res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                return res;
        }

        /*
        Checks the response from FMP API.

        @param root: The Json::Value object containing the fetched data

        @return: The flag to determine if the response is successful

        Note: Works only with array type JSON objects.
        */
        Tools::Flag checkFMP_APIResponse(const std::unique_ptr<Json::Value>& root)
        {
                // Check if root is an array
                if (root && root->isArray())
                {
                        // Iterate through each element in the array
                        for (const Json::Value& item : *root)
                        {
                                // Check each object in the array for "Error Message"
                                if (item.isMember("Error Message"))
                                {
                                        spdlog::error("Error Message: {}", item["Error Message"].asString());
                                        return Constants::FAILURE;
                                }
                        }
                        return Constants::SUCCESS;
                }
                else
                {
                        // Log an error or handle the case where root is not an array
                        spdlog::error("Expected JSON array in API response.");
                        return Constants::FAILURE;
                }
        }
}
