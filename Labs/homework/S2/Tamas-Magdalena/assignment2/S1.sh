#!/bin/bash

#Write a shell script which takes as parameters a file name followed by several words. The script will delete all occurrences of the words given as parameters in the given file

if [ "$#" -lt 2 ]; then
  echo "Usage: $0 <file> <word1> [word2] ... [wordN]"
  exit 1
fi


file="$1"

shift


for word in "$@"; do
  sed -i "s/\b$word\b//g" "$file"
done

echo "All occurrences of the specified words have been removed from the file."
