# Write a shell script which takes as parameters two names of text files. 
# The script will compare the two text files line by line and display the first 3 text lines that differ.

#!/bin/bash

# Check if correct number of arguments provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 file1 file2"
    exit 1
fi

file1="$1"
file2="$2"

# Check if files exist
if [ ! -e "$file1" ] || [ ! -e "$file2" ]; then
    echo "Error: One or both files do not exist."
    exit 1
fi

# Compare files line by line until the end of either file or 3 differences are found
line_num=1
count=0
while IFS= read -r line1 && IFS= read -r line2 <&3; do
    if [ "$line1" != "$line2" ]; then
        echo "Line $line_num:"
        echo "$file1: $line1"
        echo "$file2: $line2"
        count=$((count+1))
        if [ "$count" -eq 3 ]; then
            break
        fi
    fi
    line_num=$((line_num+1))
done < "$file1" 3< "$file2"

# Display message based on number of differences found
if [ "$count" -eq 0 ]; then
    echo "No differences found."
elif [ "$count" -eq 1 ]; then
    echo "Only one difference found."
elif [ "$count" -eq 2 ]; then
    echo "Only two differences found."
fi
