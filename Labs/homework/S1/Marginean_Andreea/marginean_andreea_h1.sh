# The script will determine the total number of lines in all ASCII text files in this directory and its subdirectories. 
# It is assumed that any directory will only contain ASCII text files
# $-for the value, "$" -for the name
#!/bin/bash

# Check if a directory name is given as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <directory>"
fi


DIR="$1"


if [ ! -d "$DIR" ]; then
  echo "Error: $DIR is not a valid directory."
fi


TOTAL_LINES=0


FILES=$(find "$DIR" -type f)


for FILE in $FILES; do

  if file "$FILE" | grep -q "ASCII text"; then
  
    LINES=$(wc -l < "$FILE") 
    TOTAL_LINES=$((TOTAL_LINES + LINES))
  fi
done

echo "Total number of lines in all ASCII text files: $TOTAL_LINES"