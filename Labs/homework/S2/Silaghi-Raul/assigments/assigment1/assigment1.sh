#!/bin/sh

words=""

echo "Enter words one by one. Type 'stop' to finish."

while true
do
    printf "Enter word: "
    read word
    if [ "$word" = "stop" ]; then
        break
    fi
    words="$words $word"
done

echo "You entered the following words:"
echo "$words"
