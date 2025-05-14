# Write a shell script which takes as parameters several file names. The script will delete the 2nd and 4th word in each line of the given files. 
# The words shall contain only letters or numbers and shall be separated by spaces.
#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Please input file names when using the script."
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi

	sed -i -E 's/\b([[:alnum:]]+)\b[[:space:]]+([[:alnum:]]+)\b([[:space:]]+[[:alnum:]]+\b)[[:space:]]+([[:alnum:]]+)\b/\1 \3/g' "$file"
echo "Words removed succesfully"
done
