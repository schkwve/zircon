#!/bin/bash

# Dear Maintainers please run this script before committing if there are any open FUSEs

# Define the path where to search for .fuse_hidden* files
SEARCH_PATH="$PWD"

# Find and delete .fuse_hidden* files
find "$SEARCH_PATH" -name '.fuse_hidden*' -type f -delete
