#Write a shell script which takes as parameters an uppercase letter followed by several file names. The script will add the given letter in the front of each lowercase on each line in all given files.



#!/bin/bash


if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <uppercase_letter> <file1> [file2 ...]"
    exit 1
fi

uppercase_letter="$1"
if [[ ! "$uppercase_letter" =~ ^[A-Z]$ ]]; then
    echo "Error: The first argument must be a single uppercase letter."
    exit 1
fi


shift


for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "Error: File '$file' does not exist."
        continue
    fi

   
    temp_file=$(mktemp)

   
    while IFS= read -r line; do
        
        modified_line=$(echo "$line" | sed "s/\([a-z]\)/$uppercase_letter\1/g")
        echo "$modified_line" >> "$temp_file"
    done < "$file"


    mv "$temp_file" "$file"
done

echo "Processing complete."