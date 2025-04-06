#!/bin/bash
#Write a shell script which takes as parameters an uppercase letter followed by several file names. The script will add the given letter in the front of each lowercase on each line in all given files.

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 UPPERCASE_LETTER file1 [file2 ...]"
    exit 1
fi

letter=$1


if ! [[ $letter =~ ^[A-Z]$ ]]; then
    echo "Error: The first parameter must be a single uppercase letter."
    exit 1
fi

shift

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "Warning: File '$file' does not exist. Skipping."
        continue
    fi

    sed -i "s/\([a-z]\)/$letter\1/g" "$file"
    echo "Updated '$file'."
done
