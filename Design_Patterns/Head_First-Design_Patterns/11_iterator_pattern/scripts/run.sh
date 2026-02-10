#!/bin/bash

# Run the executable
# This script runs the compiled program

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"
EXECUTABLE="$BUILD_DIR/IteratorAndComposite"

echo "Running Iterator and Composite Patterns demonstration..."
echo ""

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found. Build the project first."
    exit 1
fi

# Run the executable
"$EXECUTABLE"

if [ $? -eq 0 ]; then
    echo ""
    echo "Execution completed successfully!"
    exit 0
else
    echo ""
    echo "Execution failed!"
    exit 1
fi
