#Given a list of filenames and a directory name, 
#write a Shell script that prints for each file 
#all the subdirectories in which it appears. 
#Print these subdirectories sorted in decreasing 
#order of the creation date and time.  

#!/bin/bash
if [ $# -lt 2 ]; then
    echo "Usage: $0 <root-directory> <file1> [file2 ... fileN]"
    exit 1
fi 

root_directory="$1";
shift

for file in "$@"; do
   echo "File: $file"
   find "$root_directory" -type f -name "$file" -printf '%W %h\n' \
        | sort -nr \
        | cut -d' ' -f2-
done