# Write a shell script that takes a directory name as a parameter.
# The script will display the fileName and the first line of each ASCII text file found in that directory.


#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

dir="$1"

if [ ! -d "$dir" ]; then
    echo "Error: '$dir' is not a directory or does not exist."
    exit 1
fi

for file in "$dir"/*
do
    if [ -f "$file" ]
    then
        if file "$file" | grep -q "ASCII text"
        then
            echo "File: $(basename "$file")"
            head -n 1 "$file"
            echo "--------------------"
        fi
    fi
done
