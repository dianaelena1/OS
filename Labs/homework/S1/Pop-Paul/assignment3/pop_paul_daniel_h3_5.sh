#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi

    echo "Analyzing file: $file"
    line_number=0
    displayed_count=0

    while IFS= read -r line || [ -n "$line" ]; do
        line_number=$((line_number + 1))

        # Clean up Windows carriage return if present
        clean_line=$(echo "$line" | tr -d '\r')

        if [ "${#clean_line}" -gt 10 ]; then
            echo "$line_number: ${clean_line:10}"
            displayed_count=$((displayed_count + 1))
        fi
    done < "$file"

    echo "File '$file' had $displayed_count line(s) with more than 10 characters."
    echo "---------------------------------------------"
done
