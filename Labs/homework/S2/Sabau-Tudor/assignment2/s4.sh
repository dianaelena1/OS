#!/bin/bash

# Check if at least two arguments are provided
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <uppercase_letter> <file1> [file2 ...]"
    exit 1
fi

# Extract the uppercase letter and validate it
uppercase_letter="$1"
if [[ ! "$uppercase_letter" =~ ^[A-Z]$ ]]; then
    echo "Error: The first argument must be a single uppercase letter."
    exit 1
fi

# Shift to process the file arguments
shift

# Loop through each file
for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "Error: File '$file' does not exist."
        continue
    fi

    # Create a temporary file to store the modified content
    temp_file=$(mktemp)

    # Process each line in the file
    while IFS= read -r line; do
        # Add the uppercase letter before each lowercase letter
        modified_line=$(echo "$line" | sed "s/\([a-z]\)/$uppercase_letter\1/g")
        echo "$modified_line" >> "$temp_file"
    done < "$file"

    # Replace the original file with the modified content
    mv "$temp_file" "$file"
done

echo "Processing complete."