#!/bin/bash

#Write a shell script which displays all files
# in the current directory and its subdirectories that
# have write permission for the group of which the owner belongs.

if [ -z "$1" ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi
# if [ $# -ne/-lt 0 ] ..

DIRECTORY="$1"

if [ ! -d "$DIRECTORY" ]; then
    echo "Error: '$DIRECTORY' is not a directory."
    exit 1
fi

find "$DIRECTORY" -type f -perm -020 | while read -r file; do
    echo "Writable file: $file"
done
