# Data Fetcher

This code is part of Project Mencator. This particular module is responsible for gathering input data using the [FMP API](https://site.financialmodelingprep.com).

## Table of contents
- [Data Fetcher](#data-fetcher)
  - [Table of contents](#table-of-contents)
  - [Dependencies](#dependencies)
  - [Installation](#installation)
  - [Usage](#usage)
    - [Example usage](#example-usage)
  - [Project structure](#project-structure)

## Dependencies

* [C++17](https://en.cppreference.com/w/cpp/17)
* [CMake](https://cmake.org/)
* [CURL](https://curl.se/)
* [GTest](https://github.com/google/googletest)
* [JSON CPP](https://github.com/open-source-parsers/jsoncpp)
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

The usage is rather simple. User can run the application with the following command:

```bash
./main
```

The application has five major command line arguments:
* `--help`: Displays the help message.
* `--test`: Runs the tests.
* `--from`: Specifies the start date for the data fetching. (YYYY-MM-DD)
* `--to`: Specifies the end date for the data fetching. (YYYY-MM-DD)
* `--timeframe`: Specifies the timeframe for the data fetching. (1min, 5min, 15min, 30min, 1hour, 4hour, 1day)

If you want to rebuild the project, navigate to the project directory and run the following commands:

```bash
cd build &&
cmake .. &&
make
```

### Example usage

This command will display the help message:

```bash
./main --help
```

This command will run all the tests:

```bash
./main --tests
```

This command will fetch the data from 2023-08-10 to 2023-09-01 with a 4-hour timeframe and automatically save the data to data/data.json file.

```bash
./main --from=2023-08-10 --to=2023-09-01 --timeframe=4hour
```

**Note**: This application is only designed for fetching the SPY data. It is not designed to fetch any other data but can easily be modified to do so.

## Project structure

* `data/`: Contains the output data files.
* `docs/`: Contains the documentation files.
* `include/`: Contains the header files.
* `src/`: Contains the source files for the main application.
* `test/`: Contains the test files.
* `tool/`: Tools used, or offered, by the program.
* `CMakeLists.txt`: CMake configuration file.