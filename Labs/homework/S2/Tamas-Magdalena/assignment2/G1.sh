#!/bin/bash

#Write a shell script which takes as parameter a directory name. The script will display the content of all text files in the given directory and its subdirectories.

if [ -z "$1" ]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

dir="$1"


if [ ! -d "$dir" ]; then
  echo "The provided directory does not exist."
  exit 1
fi

grep -rl --include="*.txt" "" "$dir" | while read file; do
  echo "Displaying content of: $file"
  grep "" "$file"
  echo "======================================="
done

