#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 filename word1 [word2 word3 ...]"
    exit 1
fi

filename="$1"

if [ ! -f "$filename" ]; then
    echo "Error: File '$filename' not found"
    exit 1
fi

shift

temp_file=$(mktemp)

# build sed command with all words to remove
# word1\|word2\|word3
sed_pattern=$(printf "%s\\|" "$@")
# remove the trailing \| and add word boundaries
sed_pattern="\b${sed_pattern%\\|}\b"

# remove all occurrences of the words and write to temp file
sed "s/$sed_pattern//g" "$filename" > "$temp_file"

# replace original file with modified content
mv "$temp_file" "$filename"

echo "Words removed from $filename"
