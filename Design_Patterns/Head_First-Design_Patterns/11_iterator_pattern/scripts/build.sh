#!/bin/bash

# Build the project
# This script compiles the source code

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"

echo "Building Iterator and Composite Patterns project..."
echo "Build directory: $BUILD_DIR"
echo ""

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: Build directory does not exist. Run conf.sh first."
    exit 1
fi

# Build the project
cd "$BUILD_DIR" || exit 1
make

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful!"
    exit 0
else
    echo ""
    echo "Build failed!"
    exit 1
fi
