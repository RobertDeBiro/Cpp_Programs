#!/bin/bash

#==============================================================================
# Project: Gumball Machine (State Pattern)
# Script: run.sh
# Description: Run the compiled executable
#==============================================================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"
EXECUTABLE="$BUILD_DIR/GumballMachine"

echo "════════════════════════════════════════════════════════════════════════"
echo "  Running Gumball Machine Demo"
echo "════════════════════════════════════════════════════════════════════════"
echo ""

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "✗ Executable not found: $EXECUTABLE"
    echo "  Please run build.sh first to build the project."
    echo "════════════════════════════════════════════════════════════════════════"
    exit 1
fi

# Run the executable
"$EXECUTABLE"

EXIT_CODE=$?

echo ""
echo "════════════════════════════════════════════════════════════════════════"
if [ $EXIT_CODE -eq 0 ]; then
    echo "✓ Program completed successfully!"
else
    echo "✗ Program exited with code: $EXIT_CODE"
fi
echo "════════════════════════════════════════════════════════════════════════"

exit $EXIT_CODE
