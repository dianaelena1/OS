#!/bin/bash

# Check if at least one filename is given
if [ "$#" -eq 0 ]; then
  echo "Usage: $0 filename1 [filename2 ...]"
  exit 1
fi

# Process each file passed as argument
for file in "$@"; do
  echo "Processing file: $file"

  # Validate: check if file exists and is readable
  if [ ! -f "$file" ]; then
    echo "Error: '$file' does not exist or is not a regular file."
    continue
  fi

  if [ ! -r "$file" ]; then
    echo "Error: '$file' is not readable."
    continue
  fi

  # Get the first line
  first_line=$(head -n 1 "$file")

  # Count words in the first line
  word_count=$(echo "$first_line" | wc -w)

  # Get file size in bytes
  file_size=$(wc -c < "$file")

  echo "First line word count: $word_count"
  echo "File size (bytes): $file_size"
  echo "----------------------------"
done
