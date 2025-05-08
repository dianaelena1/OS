#!/bin/bash
# Write a shell script which displays all files in the current directory and its subdirectories that
# have write permission for the group of which the owner belongs.

check_permission() {
    file="$1"
    if [ -w "$file" ]; then
        echo "$file"
    fi
}

traverse_dir() {
    directory="$1"
    for item in "$directory"/*; do
        if [ -d "$item" ]; then
            traverse_dir "$item"
        elif [ -f "$item" ]; then
            check_permission "$item"
        fi
    done
}
traverse_dir "$(pwd)"
