#Write a shell script that takes as parameters several 
#file names. For each line in the given files in which 
#a word appears 2 or more times, the script will display 
#the number of that line, and the word involved.

#!/bin/bash

if [ "$#" -eq 0 ]; then
  echo "Usage: $0 file1 [file2 ... fileN]" >&2
  exit 1
fi

for file in "$@"
do
    if [ ! -f "$file" ] || [ ! -r "$file" ]; then
        echo "Skipping '$file': not a readable file."
        continue
    fi

    awk '{
            delete counts

            for (i = 1; i <= NF; i++) {
                counts[$i]++
            }

            for (word in counts) {
                if (counts[word] >= 2) {
                    print FILENAME ": " FNR ": " word
                }
            }
        }' "$file"
done
