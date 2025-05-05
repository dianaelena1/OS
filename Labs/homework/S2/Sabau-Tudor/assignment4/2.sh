#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_text_file>"
    exit 1
fi

input_file="$1"

# Check if input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found!"
    exit 1
fi

# Create output directory
output_dir="dictionary_files"
mkdir -p "$output_dir"

# Convert words to one-per-line, remove punctuation, convert to uppercase
tr -cs '[:alpha:]' '\n' < "$input_file" | tr '[:lower:]' '[:upper:]' | sort > temp_words.txt

# Clear any existing dictionary files
rm -f "$output_dir"/*

# Split into 26 files by first letter
for letter in {A..Z}; do
    grep "^$letter" temp_words.txt > "$output_dir/$letter.txt"
done

# Clean up temporary file
rm temp_words.txt

echo "Dictionary files created in '$output_dir/'"
