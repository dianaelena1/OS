#!/bin/bash
#Write a shell script which takes as parameters a text followed by several file names. 
#The script will delete all the lines which contain the text given as parameter in all given files.
#to call it ./pop_paul_daniel_h2_s2.sh "text_to_remove" file1.txt file2.txt

# Check if at least two arguments are provided
if [ "$#" -lt 2 ]; then    #$# gives the number of arguments provided to the script.
    echo "Usage: $0 <text> <file1> [file2] ... [fileN]"
    exit 1
fi

# Extract the search text
TEXT="$1"
shift  # Shift arguments to the left, so $2 becomes $1, etc.

# Loop through all given files
for FILE in "$@"; do      #"$@" represents all remaining arguments (file names).
    if [ -f "$FILE" ]; then
        # Use sed to remove lines containing the text and overwrite the file
        sed -i "/$TEXT/d" "$FILE"
        echo "Processed: $FILE"
    else
        echo "File not found: $FILE"
    fi
done
