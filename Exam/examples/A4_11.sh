#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Error: No parameters provided."
    exit 1
fi

directory="${@: -1}"

if [ ! -d "$directory" ]; then
        echo "Error: No directory provided."
        exit 1
fi


echo directory

for ((param=1;param<$#;param++));
 do

        if ! find ~/ -name "${!param}" -quit 2>/dev/null; then
    echo "Error: ${!param} does not exist."
    exit 1

	else 
        directories=$(find "$directory" -name "${!param}" -exec du -h {} +)

         # Sort directories based on file size (the size is the first column in the output of 'du -h')
         sorted_directories=$(echo "$directories" | sort -rh)
        # Output sorted directories
        echo "$sorted_directories"
         fi
done

