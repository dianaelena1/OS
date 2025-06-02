#!/bin/bash
if [ "$#" -eq 0 ]; then
    echo "Please input file names when using the script."
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        exit 1
    fi


done