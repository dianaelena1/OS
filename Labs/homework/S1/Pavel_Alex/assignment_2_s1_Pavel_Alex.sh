#!/bin/bash
# write a shell script which takes as parameters a file name followed by several words. The script will delete all occurences of the words given as parameters in the given file

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


sed_pattern=$(printf "%s\\|" "$@")
sed_pattern="\b${sed_pattern%\\|}\b"


sed "s/$sed_pattern//g" "$filename" > "$temp_file"


mv "$temp_file" "$filename"

echo "Words removed from $filename"
