#Given a text file, write a Shell script that creates a directory which contains 26 dictionary-files, such that: the first file contains in alphabetical order all the words from the initial file that start with ‘A’, one word per line, the second file contains all words starting with ‘B’ and so on, each files contains all the world starting with that letter, each word on a new line, ordered alphabetically


#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_text_file>"
    exit 1
fi

input_file="$1"


if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found!"
    exit 1
fi


output_dir="dictionary_files"
mkdir -p "$output_dir"


tr -cs '[:alpha:]' '\n' < "$input_file" | tr '[:lower:]' '[:upper:]' | sort > temp_words.txt


rm -f "$output_dir"/*


for letter in {A..Z}; do
    grep "^$letter" temp_words.txt > "$output_dir/$letter.txt"
done


rm temp_words.txt

echo "Dictionary files created in '$output_dir/'"
