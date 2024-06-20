#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Function to check if Homebrew is installed and install it if it's not
install_homebrew()
{
        if ! command -v brew >/dev/null 2>&1; then
                echo "Homebrew not found. Installing Homebrew..."
                /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        else
                echo "Homebrew is already installed."
        fi
}

# Function to install dependencies using Homebrew
install_dependencies()
{
        echo "Installing dependencies..."
        brew install cmake curl googletest jsoncpp spdlog
}

# Detect operating system using uname
OS=$(uname -s)

if [ "$OS" = "Darwin" ]; then
        # Install Homebrew if it's not installed
        install_homebrew

        # Install dependencies
        install_dependencies
else
        echo "[Error] This script is intended for macOS users. For Linux or other Unix-like systems, please install the dependencies using your package manager."
fi