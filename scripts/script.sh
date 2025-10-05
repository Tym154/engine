#!/bin/bash
set -e 

# Resolve project root (this script lives in renderer/scripts/)
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
EXECUTABLE="$BUILD_DIR/3D_renderer"

BUILD_TYPE=${1:-Debug}

echo "=== Building ($BUILD_TYPE) ==="

# Ensure build directory exists
mkdir -p "$BUILD_DIR"

# Run CMake configure step (generates Makefiles)
cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=$BUILD_TYPE

# Build with maximum parallel jobs
cmake --build "$BUILD_DIR" -- -j$(nproc)

# Run the executable if it exists
if [ -f "$EXECUTABLE" ]; then
    echo "=== Running 3D_renderer ==="
    "$EXECUTABLE"
else
    echo "Error: Executable not found in $EXECUTABLE"
    exit 1
fi
