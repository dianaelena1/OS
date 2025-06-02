#Create a shell script that takes one or more directory paths as arguments
#For each valid directory provided, the script will find all text files (ending with .txt). For each .txt
#File found, the script will display its first 5 lines. If no arguments are provided, or if none
#Of the arguments are valid directories, the script should display an appropriate error message.
#!/bin/bash

if [ "$#" -eq 0 ]; then 
    echo "Please provide at least one directory"
    exit 1
fi

found_valid_dir=false

for dir in "$@"; do
    if [ -d "$dir" ]; then
        found_valid_dir=true
        echo "Searching in directory: $dir"

        find "$dir" -type f -name "*.txt" | while read -r file; do
            echo "-- $file --"
            head -n 5 "$file"
            echo
        done
    else
        echo "'$dir' is not a valid directory"
    fi
done

if ! $found_valid_dir; then
    echo "None of the provided paths are valid directories"
    exit 1
fi












