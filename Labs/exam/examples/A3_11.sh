# Write a shell script which takes as parameters several file names. 
# The script will display the name of file which contains the highest number of words and the word count.
#!/bin/bash

if [ $# -eq 0 ]; then
        echo "No files provided!"
	exit 1
fi

max_word_count=0
max_word_file=""


for filename in "$@"; do
	if [ ! -f "$filename" ];then
		echo "File $filename not found!"
        fi

	# count the number of words in the current file
	# awk to print the number of fields (words) in each line of the file. NF =  the nr of fields (words) in the current line
	# word_count=$(awk {print NF} $filename

	# wc = count nr lines/ words    -w = count nr of words   < filename  = where to count

	word_count=$(wc -w < "$filename")

	if [ "$word_count" -gt "$max_word_count" ]; then
        	max_word_count="$word_count"
        	max_word_file="$filename"
	fi
done


echo "File with the highest word count is $max_word_file"
echo "Word Count is $max_word_count"
