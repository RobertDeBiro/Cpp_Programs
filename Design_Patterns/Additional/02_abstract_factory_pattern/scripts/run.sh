#!/bin/bash

echo "========================================"
echo "  Running Abstract Factory Pattern"
echo "========================================"
echo ""

cd "$(dirname "$0")/.." || exit 1

./out/build/abstract_factory_pattern
