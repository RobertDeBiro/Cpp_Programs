#!/bin/bash

# Run the compiled executable
# Assumes project has been built (run build.sh first)

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"
EXECUTABLE="$BUILD_DIR/home_automation"

if [ ! -f "$EXECUTABLE" ]; then
    echo "✗ Executable not found. Run build.sh first."
    exit 1
fi

echo "Running home_automation..."
echo ""
"$EXECUTABLE"
