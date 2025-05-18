#!/bin/bash

# Check if at least 2 arguments are given (a word and at least one file)
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 word file1 [file2 ...]"
    exit 1
fi

word=$1
shift  # Remove the first argument so $@ contains only file names

for file in "$@"; do
    if [ -f "$file" ]; then
        # Use sed to delete lines containing the word in-place
        sed -i "/$word/d" "$file"
        echo "Processed: $file"
    else
        echo "File not found: $file"
    fi
done

