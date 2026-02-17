#!/bin/bash

echo "========================================"
echo "  Building Singleton Pattern"
echo "========================================"

cd "$(dirname "$0")/.." || exit 1

cmake --build out/build

echo ""
echo "Build complete!"
