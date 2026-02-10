#!/bin/bash

# Build the Template Method Pattern project
# Compiles the source code using the generated build files

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"

echo "Building Template Method Pattern - Caffeine Beverage with Hook..."
echo "Build directory: $BUILD_DIR"

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "✗ Build directory does not exist. Run conf.sh first."
    exit 1
fi

# Build the project
cd "$BUILD_DIR" || exit 1
cmake --build . --config Release

if [ $? -eq 0 ]; then
    echo "✓ Build successful"
    exit 0
else
    echo "✗ Build failed"
    exit 1
fi
