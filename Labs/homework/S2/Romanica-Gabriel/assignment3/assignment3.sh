            #Write a shell script which takes as parameters several file names.
            #The script will display the ratio of the number of lowercase
            #letters to the number of uppercase letters in each given file (ex:
            #file1.txt l/U = 95/12).

#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 file1 [file2 ...]"
  exit 1
fi

for file in "$@"; do
  if [ ! -f "$file" ]; then
    echo "$file does not exist or is not a regular file."
    continue
  fi

  lower=$(grep -o '[a-z]' "$file" | wc -l)
  upper=$(grep -o '[A-Z]' "$file" | wc -l)

  echo "$file l/U = $lower/$upper"
done
