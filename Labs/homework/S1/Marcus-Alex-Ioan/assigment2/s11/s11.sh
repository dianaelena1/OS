#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <html_file>"
    exit 1
fi

INPUT_FILE="$1"

if [ ! -f "$INPUT_FILE" ]; then
    echo "File not found!"
    exit 1
fi

OUTPUT_FILE="${INPUT_FILE%.*}.txt"
sed 's/<[^>]*>//g' "$INPUT_FILE" > "$OUTPUT_FILE"
echo "Text file saved"
