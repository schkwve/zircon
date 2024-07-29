#!/bin/bash

# Used to count the lines of code in the src/ directory

# Define the target directory (one level up from the scripts directory)
target_dir="$PWD"

# Check if the target directory exists
if [ ! -d "$target_dir" ]; then
  echo "Error: Directory '$target_dir' does not exist."
  exit 1
fi

# Run cloc on the target directory
cloc "$target_dir"

echo "cloc analysis complete."
