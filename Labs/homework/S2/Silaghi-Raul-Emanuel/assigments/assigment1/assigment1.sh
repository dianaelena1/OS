#!/bin/bash

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