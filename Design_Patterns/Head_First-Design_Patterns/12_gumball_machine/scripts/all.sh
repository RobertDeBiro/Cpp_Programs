#!/bin/bash

#==============================================================================
# Project: Gumball Machine (State Pattern)
# Script: all.sh
# Description: Run complete build pipeline (configure, build, run)
#==============================================================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo ""
echo "╔════════════════════════════════════════════════════════════════════════╗"
echo "║                                                                        ║"
echo "║             GUMBALL MACHINE - STATE PATTERN BUILD PIPELINE            ║"
echo "║                                                                        ║"
echo "╚════════════════════════════════════════════════════════════════════════╝"
echo ""

# Step 1: Configure
echo "STEP 1/3: CONFIGURE"
"$SCRIPT_DIR/conf.sh"
CONF_RESULT=$?

if [ $CONF_RESULT -ne 0 ]; then
    echo ""
    echo "╔════════════════════════════════════════════════════════════════════════╗"
    echo "║  ✗ PIPELINE FAILED AT CONFIGURATION STAGE                             ║"
    echo "╚════════════════════════════════════════════════════════════════════════╝"
    echo ""
    exit 1
fi

echo ""

# Step 2: Build
echo "STEP 2/3: BUILD"
"$SCRIPT_DIR/build.sh"
BUILD_RESULT=$?

if [ $BUILD_RESULT -ne 0 ]; then
    echo ""
    echo "╔════════════════════════════════════════════════════════════════════════╗"
    echo "║  ✗ PIPELINE FAILED AT BUILD STAGE                                     ║"
    echo "╚════════════════════════════════════════════════════════════════════════╝"
    echo ""
    exit 1
fi

echo ""

# Step 3: Run
echo "STEP 3/3: RUN"
"$SCRIPT_DIR/run.sh"
RUN_RESULT=$?

echo ""

# Final status
if [ $RUN_RESULT -eq 0 ]; then
    echo "╔════════════════════════════════════════════════════════════════════════╗"
    echo "║                                                                        ║"
    echo "║  ✓✓✓ ALL STAGES COMPLETED SUCCESSFULLY ✓✓✓                            ║"
    echo "║                                                                        ║"
    echo "║  Pipeline Status:                                                      ║"
    echo "║    • Configure ✓                                                       ║"
    echo "║    • Build     ✓                                                       ║"
    echo "║    • Run       ✓                                                       ║"
    echo "║                                                                        ║"
    echo "╚════════════════════════════════════════════════════════════════════════╝"
    echo ""
    exit 0
else
    echo "╔════════════════════════════════════════════════════════════════════════╗"
    echo "║  ✗ PIPELINE FAILED AT RUN STAGE                                       ║"
    echo "╚════════════════════════════════════════════════════════════════════════╝"
    echo ""
    exit 1
fi
