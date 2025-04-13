#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' not found. Skipping."
        continue
    fi

    echo "Processing file: $file"
    
    line_num=0

    while IFS= read -r line || [ -n "$line" ]; do
        ((line_num++))
        
        words=($line)
        count_list=()
        unique_words=()

        for word in "${words[@]}"; do
            found=0
            for i in "${!unique_words[@]}"; do
                if [ "${unique_words[$i]}" == "$word" ]; then
                    ((count_list[$i]++))
                    found=1
                    break
                fi
            done
            if [ "$found" -eq 0 ]; then
                unique_words+=("$word")
                count_list+=(1)
            fi
        done

        for i in "${!unique_words[@]}"; do
            if [ "${count_list[$i]}" -gt 1 ]; then
                echo "Line $line_num: ${unique_words[$i]}"
            fi
        done
    done < "$file"
done
