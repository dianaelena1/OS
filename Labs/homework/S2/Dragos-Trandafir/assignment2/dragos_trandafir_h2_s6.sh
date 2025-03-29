#!/bin/bash

# S6.Write a shell script which takes as parameters a lowercase letter followed by several file names. 
# The script will replace any special character # with the given letter in all files given as parameters.

#echo "Read lowercase letter"
#read lc_letter

if [ $# -le 1 ]; then
  echo "Number of arguments is invalid, input at least 2 parameters"
else

lc_letter=$1   # first parameter (the letter)
echo "$lc_letter"

for ((i=2; i<=$#; i++)); do # do this for all the files
  eval file=\$$i # use escape character \ and eval to actually compute the expression
  sed -i "s/#/${lc_letter}/g" $file   # replace globally # with the lower case letter
done
fi