#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

DIRECTORY="$1"

if [ ! -d "$DIRECTORY" ]; then
    echo "Error: '$DIRECTORY' is not a valid directory."
    exit 1
fi

echo "Displaying contents of text files in '$DIRECTORY' and its subdirectories:"
echo

find "$DIRECTORY" -type f | while read -r file; do
    if file "$file" | grep -q "text"; then
        echo "----- $file -----"
        cat "$file"
        echo
    fi
done
