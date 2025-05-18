#!/bin/bash

# Write a shell script which takes as parameter a username (ex: bdae0198)
# The script will determine the section (extract the letters on
# positions 3 and 4) and the sum of all digits in the username.

input=$1

if [ $# -ne 1 ]
then
	echo "Error: wrong number of parameters!"
	exit 1
fi

sum=0

letters="${input:2:1}${input:3:1}"


for ((i=0; i<${#input}; ++i))
do
	char="${input:i:1}"
	if [[ "$char" =~ [0-9] ]]; then
		((sum+=char))
	fi
done

echo "The letters are: $letters"
echo "The sum of the digits in $input is $sum"

