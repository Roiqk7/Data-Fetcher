/*
Date: 12/06/2024

Description: This file contains the definitions of the functions used to fetch data from an API.

Notes: x
*/

#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include "../include/constants.h"
#include "../include/fetcher.h"
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
        std::unique_ptr<Json::Value> fetchRequestedData(const std::string& fromDate, const std::string& toDate, const std::string& timeframe)
        {
                // Create the URL
                Constants::URL url = Constants::API_URL + Constants::HISTORICAL_DATA_ENDPOINT + timeframe + Constants::SLASH
                        + Constants::SPY + Constants::QUESTION_MARK + "from=" + fromDate + Constants::AND
                        + "to=" + toDate + Constants::AND + Constants::API_KEY_PARAM + Constants::API_KEY;
                std::string readBuffer; // Buffer to store the fetched data

                // Hide the API key in the log
                Constants::URL hiddenApiKey = Tools::hideApiKey(url);
                spdlog::info("URL: {}", hiddenApiKey);

                // Initialize libcurl
                CURL* curl = init_curl(url, readBuffer);

                // Perform the HTTP request
                CURLcode res = perform_request(curl);

                // Check if the request was successful
                if(res != CURLE_OK)
                {
                        spdlog::error("Failed to fetch data: {}", curl_easy_strerror(res));
                        return nullptr;
                }

                // Initialize the Json::Value object
                std::unique_ptr<Json::Value> root(new Json::Value());
                Json::Reader reader;

                // Parse the received data
                bool parsingSuccessful = reader.parse(readBuffer, *root);

                // Check if the parsing was successful
                if(!parsingSuccessful)
                {
                        spdlog::error("Failed to parse data: {}", reader.getFormattedErrorMessages());
                        return nullptr;
                }

                return root;
        }

        /*
        Writes the requested data to specified file.

        @param root: The Json::Value object containing the data
        @param filePath: The path to the file
        */
        void writeRequestedData(const std::unique_ptr<Json::Value>& root, const Constants::FilePath& filePath)
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
                        spdlog::warn("Failed to open file: {}\nWriting data to ../data/data.json", filePath);
                        writeRequestedData(root, Constants::DEFAULT_DATA_FILE_PATH);
                }
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
        CURL* init_curl(Constants::URL url, std::string& readBuffer)
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
