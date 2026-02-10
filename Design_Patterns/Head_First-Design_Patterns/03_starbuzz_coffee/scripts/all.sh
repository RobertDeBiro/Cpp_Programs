#!/bin/bash

# Complete build and run script
# Combines configure, build, and run steps

echo "=========================================="
echo "  Decorator Pattern - Starbuzz Coffee"
echo "=========================================="
echo ""

# Step 1: Configure
echo "[1/3] Configuring CMake..."
./conf.sh
if [ $? -ne 0 ]; then
    echo "❌ Configuration failed!"
    exit 1
fi
echo "✅ Configuration successful"
echo ""

# Step 2: Build
echo "[2/3] Building project..."
./build.sh
if [ $? -ne 0 ]; then
    echo "❌ Build failed!"
    exit 1
fi
echo "✅ Build successful"
echo ""

# Step 3: Run
echo "[3/3] Running executable..."
echo "-------------------------------------------------------------------------------------------"
./run.sh
EXIT_CODE=$?
echo "-------------------------------------------------------------------------------------------"
echo ""

if [ $EXIT_CODE -eq 0 ]; then
    echo "✅ Execution successful"
else
    echo "❌ Execution failed with code $EXIT_CODE"
    exit $EXIT_CODE
fi

echo ""
echo "=========================================="
echo "  All steps completed successfully!"
echo "=========================================="
