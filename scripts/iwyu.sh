#!/bin/bash

# Define CFLAGS (this can be set or adjusted as needed)
CFLAGS="-std=c89 -Wall -Wextra -Werror -O3 -Isrc -fno-strict-aliasing -fno-wrapv"

# Find all .c files in the src directory
files=$(find src -type f -name "*.c")

# Check if any files were found
if [ -z "$files" ]; then
  echo "No .c files found in the src directory."
  exit 0
fi

# Run include-what-you-use on each found file
for file in $files; do
  include-what-you-use $CFLAGS "$file"
done

echo "include-what-you-use analysis complete."
