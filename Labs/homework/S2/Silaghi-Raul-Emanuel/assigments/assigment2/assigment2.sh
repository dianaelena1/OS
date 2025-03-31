#!/bin/bash

# Check if at least one file is provided
if [ "$#" -eq 0 ]; then
    echo "Usage: $0 file1 file2 ..."
    exit 1
fi

# Loop through all the provided files
for file in "$@"; do
    if [ -f "$file" ]; then
        echo "Processing file: $file"

        # Use grep to find lines containing only uppercase letters
        grep '^[A-Z ]*$' "$file"
    else
        echo "Error: $file is not a valid file."
    fi
done
