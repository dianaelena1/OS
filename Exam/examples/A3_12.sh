#!/bin/bash

if [ "$#" -lt 3 ];
then
    echo "Usage: $0 <word_to_replace> <replacement_word> <file1> [<file2> ...]"
    exit 1
fi

word_to_replace=$1
replacement_word=$2
shift 2

for file in "$@"; do
    if [ ! -f "$file" ]; 
    then 
        echo "File '$file' not found. Skipping."
        continue
    fi

    sed  -i "s/$word_to_replace/$replacement_word/g" "$file"

    echo "Replaced occurrences of '$word_to_replace' with ' $replacement_word' in '$file'."
done
