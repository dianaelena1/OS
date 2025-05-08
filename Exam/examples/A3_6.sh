#!/bin/bash

# Function to calculate average number of words per line in a file
average_words_per_line() {
    local file="$1"
    local total_lines=$(wc -l < "$file")
    local total_words=$(wc -w < "$file")
    if [ "$total_lines" -gt 0 ]; then
        echo "Average words per line in $file: $((total_words / total_lines))"
    else
        echo "File $file is empty."
    fi
}

# Initialize variables for total words and total files
total_words=0
total_files=0

# Iterate over each file passed as parameter
for file in "$@"; do
    if [ -f "$file" ]; then
        average_words_per_line "$file"
        total_words_in_file=$(wc -w < "$file")
        total_words=$((total_words + total_words_in_file))
        total_files=$((total_files + 1))
    else
        echo "File $file not found."
    fi
done

# Calculate and display average number of words per file
if [ "$total_files" -gt 0 ]; then
    echo "Average number of words per file: $((total_words / total_files))"
else
    echo "No valid files provided."
fi
