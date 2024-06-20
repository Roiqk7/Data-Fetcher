#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Create a build directory if it doesn't exist
if [ ! -d "build" ]; then
        echo "Creating build directory..."
        mkdir build
fi

# Check if the current directory is not already 'build'
if [[ $(basename "$PWD") != "build" ]]; then
        echo "Moving to the build directory..."
        cd build
fi

echo "Configuring the project with CMake..."

# Configure the project with CMake
cmake ..

echo "Building the project..."

# Build the project
make

# Go back to the original directory only if we changed directories
if [[ $(basename "$PWD") == "build" ]]; then
        echo "Moving back to the original directory..."
        cd -
fi