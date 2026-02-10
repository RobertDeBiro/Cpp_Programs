#!/bin/bash

# Configure CMake project
# This script sets up the build directory and generates build files

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"

echo "Configuring Iterator and Composite Patterns project..."
echo "Project root: $PROJECT_ROOT"
echo "Build directory: $BUILD_DIR"
echo ""

# Create build directory if it doesn't exist
mkdir -p "$BUILD_DIR"

# Run CMake configuration
cd "$BUILD_DIR" || exit 1
cmake -S "$PROJECT_ROOT" -B . -DCMAKE_BUILD_TYPE=Release

if [ $? -eq 0 ]; then
    echo ""
    echo "Configuration successful!"
    exit 0
else
    echo ""
    echo "Configuration failed!"
    exit 1
fi
