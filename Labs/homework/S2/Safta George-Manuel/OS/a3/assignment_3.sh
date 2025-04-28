#!/bin/bash
# Write a shell script which takes as parameters several file names. For each file, the script will display the name of the file, the sum of  
# the numbers on each line in that file and the ratio of the lines l1 that 
# contain numbers to the lines l2 that do not contain numbers (ex: file1 sum = 1234 l1/l2 = 3/5).

# Check if there are any arguments
if [ $# -eq 0 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

# Process each file
for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi

    total_sum=0
    l1=0
    l2=0

    while IFS= read -r line; do
        # Extract numbers from the line
        numbers=$(echo "$line" | grep -oE '[+-]?[0-9]+(\.[0-9]+)?')
        
        if [ -n "$numbers" ]; then
            # Sum the numbers
            line_sum=0
            for num in $numbers; do
                line_sum=$(echo "$line_sum + $num" | bc)
            done
            total_sum=$(echo "$total_sum + $line_sum" | bc)
            l1=$((l1 + 1))
        else
            l2=$((l2 + 1))
        fi
    done < "$file"

    echo "$file sum = $total_sum l1/l2 = $l1/$l2"
done

