#Create a shell script that takes one or more directory paths as arguments.
#For each valid directory provided, the script will find all text files 
#(ending with .txt). For each .txt file found, the script will ddisplay its 
#first 5 lines. If no arguments are provided, or if none of the arguments are valid 
#directories, the script should display an appropriate error message.

#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage $0 <dir1> [dir2...]"
    exit 1
fi

for dir in "$@"
do  
    if [ ! -d dir ]; then
        echo "Not  valid directory"
        exit 1
    fi
    
    for file in $dir/*;
    do 
        if [ -f "$file" ] && [ "$(file -b --mime-type "$file")" = "text/plain" ]; then
            echo "file: '$file' "
            head -n 5 "$file"
            echo
        fi
    done
done
