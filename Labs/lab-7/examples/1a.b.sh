#A.Write a bash script that counts all the lines of code in the C files from the directory given as command-line argument, 
#excluding lines that are empty or contain only spaces.

#!/bin/bash
if [ $# -lt 1 ]; then
echo "Insufficient arguments"
exit 1
fi
find $1 -type f | grep -E -c "\.c$"


#B.Write a bash script that counts all the lines of code in the C files from the directory given as command-line argument 
#and all its subdirectories, excluding lines that are empty or contain only spaces.

#!/bin/bash
if [ -z "$1" ]; then
    echo "No parameters given"
    exit 1
fi
if [ ! -d "$1" ]; then
    echo "Parameter is not a folder"
    exit 1
fi

total=0

    for f in $(find "$1" -type f | grep -E "\.c$"); do
    nr_lines=$(grep -E -c -v "^[ \t]*$" $f)
    echo "$f - $nr_lines"
    total=$((total+nr_lines))
done

echo "Total lines: $total"



x=7
y=2
let "z = x * y"
echo $z


