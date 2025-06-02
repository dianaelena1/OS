#One or more directories are given, find all text files and display first 5 lines.

#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 directory_name"
    exit 1
fi

for directory in "$@"; do 
    if [! -d "$directory"]; then
    echo "Directory $directory not found! Skipping..."
        continue
    fi
    for file in $directory; do 
        if [-f $file] && ["$(file -b --type "$file")"="text"]; then
            head -n 5 "$file"
        fi
    done 
done



