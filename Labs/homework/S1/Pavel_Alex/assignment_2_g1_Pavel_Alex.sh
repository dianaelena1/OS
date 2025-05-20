#!/bin/bash
#write a shell script which takes as parameter a directory name. The script will display the content of all text files in the given direcory and its subdirectories

if [ $# -ne 1 ]; then
    echo "Usage: $0 directory_name"
    exit 1
fi

directory="$1"

if [ ! -d "$directory" ]; then
    echo "Error: Directory '$directory' not found"
    exit 1
fi


process_files() {
    local dir="$1"
    
    find "$dir" -type f | while read -r file; do
        
        if file "$file" | grep -q "text"; then
            echo "=== Contents of: $file ==="
            cat "$file"
            echo "================="
            echo
        fi
    done
}

process_files "$directory"

echo "Finished displaying text file contents"
