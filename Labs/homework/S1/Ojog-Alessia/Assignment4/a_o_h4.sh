#!/bin/bash

#12
#Write a Shell program that, given a directory (as a parameter),
#creates a list of all the names that appear in it and its subdirectories (files, directories), 
#and for each file it prints the maximum number of repeating lines (in the same file).

if [ -z "$1" ]; then
   echo "Usage: $0 <directory>"
   exit 1
fi

DIR="$1"


if [ ! -d "$DIR" ]; then
    echo "Error: '$DIR' is not a directory."
    exit 2
fi

echo "Files and directories in: $DIR"
echo "-----------------------------------------"

find "$DIR" | while read -r PATH; do
    echo "-> $PATH"

    if [ -f "$PATH" ]; then
        echo "Processing file: $PATH"

        MAX_REPEATS=$(/usr/bin/sort "$PATH" | /usr/bin/uniq -c | /usr/bin/awk '{print $1}' | /usr/bin/sort -nr | /usr/bin/head -n 1)

        if [ -z "$MAX_REPEATS" ]; then
            echo "   Max line repetitions: 0 (empty or unreadable file)"
        else
            echo "   Max line repetitions: $MAX_REPEATS"
        fi
    fi
done
