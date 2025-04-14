#!/bin/bash
#Write a shell script which takes as parameters several file names.
#The script will delete the first 2 characters on each line in the given files.

# Check if at least one file is provided
if [ "$#" -lt 1 ]; then
  echo "Usage: $0 file1 [file2 ... fileN]"
  exit 1
fi

# Loop through all file arguments
for file in "$@"; do
  if [ -f "$file" ]; then
    sed -i '' 's/^..//' "$file"
    echo "Processed: $file"
  else
    echo "File not found: $file"
  fi
done


#Write a shell script which takes as parameters several file names.
# The script will display all the lines in the given files that don't contain any letter or digit.

# Check if at least one file is provided
if [ "$#" -lt 1 ]; then
  echo "Usage: $0 file1 [file2 ... fileN]"
  exit 1
fi

# Loop through all the given files
for file in "$@"; do
  if [ -f "$file" ]; then
    echo "Lines in $file without any letters or digits:"
    grep -Ev '[[:alnum:]]' "$file"
  else
    echo "File not found: $file"
  fi
done
