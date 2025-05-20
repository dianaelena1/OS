#!/bin/bash

#13-GREP
#Write a shell script which takes as parameters several file names.
#The script will display all the lines in the given files that don't contain any letter or digit.


if [ $# -eq 0 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi


for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File not found: $file"
        continue
    fi
    
    echo "Processing file: $file"
    grep -E "^[^a-zA-Z0-9]*$" "$file"
done
#grep searches for text in a file
# "^[^a-zA-Z0-9]*$" -expression matches any character that is not a letter or digit