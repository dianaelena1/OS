#Write a shell script which takes as parameters several file names. The script will delete
#the 2nd and 4th word in each line of the given files. The words shall contain only
#letters or numbers and shall be separated by spaces.
#!/bin/bash

if [ "$#" -eq 0 ]; then
  echo "Usage: $0 file1 [file2 ... fileN]"
  exit 1
fi

for file in "$@"
do
    if [ ! -f "$file" ] || [ ! -r "$file" ]; then
        echo "Skipping '$file': not a readable file."
        continue
    fi

    sed -E 's/^(([[:alnum:]]+)[[:space:]]+)([[:alnum:]]+)[[:space:]]+(([[:alnum:]]+)[[:space:]]+)?([[:alnum:]]+)?/\
    \2 \4\6/' "$file" > tmpfile && mv tmpfile "$file"
done
