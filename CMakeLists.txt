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

# Create a library for the core functionality
add_library(FetcherLib
        src/dataFetcher.cpp
        src/fetcher.cpp
        src/flowControl.cpp
        src/inputHandler.cpp
        tool/tools.cpp
)

# Make the FetcherLib headers available to other projects
target_include_directories(FetcherLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the executable main.cpp
add_executable(Main main.cpp)

# Link the FetcherLib library with the Main executable
target_link_libraries(Main FetcherLib)

# Include external libraries
# Find and include the CURL library
find_package(CURL REQUIRED)
target_include_directories(FetcherLib PUBLIC ${CURL_INCLUDE_DIR})
target_link_libraries(FetcherLib ${CURL_LIBRARIES})

# Find and include the Google test library
find_package(GTest REQUIRED)
target_include_directories(FetcherLib PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(FetcherLib GTest::GTest GTest::Main)

# Find and include the Jsoncpp library
find_path(JSONCPP_INCLUDE_DIR json/json.h)
find_library(JSONCPP_LIBRARY jsoncpp)
target_include_directories(FetcherLib PUBLIC ${JSONCPP_INCLUDE_DIR})
target_link_libraries(FetcherLib ${JSONCPP_LIBRARY})

# Find and include the spdlog library
find_package(spdlog REQUIRED)
target_link_libraries(FetcherLib spdlog::spdlog)

# Option to enable or disable building of tests
option(BUILD_TESTS "Build the tests" ON)

if(BUILD_TESTS)
        # Find and include the Google Test package
        find_package(GTest REQUIRED)
        include_directories(${GTEST_INCLUDE_DIRS})

        # Create a test executable
        add_executable(FetcherTests
                test/dataFetcher.cpp
                test/fetcher.cpp
                test/inputHandler.cpp
                test/tools.cpp
        )

        # Link FetcherTests with GTest and FetcherLib
        target_link_libraries(FetcherTests GTest::GTest GTest::Main FetcherLib)
endif()