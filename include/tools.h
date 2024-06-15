/*
Date: 12/06/2024

Description: This file contains the declarations of helper functions used in the Fetcher module.

Notes: x
*/

#ifndef TOOLS_H
#define TOOLS_H

#include <boost/program_options.hpp>
#include <string>

namespace Fetcher
{
        namespace Tools
        {
        // Typedefs
                using Flag = int; // Defines the flag data type
                using FilePath = std::string; // File path data type
                using URL = std::string; // URL data type used in communication with the API
        // Functions
                bool checkProgramArguments(const std::unique_ptr<boost::program_options::variables_map>& vm);
                bool checkURLArgument(const std::unique_ptr<boost::program_options::variables_map>& vm);
                bool checkFromToTimeFrameArguments(const std::unique_ptr<boost::program_options::variables_map>& vm);
                URL hideApiKey(const URL& url);
                URL createUrl(const std::string& fromDate, const std::string& toDate, const std::string& timeFrame);
                URL getURL(const std::unique_ptr<boost::program_options::variables_map>& vm);
                FilePath getOutputFilePath(const std::unique_ptr<boost::program_options::variables_map>& vm);
                std::string readFileContents(const FilePath& filePath);
                void writeFileContents(const FilePath& filePath, const std::string& contents);
        }
}

#endif // !TOOLS_H