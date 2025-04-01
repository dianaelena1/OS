#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Please provide at least one file name as a parameter."
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi

    lower_count=$(grep -o '[a-z]' "$file" | wc -l)
    upper_count=$(grep -o '[A-Z]' "$file" | wc -l)

    echo "$file l/U = $lower_count/$upper_count"
done
