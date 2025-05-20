#Write a script that receives as command line arguments pairs consisting of a filename and a word. 
#For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.

#!/bin/bash
if [ $# -lt 2 ]; then
    echo "Please provide at least 2 arguments"
    exit 1
fi

if [ $(($# % 2)) -eq 1 ]; then
    echo "You must provide an even number of arguments"
    exit 1
fi

while [ $# -gt 1 ]; do
file=$1
word=$2

if [ ! -f "$file" ]; then
    echo "Name $file is not a file"
else

count=$(grep -E -o "\<$word\>" "$file" | wc -l)

if [ $count -ge 3 ]; then
    echo "Word $word appears $count times in file $file"
fi

fi
shift 2
done

if [ $# -eq 1 ]; then
    echo "Warning: final pair is incomplete"
fi