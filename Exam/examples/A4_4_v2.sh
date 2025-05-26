#!/bin/bash

# directory name argument
dir_name=$1

# shifting to get to the other arguments which are all file names
shift
file_names=$@

for file_name in $file_names
do
    echo "File: $file_name"
    find $dir_name -name $file_name -exec dirname {} \; | while read line
    do
        ls -lt -- "$line" | awk -v file="$file_name" '$9 == file {printf "%s %s %s %s\n", $6, $7, $8, $line}'
    done | while read month day time dir
    do
        date=$(date -d"$month $day $time" +%s)
        echo $date $dir
    done | sort -nr | while read timestamp dir
    do
        date=$(date -d@$timestamp +"%b %d %T")
        echo $date $dir
    done
done
