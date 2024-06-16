# Specify the minimum version for CMake and the project's name
cmake_minimum_required(VERSION 3.10)
project(Fetcher)

# Target the Apple Silicon architecture
if(NOT CMAKE_OSX_ARCHITECTURES)
        set(CMAKE_OSX_ARCHITECTURES arm64)
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include the project's headers
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Create a library for the core functionality
add_library(FetcherLib
        src/dataFetcher.cpp
        src/fetcher.cpp
        src/flowControl.cpp
        src/inputHandler.cpp
        tool/tools.cpp
)

# Create a library for the tests
add_library(FetcherTests
        test/fetcher.cpp
        test/tools.cpp
)

# Add the executable which is main.cpp only
add_executable(Main main.cpp)

# Link the FetcherLib library with the Main executable
target_link_libraries(Main FetcherLib FetcherTests)

# Include external libraries
# Find and include the CURL library
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(FetcherLib ${CURL_LIBRARIES})

# Find and include the Google Test package
find_package(GTest REQUIRED)
target_link_libraries(FetcherTests GTest::GTest GTest::Main)

# Find and include the Jsoncpp library
find_path(JSONCPP_INCLUDE_DIR json/json.h)
find_library(JSONCPP_LIBRARY jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIR})
target_link_libraries(FetcherLib ${JSONCPP_LIBRARY})

# Find and include the spdlog library
find_package(spdlog REQUIRED)
target_link_libraries(FetcherLib spdlog::spdlog)