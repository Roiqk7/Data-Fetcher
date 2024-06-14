# Specify the minimum version for CMake and the project's name
cmake_minimum_required(VERSION 3.10)
project(Fetcher)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include the project's headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the executables
add_executable(Main src/main.cpp src/parser.cpp tests/fetcher.cpp tests/tools.cpp)

# Include external libraries
# Find and include the Boost library (specify required components if necessary)
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(Main ${Boost_LIBRARIES})

# Find and include the CURL library
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(Main ${CURL_LIBRARIES})

# Find and include the Google Test package
find_package(GTest REQUIRED)
target_link_libraries(Main GTest::GTest GTest::Main)

# Find and include the Jsoncpp library
find_path(JSONCPP_INCLUDE_DIR json/json.h)
find_library(JSONCPP_LIBRARY jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIR})
target_link_libraries(Main ${JSONCPP_LIBRARY})

# Find and include the spdlog library
find_package(spdlog REQUIRED)
target_link_libraries(Main spdlog::spdlog)