#!/bin/bash

#Write a shell script which takes as parameters several file names.
#The script will display the lines containing the same word in consecutive positions in the given files.
#Each line will be prefixed with its number and the word involved

if [ $# -eq 0 ]; then
    echo "Usage: $0 file1 [file2 ... fileN]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File $file not found!"
        continue
    fi

    echo "Processing file: $file"

    awk '
    {
        line = $0
        for (i = 1; i <= NF - 1; i++) {
            if ($i == $(i+1)) {
                print "Line " NR ": [" $i "] " line
                next
            }
        }
    }
    ' "$file"

done

