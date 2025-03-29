#13-GREP
#Write a shell script which takes as parameters several file names. 
#The script will delete the first 2 characters on each line in the given files.


#!/bin/bash

#check if at least one file is provided
if [ $# -eq 0 ]; then   #eq- checks if equivalent
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

#loop through all provided files
for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File not found: $file"
        continue
    fi
    
    echo "Processing file: $file"
    sed 's/^..//' "$file"
done
#sed-processes text in a file
#^- start of each line
#..-matches first two characters of a line
#//-replaces the two characters with nothing