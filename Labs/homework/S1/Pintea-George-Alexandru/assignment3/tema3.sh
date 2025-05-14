#!/bin/bash
#Write a shell scritp that takes as parameters several file names. For each given file, the script will
#display its name and the average number of words per line. At the end, the script will display also the
#average number of words per file.


if [ "$#" -lt 1 ]; then
	echo "Usage $0 file1, file2,..."
	exit 1 
fi

total_words=0
total_lines=0
file_count=0

for file in "$@"; do
	if [ ! -f "$file" ]; then
		echo "File '$file' does not exist."
		continue
	fi

	words=$(wc -w < "$file")
	lines=$(wc -l < "$file")

	if [ "$lines" -eq 0 ] ; then
		avg_words_per_line=0
	else
		avg_words_per_line=$(echo "scale=2; $words / $lines" | bc)
	fi

	echo "File: $file -Average words per line: $avg_words_per_line"

	total_words=$((total_words + words))
	total_lines=$((total_lines + lines))
	file_count=$((file_count + 1))

done

if [ "$file_count" -gt 0 ]; then
	avg_words_per_file=$(echo "scale=2; $total_words / $file_count" | bc)
	echo "Average words per file: $avg_words_per_file"
fi
