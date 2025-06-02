#!/bin/bash

#write a (IGNORE)  Shell program that, starting with the directory given as a first parameter, downwards (recursively), 
#creates a list of all names that appear (files and directory), and for each filename it prints the number of files with the same name

if [ -z "$1" ]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

if [ ! -d "$1" ]; then
  echo "Error: '$1' is not a directory."
  exit 2
fi

find "$1" -print0 | xargs -0 -n1 basename | sort | uniq -c | while read count name; do
  echo "$name: $count"
done
