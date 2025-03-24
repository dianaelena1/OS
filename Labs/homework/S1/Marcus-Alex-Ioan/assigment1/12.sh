#!/bin/bash



# Write a shell script which takes as parameter a directory name. 
# The script will display the filename, and the first 3 lines of 
# each ASCII text file found in that directory.


if [ -z "$1" ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

DIRECTORY="$1"

if [ ! -d "$DIRECTORY" ]; then
    echo "Error: '$DIRECTORY' is not a directory."
    exit 1
fi

find "$DIRECTORY" -type f | while read -r file; do
    if file "$file" | grep -q "ASCII text"; then
        echo -e "\nFile: $file"
        head -n 3 "$file"
    fi
done
