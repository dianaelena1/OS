#!/bin/bash
# write a shell script which takes as parameters several file names. For each given file, the script will display its name and the average nu,ber of words per line. At the end, the script will display also the average nmber of words per file

if [ $# -eq 0 ]; then
    echo "Usage: $0 file1 file2 file3 ..."
    exit 1
fi

total_words=0
total_files=0

for file in "$@"
do
    if [ -f "$file" ]; then
        lines=$(wc -l < "$file")
        words=$(wc -w < "$file")

        if [ "$lines" -eq 0 ]; then
            avg_words=0
        else
            avg_words=$(echo "scale=2; $words / $lines" | bc)
        fi

        echo "File: $file - Average words per line: $avg_words"

        total_words=$((total_words + words))
        total_files=$((total_files + 1))
    else
        echo "Warning: '$file' is not a valid file."
    fi
done

if [ "$total_files" -ne 0 ]; then
    avg_words_per_file=$(echo "scale=2; $total_words / $total_files" | bc)
    echo "Average number of words per file: $avg_words_per_file"
else
    echo "No valid files provided."
fi
