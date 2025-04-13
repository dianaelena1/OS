#!/bin/bash

# Check if at least 2 arguments are passed (text + one file)
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 \"text to insert\" file1 [file2 ...]"
    exit 1
fi

text="$1"   # The text to insert
shift       # Remaining arguments are file names

for file in "$@"; do
    if [ -f "$file" ]; then
        # Insert the text after the first line using sed
        sed -i "1a$text" "$file"
        echo "Inserted text into $file"
    else
        echo "File not found: $file"
    fi
done

