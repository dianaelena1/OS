#!/bin/bash
#Write a shell script which takes as parameters a word followed by several file names. 
#The shell will display the names of the files containing the given word and the total number of these files.
# Check if at least two arguments are provided
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <word> <file1> [file2] ... [fileN]"
    exit 1
fi

# Extract the search words
WORD="$1"
shift  # Shift arguments to the left

# Counter for files containing the word
count=0

# Loop through all given files
for FILE in "$@"; do
    if [ -f "$FILE" ]; then
        if grep -q "$WORD" "$FILE"; then
            echo "Found in: $FILE"
            ((count++))
        fi
    else
        echo "File not found: $FILE"
    fi
done

echo "Total files containing '$WORD': $count"
