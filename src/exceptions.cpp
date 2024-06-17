/*
Date: 16/06/2024

Description: This file contains definitions of custom exceptions used in the programme.

Notes: x
*/

#include <exception>
#include <string>
#include "../src/include/exceptions.h"

namespace Fetcher
{
        namespace Exceptions
        {
                HTTPRequestFailed::HTTPRequestFailed(const std::string& message)
                        : message(message) {}

                const char* HTTPRequestFailed::what() const noexcept
                {
                        return message.c_str();
                }

                FailedToParseRequestedData::FailedToParseRequestedData(const std::string& message)
                        : message(message) {}

                const char* FailedToParseRequestedData::what() const noexcept
                {
                        return message.c_str();
                }

                FailedToFetchRequestedData::FailedToFetchRequestedData(const std::string& message)
                        : message(message) {}

                const char* FailedToFetchRequestedData::what() const noexcept
                {
                        return message.c_str();
                }

                ApiResponseError::ApiResponseError(const std::string& message)
                        : message(message) {}

                const char* ApiResponseError::what() const noexcept
                {
                        return message.c_str();
                }

                UnexpectedJsonType::UnexpectedJsonType(const std::string& message)
                        : message(message) {}

                const char* UnexpectedJsonType::what() const noexcept
                {
                        return message.c_str();
                }
        }
}