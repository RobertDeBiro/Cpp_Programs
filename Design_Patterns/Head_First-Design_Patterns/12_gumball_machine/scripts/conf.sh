#!/bin/bash

#==============================================================================
# Project: Gumball Machine (State Pattern)
# Script: conf.sh
# Description: Configure CMake build system
#==============================================================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"

echo "════════════════════════════════════════════════════════════════════════"
echo "  Configuring CMake Build System"
echo "════════════════════════════════════════════════════════════════════════"
echo ""
echo "Project Root: $PROJECT_ROOT"
echo "Build Directory: $BUILD_DIR"
echo ""

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

# Navigate to build directory and run CMake
cd "$BUILD_DIR" || exit 1

echo "Running CMake configuration..."
echo "────────────────────────────────────────────────────────────────────────"
cmake -S "$PROJECT_ROOT" -B . -DCMAKE_BUILD_TYPE=Release

if [ $? -eq 0 ]; then
    echo "────────────────────────────────────────────────────────────────────────"
    echo "✓ CMake configuration successful!"
    echo "════════════════════════════════════════════════════════════════════════"
    exit 0
else
    echo "────────────────────────────────────────────────────────────────────────"
    echo "✗ CMake configuration failed!"
    echo "════════════════════════════════════════════════════════════════════════"
    exit 1
fi
