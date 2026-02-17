#!/bin/bash

echo "========================================"
echo "  Building Abstract Factory Pattern"
echo "========================================"

cd "$(dirname "$0")/.." || exit 1

cmake --build out/build

echo ""
echo "Build complete!"
