#!/bin/bash

# Write a shell script which takes as parameters a word followed by several file names. The shell will delete all the lines containing the given word in all given files.

if [ $# -lt 2 ]; then
    echo "Error: Not enough arguments."
    echo "Usage: $0 word file1 [file2 ...]"
    exit 1
fi


search_word="$1"
shift
for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "Error: File '$file' does not exist or is not a regular file."
        continue
    fi
    
    if [ ! -r "$file" ] || [ ! -w "$file" ]; then
        echo "Error: Cannot access file '$file' for reading or writing."
        continue
    fi

    temp_file=$(mktemp)

    grep -v "\<$search_word\>" "$file" > "$temp_file"

    if [ $? -gt 1 ]; then
        echo "Error: Failed to process file '$file'."
        rm -f "$temp_file"
        continue
    fi

    cat "$temp_file" > "$file"
    rm -f "$temp_file"
    
    echo "Processed '$file'."
done

echo "All files processed."