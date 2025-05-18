#!/bin/bash

# Check for at least one file
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        echo "In $file:"
        # Print lines that contain only uppercase letters (and optional spaces)
        grep -x '^[A-Z ]*$' "$file"
        echo
    else
        echo "File not found: $file"
    fi
done

