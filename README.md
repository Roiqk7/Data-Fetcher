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

TODO

## Project structure

* `build/`: Contains the build files generated by CMake.
* `data/`: Contains the output data files.
* `docs/`: Contains the documentation files.
* `include/`: Contains the header files.
* `src/`: Contains the source files for the main application.
* `tests/`: Contains the test files.