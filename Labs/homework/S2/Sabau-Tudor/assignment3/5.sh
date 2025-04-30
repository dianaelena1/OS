#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <file1> [file2] [...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "Error: File '$file' does not exist."
        continue
    fi

    awk -v filename="$file" '
    BEGIN { count = 0 }
    length($0) > 10 {
        count++
        print "Line " NR ": " substr($0, 11)
    }
    END {
        print "Finished analyzing \"" filename "\". Lines displayed: " count
        print "-------------------------------------------"
    }
    ' "$file"

done
