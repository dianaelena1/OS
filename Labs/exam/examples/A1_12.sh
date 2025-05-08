#!/bin/bash
# Write a shell script which takes as parameter a directory name. 
# The script will display the filename, and the first 3 lines of each ASCII text file found in that directory.

filepath="$1"
for file in "$filepath"/*; do
    if [ -f "$file" ] && [ "$(file -b --mime-type "$file")" = "text/plain" ]; then  #check if file and mime type text
        head -n 3 "$file"
        #display the first 3 lines
    fi
done
