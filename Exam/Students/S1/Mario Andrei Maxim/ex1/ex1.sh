#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1, file2.."
    exit 1
fi 

for file in "$@"; do
    if [ ! -f "$file" ]; then 
        echo "File not found: $file"
        continue
    fi

    awk '{
        printf "%s", $1;
        for(i = 3; i <= NF; i++) {
            printf " %s", $i;
        }
        print "";
    }' "$file" > "file.tmp"
done