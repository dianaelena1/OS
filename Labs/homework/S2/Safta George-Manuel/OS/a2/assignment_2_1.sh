#!/bin/bash
# WITH SED 
# Write a shell script which takes as parameters a word followed by several file names. 
# The shell will delete all the lines containing the given word in all given files.

# Check if there are at least two arguments
if [ "$#" -lt 2 ]; then
  echo "Usage: $0 word file1 [file2 ...]"
  exit 1
fi

word=$1
shift # Shift all arguments to the left, so now $@ contains only the filenames

# Iterate through all file names
for file in "$@"
do
  if [ -f "$file" ]; then
    # Delete lines containing the word (in-place)
    sed -i "/$word/d" "$file"
    echo "The word \"$word\"  was deleted from: $file"

  else
    echo "File not found: $file"
  fi
done
