#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory_name> <filename_list>"
    exit 1
fi

directory_name=$1
filename_list=$2

if [ ! -d "$directory_name" ]; then
    echo "Error: Directory '$directory_name' does not exist."
    exit 1
fi

if [ ! -f "$filename_list" ]; then
    echo "Error: File '$filename_list' does not exist."
    exit 1
fi

if [ -z "$(ls -A "$directory_name")" ]; then
    echo "Error: Directory '$directory_name' is empty."
    exit 1
fi

subdirectories=$(find "$directory_name" -mindepth 1 -type d 2>/dev/null)

while IFS= read -r subdirectory; do
    echo "Searching in directory: $subdirectory"
    if [ ! -r "$subdirectory" ]; then
        echo "Warning: No read permission for directory '$subdirectory'"
        continue
    fi
    while IFS= read -r filename; do
        if [ -e "$subdirectory/$filename" ]; then
            echo "File '$filename' found in subdirectory '$subdirectory'"
        fi
    done < "$filename_list"
done <<< "$subdirectories"
