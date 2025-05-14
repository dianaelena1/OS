#!/bin/bash
# Write a Shell program that receives as parameters two directory names and moves the branch specified by the second directory in the first directory, as a subbranch, adding the extension .unu to each file contained.

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <destination_dir> <source_dir>"
    exit 1
fi

dest_dir="$1"
src_dir="$2"

if [ ! -d "$dest_dir" ]; then
    echo "Error: Destination directory '$dest_dir' does not exist."
    exit 1
fi

if [ ! -d "$src_dir" ]; then
    echo "Error: Source directory '$src_dir' does not exist."
    exit 1
fi

src_base=$(basename "$src_dir")
target_branch="$dest_dir/$src_base"

mv "$src_dir" "$dest_dir/"

find "$target_branch" -type f | while read -r file; do
    mv "$file" "$file.unu"
done