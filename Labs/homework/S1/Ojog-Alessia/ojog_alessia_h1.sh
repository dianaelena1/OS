#!/bin/bash

#6
#Write a shell script that reads words from keyboard (the reading stops when the user has entered the word "stop"). The script will display the list of words entered from the keyboard.

#empty array to store words
words=()


while true; do
    read -p "Enter a word (type 'stop' to finish): " word
    if [[ "$word" == "stop" ]]; then
        break
    fi
    words+=("$word")
done

#list of words entered
echo "You entered the following words:"
for w in "${words[@]}"; do
    echo "$w"
done
