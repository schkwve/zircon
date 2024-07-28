#!/bin/bash

# Define the path to the .clang-format file
config_file=".clang-format"

# Check if the .clang-format file exists
if [ ! -f "$config_file" ]; then
  echo "Error: .clang-format configuration file not found in the parent directory."
  exit 1
fi

# Find all .c and .h files in the src directory
files=$(find src -type f \( -name "*.c" -o -name "*.h" \))

# Check if any files were found
if [ -z "$files" ]; then
  echo "No .c or .h files found in the src directory."
  exit 0
fi

# Apply clang-format to each file using the specified configuration file
for file in $files; do
  clang-format -i -style=file -fallback-style=none -config="$config_file" "$file"
done

echo "Formatting complete."
