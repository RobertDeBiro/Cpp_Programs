#!/bin/bash

echo "========================================"
echo "  Running Singleton Pattern"
echo "========================================"
echo ""

cd "$(dirname "$0")/.." || exit 1

./out/build/singleton_pattern
