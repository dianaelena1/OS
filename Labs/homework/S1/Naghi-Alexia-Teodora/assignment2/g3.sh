#!/bin/bash

# Check if at least one directory is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 dir1 [dir2 ...]"
    exit 1
fi

for dir in "$@"; do
    if [ -d "$dir" ]; then
        find "$dir" -type f | while read -r file; do
            # Use the `file` command to check if the file is binary
            if file "$file" | grep -q "ELF"; then
                echo "Binary file: $file"
            fi
        done
    else
        echo "Directory not found: $dir"
    fi
done

