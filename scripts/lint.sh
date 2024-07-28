#!/bin/bash

# Define the path to the .clang-tidy file
config_file=".clang-tidy"

# Check if the .clang-tidy file exists
if [ ! -f "$config_file" ]; then
  echo "Error: .clang-tidy configuration file not found in the parent directory."
  exit 1
fi

# Define CFLAGS (this can be set or adjusted as needed)
CFLAGS="-std=c89 -Wall -Wextra -Werror -O3 -Isrc -fno-strict-aliasing -fno-wrapv"

# Find all .c and .h files in the src directory
files=$(find src -type f \( -name "*.c" -o -name "*.h" \))

# Check if any files were found
if [ -z "$files" ]; then
  echo "No .c or .h files found in the src directory."
  exit 0
fi

# Run clang-tidy on the found files
clang-tidy $files -- $CFLAGS

echo "clang-tidy analysis complete."
