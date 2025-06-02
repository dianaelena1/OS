#!/bin/bash

# Check for at least one file
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        echo "In $file:"
        grep -x '^[0-9]*&' "$file"
        echo
    else
        echo "File not found: $file"
    fi
done
