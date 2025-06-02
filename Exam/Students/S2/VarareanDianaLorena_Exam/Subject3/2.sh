# Write a script that recieves an uppercase letter and several file names as arguments,
# and replaces all non-alphabetic characters in those files with that letter.


#!/bin/bash

if [ "$#" -lt 2 ]
then
    echo "Usage: $0 <uppercase_letter> <file1> [file2] ..."
    exit 1
fi

uppercase=$1
shift

if [[ ! "$uppercase" =~ ^[A-Z]$ ]]
then
    echo "Error: First argument must be a single uppercase letter."
    exit 1
fi

for file in "$@"
do
    if [ ! -f "$file" ]
    then
        echo "Warning: File '$file' does not exist. Skipping."
        continue
    fi

    sed -i "s/\([^a-zA-Z]\)/$uppercase/g" "$file"
done