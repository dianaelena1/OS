#Write a shell script that takes several file names as parameters. The script will interchange the 1st word with the 3rd word in each line of the given files. The words contain only letters or numbers and are separated by any other character.
#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <file1> [file2 ...]"
    exit 1
fi

for FILE in "$@"; do
    if [ ! -f "$FILE" ]; then
        echo "File $FILE not found! Skipping..."
        continue
    fi

    echo "Processing file: $FILE"

    while IFS= read -r LINE; do
        WORDS=($(echo "$LINE" | grep -oE '[[:alnum:]]+'))

        if [ "${#WORDS[@]}" -lt 3 ]; then
            echo "$LINE"
            continue
        fi

        W1="${WORDS[0]}"
        W3="${WORDS[2]}"

        MODIFIED=$(echo "$LINE" \
            | sed "0,/$W1/{s/$W1/__TEMP__/}" \
            | sed "0,/$W3/{s/$W3/$W1/}" \
            | sed "s/__TEMP__/$W3/")

        echo "$MODIFIED"
    done < "$FILE"
done
