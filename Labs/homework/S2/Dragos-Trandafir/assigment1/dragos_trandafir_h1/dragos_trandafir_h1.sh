#!/bin/bash

#2 .Write a shell script which takes as parameters two names of text files. The script will compare the two text files line by line and #display the first 3 text lines that differ.

echo "Name of first file: $1"
echo "Name of second file: $2"

file1="$1"
file2="$2"
counter=3

exec 3< "$file2"  

if [! -f $1 ] && [! -f $2 ]
  echo "files do not exist"
  exit 1

while IFS= read -r line1 && IFS= read -r line2 <&3 && (($counter!=0)); do 
    if [[ -z "$line1" || -z "$line2" ]]; then
        echo "Empty line encountered. Stopping."  
        break
    fi
    if [ "$line1" != "$line2" ]; then 
      echo "File1: $line1"
      echo "File2: $line2"
      counter=$(($counter-1))
    fi
done < "$file1"

exec 3<&-  

# cd ./Labs/lab-4/homework/dragos_trandafir_h1
# sudo ./dragos_trandafir_h1.sh file1.txt file2.txt