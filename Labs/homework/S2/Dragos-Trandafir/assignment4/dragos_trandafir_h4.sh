#!/bin/bash

#13.Given a text file, write a Shell script that creates a directory containing 10 dictionary files corresponding to the 10 digits (0-9), and each file contains all the strings from the text file that start with that digit, each on a separate line, ordered alphabetically.  

if [ $# -ne 1 ]; then
  echo "input a text file"
  exit 1
fi
# cd ./Labs/homework/S2/Dragos-Trandafir/assignment4
# ./dragos_trandafir_h4.sh file1.txt 

if [ ! -f "$1" ]; then
  echo "inputed text file does not exist"
  exit 1
fi



# mkdir digit_files

for digit in {0..9}; do
  grep -o "\b$digit\w*" "$1" | sort > "digit_files/file$digit.txt" 
done

