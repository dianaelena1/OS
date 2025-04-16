#!/bin/bash

# Write a shell script which takes as parameters several file names.
# The script will replace all lowercase vowels with corresponding
# uppercase letters in each line of the given files.

# sed -i 'y/aeiou/AEIOU/' input.txt

for file in "$@"; do
	while read line; do
		modified_line=$(echo "$line" | tr 'aeiou' 'AEIOU')
		echo "$modified_line" >> temp_file
	done < "$file"
	mv temp_file "$file"
done

