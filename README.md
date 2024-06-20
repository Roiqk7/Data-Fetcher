# Data Fetcher

This code is part of Project Mencator. This particular module is responsible for gathering input data using the [FMP](https://site.financialmodelingprep.com) and [Polygon.io](https://polygon.io). Keep in mind that this project is intended for MacOS users. If you would like to implement this project to a different operating system, feel free to fork the repository and make the necessary changes.

## Table of contents
- [Data Fetcher](#data-fetcher)
  - [Table of contents](#table-of-contents)
  - [Dependencies](#dependencies)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Project structure](#project-structure)

## Dependencies

* [C++17](https://en.cppreference.com/w/cpp/17)
* [Homebrew](https://brew.sh/)
* [CMake](https://cmake.org/)
* [CURL](https://curl.se/)
* [GTest](https://github.com/google/googletest)
* [Json Cpp](https://github.com/open-source-parsers/jsoncpp)
* [spdlog](https://github.com/gabime/spdlog)

The dependencies can be installed using `dependencies.sh` which is located in the root directory of the project. You can run the script by executing the following command:

```bash
./dependencies.sh
```

<details>
<summary>zsh: permission denied: ./dependencies.sh</summary>

To fix this error run:

```bash
chmod +x dependencies.sh
```

This will make the file executable. Now you can run the file and install all the dependencies.

</details>

## Installation

First, clone the repository:

```bash
git clone https://github.com/Roiqk7/Data-Fetcher.git
```

Afterwards navigate to the project directory:

```bash
cd Data-Fetcher
```

Then install the dependencies by running the `dependencies.sh` file:

```bash
./dependencies.sh
```

<details>
<summary>zsh: permission denied: ./dependencies.sh</summary>

To fix this error run:

```bash
chmod +x dependencies.sh
```

This will make the file executable. Now you can run the file and install all the dependencies.

</details>

Now you can build the project by executing the `build.sh` file:

```bash
./build.sh
```

<details>
<summary>zsh: permission denied: ./build.sh</summary>

```bash
chmod +x build.sh
```

This will make the file executable. Now you can run the file and build the project.

</details>

**Note:** You do not have to build the project if you only want to use it as a library. Building the project is only necessary if you want to run the tests or want to contribute. In order for the tests to run, you need to add your API keys into `src/include/constants.h`.

## Usage

Include the library in your C++ project by including the header file:

```cpp
#include <dataFetcher/dataFetcher.h>
```

Then, you can use the functions provided by the library:

<details>
<summary>Declarations</summary>

```cpp
Json::Value fetchHistoricalData(const std::string& tickerSymbol, const std::string& fromDate, const std::string& toDate,
                const std::string& timeFrame, const std::string& api, const std::string& apiKey);
Json::Value fetchHistoricalData(const std::string& urlString);
Json::Value fetchHistoricalData(const std::string& urlString, const std::string& apiKey);
```
</details>

These functions will allow you, the user, to fetch historical data of a given stock/etf in a given period of time with a desired time frame. The programme supports the [FMP](https://site.financialmodelingprep.com) and [Polygon.io](https://polygon.io) APIs. The function will return a `Json::Value` object that contains the fetched data. Browse the [documentation](https://github.com/Roiqk7/Data-Fetcher/tree/main/docs) for more information.

If you need to run the tests, you can do so by running the following command:

```bash
./FetcherTests
```

## Project structure

* `data/`: Contains the output data files.
* `docs/`: Contains the documentation files.
* `include/`: Contains the header files.
* `src/`: Contains the source files for the main application.
* `src/include/`: Contains internally used header files.
* `test/`: Contains the test files.
* `test/data/`: Contains files used for testing.
* `tool/`: Tools used, or offered, by the program.
* `CMakeLists.txt`: CMake configuration file.