#!/bin/bash

# Configure CMake project
# Creates build directory and generates build system

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"

echo "Configuring CMake project..."
echo "Project root: $PROJECT_ROOT"
echo "Build directory: $BUILD_DIR"

cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR"

if [ $? -eq 0 ]; then
    echo "✓ Configuration successful"
else
    echo "✗ Configuration failed"
    exit 1
fi
