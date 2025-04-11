#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 file1 file2 ..."
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        echo "Processing file: $file"

        grep '^[A-Z ]*$' "$file"
    else
        echo "Error: $file is not a valid file."
    fi
done
