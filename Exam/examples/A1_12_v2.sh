#!/bin/bash
# Write a shell script which takes as parameter a directory name. 
# The script will display the filename, and the first 3 lines of each ASCII text file found in that directory.

if [ $# -ne 1 ]; then
    echo "Usage: $0 directory_name"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "$1 is not a directory"
    exit 1
fi

for file in "$1"/*; 
do
    if [ -f "$file" ] && [ "$(file -b --mime-type "$file")" = "text/plain" ]; then
        echo "Filename: $file"
        head -n 3 "$file"
        echo
    fi
done
