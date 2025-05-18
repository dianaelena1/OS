#Create a bash script that finds all the text files in a specified folder (the current folder if there is no specified folder). 
#For all such files, the script will report the filesize, permissions and number of unique lines.

#!/bin/bash
dir=${1:-"."}

if [ -d "$dir" ]; then

for f in $(find "$dir" -type f); do

if file $f | grep -E -q "text"; then
    size=$(du -b $f | cut -f1)
    perm=$(ls -l $f | cut -d' ' -f1)
    lines=$(sort $f | uniq | wc -l)
    echo "Filename: $f - size: $size - permissions: $perm - unique lines: $lines"
fi

done
fi