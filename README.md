# Data Fetcher

This code is part of Project Mencator. This particular module is responsible for gathering input data using the [FMP](https://site.financialmodelingprep.com) and [Polygon.io](https://polygon.io).

## Table of contents
- [Data Fetcher](#data-fetcher)
  - [Table of contents](#table-of-contents)
  - [Dependencies](#dependencies)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Project structure](#project-structure)

## Dependencies

* [C++17](https://en.cppreference.com/w/cpp/17)
* [CMake](https://cmake.org/)
* [CURL](https://curl.se/)
* [GTest](https://github.com/google/googletest)
* [Json Cpp](https://github.com/open-source-parsers/jsoncpp)
* [spdlog](https://github.com/gabime/spdlog)

Installation of the dependencies on MacOS using Homebrew:

```bash
brew install boost &&
brew install cmake &&
brew install curl &&
brew install googletest &&
brew install jsoncpp &&
brew install spdlog
```

## Installation

After installing the dependencies, you can clone the repository:

```bash
git clone https://github.com/Roiqk7/Data-Fetcher.git
```

Then, you can build the project by navigating to the project directory and running the following commands:

```bash
mkdir build &&
cd build &&
cmake .. &&
make
```

## Usage

Include the library in your C++ project by including the header files:

```cpp
#include <dataFetcher/dataFetcher.h>
```

Then, you can use the functions provided by the library:

<detail>
<summary>Declarations</summary>

```cpp
        Json::Value fetchHistoricalData(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate,
                        const std::string& timeFrame, const std::string& api, const std::string& apiKey);
        Json::Value fetchHistoricalData(const std::string& urlString);
        Json::Value fetchHistoricalData(const std::string& urlString, const std::string& apiKey);
```
</detail>

## Project structure

* `data/`: Contains the output data files.
* `docs/`: Contains the documentation files.
* `include/`: Contains the header files.
* `src/`: Contains the source files for the main application.
* `src/include/`: Contains internally used header files.
* `test/`: Contains the test files.
* `tool/`: Tools used, or offered, by the program.
* `CMakeLists.txt`: CMake configuration file.