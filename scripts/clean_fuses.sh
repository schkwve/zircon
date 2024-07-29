#!/bin/bash

# Used to delete open Filesystems in Userspace (FUSE) files

# Define the path where to search for .fuse_hidden* files
SEARCH_PATH="$PWD"

# Find and delete .fuse_hidden* files
find "$SEARCH_PATH" -name '.fuse_hidden*' -type f -delete
