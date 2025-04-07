#!/bin/bash
# WITH GREP 
# Write a shell script which takes as parameters a few directory names. 
# The script will display the names of all binary files in the given directories and their subdirectories.

# Check if at least one directory was provided
if [ "$#" -lt 1 ]; then
  echo "Usage: $0 dir1 [dir2 ...]"
  exit 1
fi

# Loop through each directory provided as argument
for dir in "$@"; do
  if [ -d "$dir" ]; then
    # Find all files, check each with 'file', and filter binary types
    find "$dir" -type f | while read -r file; do
      if file "$file" | grep -qE 'ELF|executable|binary'; then
        echo "$file"
      fi
    done
  else
    echo "Directory not found: $dir"
  fi
done
