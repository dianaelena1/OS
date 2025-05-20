#Find recursively in a given directory all the symbolic links, and report those that point to files/directories 
#that no longer exist. Use option -L to test if a path is a symbolic link, and option -e to test if it exists 
#(will return false if the target to which the link points does not exist)

#!/bin/bash
for link in $(find "$1" -type l); do

if [ ! -e "$link" ]; then
    echo "Link $link is not valid"
fi

done