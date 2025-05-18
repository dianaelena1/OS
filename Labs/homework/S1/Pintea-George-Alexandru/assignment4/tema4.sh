#!/bin/bash
#Given a text file, write a Shell script that creates a directory containing 10 dictionary files
#corresponding to the 10 digits (0-9), and each file contains all the strings from the text file
#that start with that digit, each on a separate line, ordered alphabetically

if [ $# -ne 1 ]; then
	echo "Usage: $0 input_file.txt"
	exit 1
fi

INPUT_FILE="$1"

if [ ! -f "$INPUT_FILE" ]; then
	echo "File '$INPUT_FILE' does not exist."
	exit 1
fi


OUTPUT_DIR="digit_dictionaries"
mkdir -p "$OUTPUT_DIR"

for digit in {0..9}; do
	grep "^$digit" "$INPUT_FILE" | sort > "$OUTPUT_DIR/$digit.txt"
done

echo "Dictionary files created in '$OUTPUT_DIR' directory."
