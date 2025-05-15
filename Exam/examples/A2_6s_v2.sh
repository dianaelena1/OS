# Write a shell script which takes as parameters a lowercase letter followed by several file names. 
# The script will replace any special character with the given letter in all files given as parameters.

#!/bin/bash

# Check if the number of arguments is less than 2
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <lowercase_letter> <file1> [<file2> ...]"
    exit 1
fi

# Extract the lowercase letter from the first argument
letter="$1"

# Check if the first argument is a lowercase letter
if ! [[ "$letter" =~ ^[a-z]$ ]]; then
    echo "Error: First argument must be a lowercase letter."
    exit 1
fi

# Check if the lowercase letter is not a single character
if [ ${#letter} -ne 1 ]; then
    echo "Error: First argument must be a single lowercase letter."
    exit 1
fi

# Check if the remaining arguments are files
for file in "${@:2}"; do
    if [ ! -f "$file" ]; then
        echo "Error: '$file' is not a file."
        exit 1
    fi
done

# Shift to skip the first argument (the letter)
shift

# Loop through each file provided as argument
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist. Skipping..."
        continue
    fi

    # Perform the replacement
    sed -i "s/[^a-zA-Z0-9]/$letter/g" "$file"
    echo "Replaced special characters with '$letter' in file '$file'."
done
