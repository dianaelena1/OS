#Write a bash script that counts all the C files from a given directory and all of its subdirectories.

#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Insufficient arguments"
    exit 1
fi

find $1 -type f | grep -E -c "\.c$"