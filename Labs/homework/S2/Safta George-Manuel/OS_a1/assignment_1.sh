#!/bin/bash

# Check if exactly two arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <usernames_file> <message_file>"
    exit 1
fi

# Assign arguments to variables
USERNAMES_FILE="$1"
MESSAGE_FILE="$2"

# Check if the files exist
if [ ! -f "$USERNAMES_FILE" ]; then
    echo "Error: Usernames file '$USERNAMES_FILE' not found!"
    exit 1
fi

if [ ! -f "$MESSAGE_FILE" ]; then
    echo "Error: Message file '$MESSAGE_FILE' not found!"
    exit 1
fi

# Read message content
MESSAGE_CONTENT=$(cat "$MESSAGE_FILE")

# Send email to each user
while IFS= read -r USERNAME; do
    echo "$MESSAGE_CONTENT" | mail -s "Notification" "$USERNAME"
    echo "Mail sent to: $USERNAME"
done < "$USERNAMES_FILE"

echo "All emails sent successfully."
