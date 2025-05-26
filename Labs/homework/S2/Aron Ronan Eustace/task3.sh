#!/bin/bash


#Write a shell script which takes as parameters two words followed by several file names. The script will replace any occurrence of the first word with the second word in each line of the given files.

if [ "$#" -lt 3 ]; then
  echo "Usage: $0 old_word new_word file1 [file2 …]"
  exit 1
fi

old="$1"
new="$2"
shift 2

for file in "$@"; do
  if [ ! -f "$file" ]; then
    echo "No such file: $file"
    exit 1
  fi

  awk -v o="$old" -v n="$new" '{ gsub(o, n); print }' "$file" > tmp && mv tmp "$file"
done

