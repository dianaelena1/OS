#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 filename word1 [word2 ... wordN]"
    exit 1
fi

file="$1"

if [ ! -f "$file" ]; then
    echo "Error: File '$file' not found."
    exit 2
fi

shift

temp_file=$(mktemp)

cp "$file" "$temp_file"

for word in "$@"; do
    sed -i "s/\b$word\b//g" "$temp_file"
done

mv "$temp_file" "$file"

echo "Words removed successfully."
