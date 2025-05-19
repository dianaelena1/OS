#Pb 7:Write a shell script which takes as parameter a directory name. 
#The script will determine the total number of lines in all ASCII text 
#files in this directory and its subdirectories. It is assumed that any 
#directory will only contain ASCII text files.

#!/bin/bash
if [-z "$1"];
    then 
        echo "Usage $0 <directory>"
        exit 1
fi

dir="$1"


if [! -d "$dir"];
    then 
        echo "Error: $dir is not a valid directory."
        exit 1
fi


total_lines=0
 
for file in $(find "$dir" -type f); 
    do
        lines=$(wc -l < "$file")
        total_lines=$((total_lines + lines))
done

echo "Total number of lines in all files: $total_lines"