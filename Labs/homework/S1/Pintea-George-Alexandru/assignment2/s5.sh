#!/bin/bash
#Write a shell script that takes as parameters several file names. The script will delete all words that contain atleast 1 digit from
#all given files.


if [ "$#" -lt 1 ]; then
	echo "Usage: $0 file1 [file2 ...]"
	exit 1
fi



for file in "$@";  do
	if [ -f "$file" ]; then
		sed -E 's/\b[[:alnum:]]*[0-9][[:alnum:]]*\b//g' "$file" > temp_file && mv temp_file "$file"
		echo "Processed $file"
	else
		echo "File not found"
	fi
done

