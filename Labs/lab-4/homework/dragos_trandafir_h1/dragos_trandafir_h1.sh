#!/bin/bash

#2 .Write a shell script which takes as parameters two names of text files. The script will compare the two text files line by line and #display the first 3 text lines that differ.

# file_path="file1.txt"
# cat ${file_path}
echo "Name of first file: $1"
echo "Name of second file: $2"

echo "First file is named $1"
echo "Second file is named $2"

file1=$1
file2=$2

cat "$file1" ; cat "$file2"

file1="$1"
file2="$2"
counter=3

exec 3< "$file2"  #open file2 with fil descriptor 3

while IFS= read -r line1 && IFS= read -r line2 <&3 && (($counter!=0)); do #while we read lines from both & we have lines to count
    if [[ -z "$line1" || -z "$line2" ]]; then
        echo "Empty line encountered. Stopping."  #stop when empty line
        break
    fi
    if [ "$line1" != "$line2" ]; then #only if 2 line are different decrase counetr
      echo "File1: $line1"
      echo "File2: $line2"
      counter=$(($counter-1))
    fi
done < "$file1"

exec 3<&-  #close file descriptor 3

# cd ./Labs/lab-4/homework/dragos_trandafir_h1
# sudo ./dragos_trandafir_h1.sh file1.txt file2.txt