# Write a shell script which takes as parameters a lowercase letter followed by several file names. 
# The script will replace any special character with the given letter in all files given as parameters.

#!/bin/bash

# first arg is letter -> validate lowercase
letter=$1 

# == for exact string comparison, =~ for pattern matching with regular expr
if ! [[ $letter =~ [a-z] ]];then
	echo "The first argument should be a lowercase letter!"	
fi

for file in "${@:2}"; do
	# check if the files exist  -f
	if [ ! -f "$file" ]; then
		echo "File $file not found!"
	fi

	# replace all that are not a-z, A-Z, or digits  /g globally
	# -i to use file in-place
	sed -i "s/[^a-zA-Z0-9]/$letter/g" "$file"
done
