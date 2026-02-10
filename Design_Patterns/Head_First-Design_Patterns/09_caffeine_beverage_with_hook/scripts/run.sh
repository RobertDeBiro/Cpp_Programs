#!/bin/bash

# Run the Template Method Pattern executable
# Executes the compiled program

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/out/build"
EXECUTABLE="$BUILD_DIR/caffeine_beverage_with_hook"

echo "Running Template Method Pattern - Caffeine Beverage with Hook..."
echo "Executable: $EXECUTABLE"
echo ""

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "✗ Executable does not exist. Run build.sh first."
    exit 1
fi

# Run the executable
"$EXECUTABLE"
EXIT_CODE=$?

echo ""
if [ $EXIT_CODE -eq 0 ]; then
    echo "✓ Execution completed successfully"
else
    echo "✗ Execution failed with exit code $EXIT_CODE"
fi

exit $EXIT_CODE
