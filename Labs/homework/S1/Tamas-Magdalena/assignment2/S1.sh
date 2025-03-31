#!/bin/bash

#Write a shell script which takes as parameters a file name followed by several words. The script will delete all occurrences of the words given as parameters in the given file

# Check if at least two parameters are provided (filename and at least one word to delete)
if [ "$#" -lt 2 ]; then
  echo "Usage: $0 <file> <word1> [word2] ... [wordN]"
  exit 1
fi

# The first parameter is the file name
file="$1"

# Shift to get the words that need to be deleted
shift

# Loop through each word to delete
for word in "$@"; do
  # Use sed to delete occurrences of the word (case sensitive)
  # The \b in the pattern makes sure we only match whole words
  sed -i "s/\b$word\b//g" "$file"
done

echo "All occurrences of the specified words have been removed from the file."
