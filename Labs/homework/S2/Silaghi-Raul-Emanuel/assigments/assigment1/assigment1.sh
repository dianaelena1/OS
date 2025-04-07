#!/bin/bash

# Write a shell script that reads words from keyboard (the reading stops when the user has entered the word "stop").
# The script will display the list of words entered from the keyboard.
words=()
echo "Enter the words. Type 'stop' to finish."


while true; do
  read -p "Enter word: " word

  if [ "$word" = "stop" ]; then
    break
  fi

  words+=("$word")
done

echo "You entered the following words: "
for word in "${words[@]}"; do
  echo "$word"
done