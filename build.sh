#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Create a build directory and enter it
mkdir -p build
cd build

# Configure the project with CMake
cmake ..

# Build the project
make

# Go back to the original directory
cd -