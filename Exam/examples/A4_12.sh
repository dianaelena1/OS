#!/bin/bash

# Check if directory exists
if [ -d "$1" ]; then
    for file in $(find "$1" -type d); do
        echo "Directory: $file"
    done
    # List all files in directory and its subdirectories
    for file in $(find "$1" -type f); do
        echo "File: $file"
        # Print the maximum number of repeating lines
        sort "$file" | uniq -c | sort -nr | head -n 1
    done

else
    echo "Directory does not exist."
fi