#Pb 11 - Given a list of files and a directory, print for each filename 
# all the subdirectories in which it appears, ordered decreasingly by the file size
# (a file can have the same name but different sizes in different subdirectories).


#!/bin/bash

if [ "$#" -lt 2 ]
then
  echo "Usage: $0 <directory> <file1> [file2 ...]"
  exit 1
fi

directory="$1"
shift

for filename in "$@"
do
  echo "File: $filename"

  find "$directory" -type f -name "$filename" 2>/dev/null | while read -r path
  do
    filesize=$(stat -c%s "$path")
    dirname=$(dirname "$path")
    echo "$filesize $dirname"
  done | sort -nr | while read -r filesize dirname
  do
    echo "$dirname (size: $filesize)"
  done

  echo "-------------------------------------------"
done