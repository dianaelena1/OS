# Write a shell script that takes several file names as parameters. 
# The script will interchange the 1st word with the 3rd word in each line of the given files. 
# The words contain only letters or numbers and are separated by any other character.
#!/bin/bash

# Check if there are arguments 
if [ $# -lt 1 ]; then
  echo "Usage: $0 <file1> <file2> ..."
  exit 1
fi

# Loop through all the input files
for file in "$@"; do
  # Check if the file exists
  if [ ! -f "$file" ]; then
    echo "File $file does not exist!"
    continue
  fi
  
  # Process each line in the file
  while IFS= read -r line; do
    # Use regex to extract and swap the first and third words, preserving the rest of the line
    new_line=$(echo "$line" | sed -E 's/([[:alnum:]]+)[^[:alnum:]]+([[:alnum:]]+)[^[:alnum:]]+([[:alnum:]]+)(.*)/\3 \2 \1\4/')
    
    echo "$new_line"
  done < "$file" > "$file.tmp" # Write the output to a temporary file

  # Replace the original file with the modified content
  mv "$file.tmp" "$file"
done