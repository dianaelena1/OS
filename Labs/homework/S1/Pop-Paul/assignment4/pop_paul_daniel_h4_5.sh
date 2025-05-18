#Write a Shell program that receives as parameters two directory names and moves the branch specified
#by the second directory in the first directory, as a subbranch, adding the extension .unu to each file contained.  

#!/bin/bash

# Check for exactly two arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <target_directory> <source_directory>"
    exit 1
fi

# Assign arguments to variables
TARGET_DIR="$1"
SOURCE_DIR="$2"

# Check if both directories exist
if [ ! -d "$TARGET_DIR" ]; then
    echo "Error: Target directory '$TARGET_DIR' does not exist."
    exit 1
fi

if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Source directory '$SOURCE_DIR' does not exist."
    exit 1
fi

# Extract the name of the source directory (last component of the path)
BRANCH_NAME=$(basename "$SOURCE_DIR")

# Destination path
DEST="$TARGET_DIR/$BRANCH_NAME"

# Move the directory
mv "$SOURCE_DIR" "$DEST"

# Add .unu extension to all files in the moved branch
find "$DEST" -type f | while read file; do
    mv "$file" "$file.unu"
done

echo "Branch '$BRANCH_NAME' moved into '$TARGET_DIR' and files renamed with .unu extension."
