#!/bin/bash

#Write a shell script which takes as parameters several file names. The script will display the number of files, the average number of words per #file and the total word count.

# check if at least 1 file is provided
if [ $# -lt 1 ]; then
  echo "Provide at least 1 file name!"
  exit 1
fi

echo "Nr of files is $#"
nrfiles=0
total_nr_words=0

# iterate through all files
for file in "$@"; do

  # check the file existence
  if [ ! -f "$file" ]; then
    echo "$file is not a valid file"
    continue
  fi

  #words=$(wc -w < "$file")

  #echo "$file has $words words"

  # Use awk to count words: sum up number of fields (NF) on each line
  words=$(awk '{ total = total + NF } END { print total+0 }' "$file") # +0 if no lines in files

  total_nr_words=$(($total_nr_words+$words))
  nrfiles=$(($nrfiles+1))

done

echo "Number of valid files is $nrfiles"
echo "Total nr of words is $total_nr_words"
echo "Avg number of words per file is $(($total_nr_words/$nrfiles))"

# cd ./Labs/homework/S2/Dragos-Trandafir/assignment3
# sudo ./dragos_trandafir_h3.sh file1.txt file2.txt