#Write a Shell program that receives as parameters two directory names and moves the branch specified 
#by the second directory in the first directory, as a subbranch, adding the extension .unu to each file 
#contained. 

#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <destination_directory> <source_directory>"
    exit 1
fi

DEST_DIR="$1"
SRC_DIR="$2"
BASENAME_SRC=$(basename "$SRC_DIR")
TARGET_DIR="$DEST_DIR/$BASENAME_SRC"

if [ ! -d "$DEST_DIR" ]; then
    echo "Error: Destination directory '$DEST_DIR' does not exist."
    exit 1
fi

if [ ! -d "$SRC_DIR" ]; then
    echo "Error: Source directory '$SRC_DIR' does not exist."
    exit 1
fi

mv "$SRC_DIR" "$DEST_DIR"

find "$TARGET_DIR" -type f | while read -r file; do
    mv "$file" "$file.unu"
done

echo "Move complete. All files in '$TARGET_DIR' have '.unu' extension."
