# Data Fetcher

This code is part of Project Mencator. This particular module is responsible for gathering input data using the [FMP API](https://site.financialmodelingprep.com).

## Dependencies

* [C++17](https://en.cppreference.com/w/cpp/17)
* [CMake](https://cmake.org/)
* [CURL](https://curl.se/)
* [GTest](https://github.com/google/googletest)
* [JSON CPP](https://github.com/open-source-parsers/jsoncpp)
* [spdlog](https://github.com/gabime/spdlog)

Installing the dependencies on MacOS:

```bash
brew install cmake &&
brew install curl &&
brew install googletest &&
brew install jsoncpp &&
brew install spdlog
```

## Installation

After installing the dependencies and cloning the project, go into the project directory and run the following commands:

```bash
mkdir build &&
cd build &&
cmake .. &&
make
```

## Usage

TODO

## Project structure

* `build/`: Contains the build files generated by CMake.
* `docs/`: Contains the documentation files.
* `include/`: Contains the header files.
* `lib/`: Contains used libraries.
* `src/`: Contains the source files for the main application.
* `tests/`: Contains the test files.