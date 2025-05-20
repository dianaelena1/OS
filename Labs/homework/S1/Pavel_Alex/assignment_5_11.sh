#!/bin/bash
# Write a shell script which takes as parameters several file names. The script will display the name of the file which contains the highest number of words and the word count.

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <file1> [file2 ... fileN]"
    exit 1
fi

max_words=0
max_file=""

for file in "$@"; do
    if [ -f "$file" ]; then
        count=$(wc -w < "$file")
        if [ "$count" -gt "$max_words" ]; then
            max_words=$count
            max_file=$file
        fi
    else
        echo "Warning: '$file' is not a file or does not exist."
    fi
done

if [ -n "$max_file" ]; then
    echo "File with the most words: $max_file ($max_words words)"
else
    echo "No valid files provided."
fi