#!/bin/bash

# Handle the case when no file is provided
if [ "$#" -eq 0 ]; then
    echo "Please enter at least one file."
    exit 1
fi

# Iterate through each file provided as argument
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "$file does not exist."
        continue
    fi

    awk '
         BEGIN {lower = 0; upper = 0}
         {
       	# $0 - current line
          for ( i = 1; i <= length($0); i++) {
		char = substr($0, i , 1) # saving each character
		if(char ~ /[a-z]/) lower++; #check if char is L/U case
		if(char ~ /[A-Z]/) upper++;
	  }
	}
	END {ratio = (lower "/" upper)
	print FILENAME " l/U = " ratio }' $file
done
