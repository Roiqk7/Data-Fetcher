# Data Fetcher

This code is part of Project Mencator. This particular module is responsible for gathering input data using the [FMP API](https://site.financialmodelingprep.com).

## Dependencies

* [C++17](https://en.cppreference.com/w/cpp/17)
* [CMake](https://cmake.org/)
* [CURL](https://curl.se/)
* [GTest](https://github.com/google/googletest)
* [JSON CPP](https://github.com/open-source-parsers/jsoncpp)
* [spdlog](https://github.com/gabime/spdlog)

Installing the dependencies on MacOS using Homebrew:

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
git clone https://github.com/Roiqk7/Data-Fetcher/tree/main
```

Then, you can build the project:

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

as you would expect. The application has five major command line arguments:
* `--help`: Displays the help message.
* `--test`: Runs the tests.
* `--from`: Specifies the start date for the data fetching.
* `--to`: Specifies the end date for the data fetching.
* `timeframe`: Specifies the timeframe for the data fetching.

Example usage:

```bash
./main --tests
```

This command will run all the tests.

```bash
./main --from=2023-08-10 --to=2023-09-01 --timeframe=4hour
```

This command will fetch the data from 2023-08-10 to 2023-09-01 with a 4-hour timeframe and save the data to data/data.json file.

**Note**: This application is only designed for fetching the SPY data. It is not designed to fetch any other data but can easily be modified to do so.

## Project structure

* `build/`: Contains the build files generated by CMake.
* `data/`: Contains the output data files.
* `docs/`: Contains the documentation files.
* `include/`: Contains the header files.
* `src/`: Contains the source files for the main application.
* `tests/`: Contains the test files.