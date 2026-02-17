#!/bin/bash

echo "========================================"
echo "  Configuring Abstract Factory Pattern"
echo "========================================"

cd "$(dirname "$0")/.." || exit 1

cmake -S . -B out/build -DCMAKE_BUILD_TYPE=Release

echo ""
echo "Configuration complete!"
