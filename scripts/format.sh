#!/bin/bash

# Check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "clang-format could not be found, please install it first."
    exit 1
fi

# Directory to scan
SRC_DIR="src"

# Find and format all .h and .c files in the src/ directory and subdirectories
find "$SRC_DIR" -type f \( -name "*.h" -o -name "*.c" \) -exec clang-format -i {} \;

echo "Formatting complete."
