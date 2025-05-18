# The script will determine the total number of lines in all ASCII text files in this directory and its subdirectories. 
# It is assumed that any directory will only contain ASCII text files
# $-for the value, "$" -for the name
#!/bin/bash

# Check if a directory name is given as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <directory>"
fi

# Assign the directory name to a variable
DIR="$1"

# Check if the argument is a directory
if [ ! -d "$DIR" ]; then
  echo "Error: $DIR is not a valid directory."
fi

# To count the lines
TOTAL_LINES=0

# Find all files in the directory and its subdirectories
FILES=$(find "$DIR" -type f)

# Process each file
for FILE in $FILES; do
  # Check if the file is an ASCII text file
  if file "$FILE" | grep -q "ASCII text"; then
    # Count the lines in the file
    LINES=$(wc -l < "$FILE") 
    TOTAL_LINES=$((TOTAL_LINES + LINES))
  fi
done

echo "Total number of lines in all ASCII text files: $TOTAL_LINES"