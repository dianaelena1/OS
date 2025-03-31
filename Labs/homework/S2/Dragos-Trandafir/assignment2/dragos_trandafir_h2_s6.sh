#!/bin/bash

# S6.Write a shell script which takes as parameters a lowercase letter followed by several file names. The script will replace any special character # with the given letter in all files given as parameters.

#echo "Read lowercase letter"
#read lc_letter

if [ $# -le 2 ]; then
  echo "Number of arguments is invalid, input at least 2 parameters"
else

lc_letter=$1   
echo "$lc_letter"

for ((i=2; i<=$#; i++)); do 
  eval file=\$$i 
  sed -i "s/#/${lc_letter}/g" $file   
done
fi