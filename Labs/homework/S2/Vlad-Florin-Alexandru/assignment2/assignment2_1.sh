#!/bin/bash
#Write a shell script which takes as parameters an uppercase letter followed by several file names. The script will add the given letter in the front of each lowercase on each line in all given files.
letter=$1
shift


for file in "$@"; do

    grep '[a-z]' "$file" > /dev/null

    sed -i "s/\([a-z]\)/$letter\1/g" "$file"
done
