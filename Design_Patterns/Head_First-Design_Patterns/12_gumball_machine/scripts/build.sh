#!/bin/bash

#==============================================================================
# Project: Gumball Machine (State Pattern)
# Script: build.sh
# Description: Build the project using CMake
#==============================================================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"

echo "════════════════════════════════════════════════════════════════════════"
echo "  Building Project"
echo "════════════════════════════════════════════════════════════════════════"
echo ""
echo "Build Directory: $BUILD_DIR"
echo ""

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "✗ Build directory does not exist!"
    echo "  Please run conf.sh first to configure the build system."
    echo "════════════════════════════════════════════════════════════════════════"
    exit 1
fi

# Navigate to build directory
cd "$BUILD_DIR" || exit 1

echo "Running build..."
echo "────────────────────────────────────────────────────────────────────────"
cmake --build . --config Release

if [ $? -eq 0 ]; then
    echo "────────────────────────────────────────────────────────────────────────"
    echo "✓ Build successful!"
    echo "  Executable: $BUILD_DIR/GumballMachine"
    echo "════════════════════════════════════════════════════════════════════════"
    exit 0
else
    echo "────────────────────────────────────────────────────────────────────────"
    echo "✗ Build failed!"
    echo "════════════════════════════════════════════════════════════════════════"
    exit 1
fi
