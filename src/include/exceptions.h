/*
Date: 16/06/2024

Description: This file contains declarations of custom exceptions used in the programme.

Notes: x
*/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

namespace Fetcher
{
        namespace Exceptions
        {
                class HTTPRequestFailed : public std::exception
                {
                public:
                        HTTPRequestFailed(const std::string& message);

                        virtual const char* what() const noexcept override;
                private:
                        std::string message;
                };

                class FailedToParseRequestedData : public std::exception
                {
                public:
                        FailedToParseRequestedData(const std::string& message);

                        virtual const char* what() const noexcept override;
                private:
                        std::string message;
                };

                class FailedToFetchRequestedData : public std::exception
                {
                public:
                        FailedToFetchRequestedData(const std::string& message);

                        virtual const char* what() const noexcept override;
                private:
                        std::string message;
                };

                class ApiResponseError : public std::exception
                {
                public:
                        ApiResponseError(const std::string& message);

                        virtual const char* what() const noexcept override;
                private:
                        std::string message;
                };

                class UnexpectedJsonType : public std::exception
                {
                public:
                        UnexpectedJsonType(const std::string& message);

                        virtual const char* what() const noexcept override;
                private:
                        std::string message;
                };
        }
}

#endif // !EXCEPTIONS_H