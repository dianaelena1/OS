#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <usernames_file> <message_file>"
    exit 1
fi

USERNAMES_FILE="$1"
MESSAGE_FILE="$2"


if [ ! -f "$USERNAMES_FILE" ] || [ ! -f "$MESSAGE_FILE" ]; then
    echo "Error: One or both files not found!"
    exit 1
fi


MESSAGE=$(cat "$MESSAGE_FILE")

while IFS= read -r USERNAME; do
    echo "To: $USERNAME"
    echo "Subject: Your Message Subject"
    echo "$MESSAGE"
    echo "----------------------------------"
done < "$USERNAMES_FILE"

