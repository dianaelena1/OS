#!/bin/bash
#Write a shell script which takes as parameters several file names.
# For each given file, the script will display its name and the average number of words per line.
# At the end, the script will display also the average number of words per file.

# Check if at least one file is passed
if [ "$#" -lt 1 ]; then
  echo "Usage: $0 file1 [file2 ...]"
  exit 1
fi

total_words=0
file_count=0

for file in "$@"; do
  if [ -f "$file" ]; then
    result=$(awk '{ w += NF } END { print w, NR }' "$file")
    words=$(echo "$result" | cut -d' ' -f1)
    lines=$(echo "$result" | cut -d' ' -f2)

    if [ "$lines" -eq 0 ]; then
      avg_per_line=0
    else
      avg_per_line=$(awk -v w="$words" -v l="$lines" 'BEGIN { printf "%.2f", w/l }')
    fi

    echo "File: $file - Average words per line: $avg_per_line"

    total_words=$((total_words + words))
    file_count=$((file_count + 1))
  else
    echo "Warning: '$file' is not a valid file."
  fi
done

if [ "$file_count" -gt 0 ]; then
  avg_per_file=$(awk -v t="$total_words" -v f="$file_count" 'BEGIN { printf "%.2f", t/f }')
  echo "Average words per file: $avg_per_file"
else
  echo "No valid files were processed."
fi

