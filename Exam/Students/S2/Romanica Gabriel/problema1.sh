
#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 file1 file2"
    exit 1
fi

file1="$1"
file2="$2"

if [ ! -e "$file1" ] || [ ! -e "$file2" ]; then
    echo "Error: One or both files do not exist."
    exit 1
fi

line_num=1
count=0
while IFS= read -r line1 && IFS= read -r line2 <&3; do
    if [ "$line1" != "$line2" ]; then
        echo "Line $line_num:"
        echo "$file1: $line1"
        echo "$file2: $line2"
        count=$((count+1))
        break
    fi
    line_num=$((line_num+1))
done < "$file1" 3< "$file2"

if [ "$count" -eq 0 ]; then
    echo "No differences found."
elif [ "$count" -ne 0 ]; then
    echo "Files are different."
fi
