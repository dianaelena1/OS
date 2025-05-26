#!/bin/bash

#Write a shell script which takes as parameters a few directory names. The script will display the names of all binary files in the given directories and their subdirectories.

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <dir1> [dir2 ... dirN]"
    exit 1
fi

for dir in "$@"; do
    if [ -d "$dir" ]; then
        find "$dir" -type f | while read -r file; do
            if file "$file" | grep -q 'executable\|ELF\|Mach-O\|PE32\|MS-DOS'; then
                echo "$file"
            fi
        done
    else
        echo "Warning: '$dir' is not a directory or does not exist."
    fi
done