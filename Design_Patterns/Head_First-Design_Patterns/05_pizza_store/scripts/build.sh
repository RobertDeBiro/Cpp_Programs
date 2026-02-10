#!/bin/bash

# Build the project using make
# Assumes CMake has already been configured (run conf.sh first)

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"

if [ ! -d "$BUILD_DIR" ]; then
    echo "✗ Build directory not found. Run conf.sh first."
    exit 1
fi

echo "Building project..."
cd "$BUILD_DIR" || exit 1
make

if [ $? -eq 0 ]; then
    echo "✓ Build successful"
else
    echo "✗ Build failed"
    exit 1
fi
