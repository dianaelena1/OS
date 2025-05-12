#!/bin/bash

if [ $# -eq 0 ];
then
   echo "Usage: $0 file1 [file2 ...]"
   exit 1
fi

for file in "$@"; do
    grep -v '[[:upper:]]' "$file"
done
