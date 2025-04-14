#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <uppercase_letter> <file1> <file2> ..."
    exit 1
fi

uppercase_letter=$1

if [[ ! "$uppercase_letter" =~ [A-Z] ]]; then
    echo "Error: The first argument must be an uppercase letter."
    exit 1
fi

for file in "${@:2}"; do
    if [ ! -f "$file" ]; then
        echo "Error: File '$file' does not exist."
        continue
    fi

    temp_file=$(mktemp)

    echo "Processing file: $file"

    while IFS= read -r line; do
        modified_line=$(echo "$line" | sed "s/[a-z]/$uppercase_letter&/g")
        echo "$modified_line"
        echo "$modified_line" >> "$temp_file"
    done < "$file"

    mv "$temp_file" "$file"

    echo "File '$file' has been processed and updated."
done
