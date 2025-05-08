# Write a shell script which takes as parameters several file names. 
# The script will delete all words that contain at least one digit from all given files.
#!/bin/bash

for file in "$@"; do
    if [ -f "$file" ]; then
        # Use sed to delete words containing at least one digit
        sed -i -E 's/\b[[:alpha:]]*[[:digit:]][[:alnum:]]*\b//g' "$file"
        echo "Words containing digits deleted from $file"
    else
        echo "File $file not found."
    fi
done
