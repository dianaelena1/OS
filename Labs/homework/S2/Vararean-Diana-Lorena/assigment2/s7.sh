#Pb s7 - Write a shell script which takes as parameters several file names.
# The script will replace all lowercase vowels with corresponding uppercase 
# letters in each line of the given files.

#!/bin/bash

for file in "$@"
do
    if [ -f "$file" ]
    then
        sed -i 's/a/A/g; s/e/E/g; s/i/I/g; s/o/O/g; s/u/U/g' "$file"
    else
        echo "Error: '$file' does not exist."
    fi
done