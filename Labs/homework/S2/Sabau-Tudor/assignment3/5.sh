#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <file1> [file2] [...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "Error: File '$file' does not exist."
        continue
    fi

    line_number=0
    display_count=0

    while IFS= read -r line || [ -n "$line" ]; do  # <--- This OR fix is important
        line_number=$((line_number + 1))
        if [ ${#line} -gt 10 ]; then
            echo "Line $line_number: ${line:10}"
            display_count=$((display_count + 1))
        fi
    done < "$file"

    echo "Finished analyzing '$file'. Lines displayed: $display_count"
    echo "-------------------------------------------"
done
