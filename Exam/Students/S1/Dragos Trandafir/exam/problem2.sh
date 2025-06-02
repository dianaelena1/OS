# Write a shell script which takes as parameter more directory names. The script will display the filename, and the first 5 lines of each ASCII text file found in that directory.

#!/bin/bash

valid_directories=0

if ! [ $# -ge 1 ]; then
    echo "Usage: $0 directory_name1 directory_name2 ..."
    exit 1
fi

directories=( "$@" )

for directory in ${directories[@]}

do
        if [[ -d "${directory}" ]]; then
                valid_directories=1
                break
        fi
done

if [ $valid_directories == 0 ]; then
  echo "No valid directories!"
  exit 1
fi


for directory in ${directories[@]}
do
	for file in $directory/*; 
do
    if [ -f "$file" ] && [ "$(file -b --mime-type "$file")" = "text/plain" ]; then
        echo "Filename: $file"
        head -n 5 "$file"
        echo
    fi
done
done



# cd ./Labs/lab-4/homework/dragos_trandafir_h1
# sudo ./problem2.sh dir1
