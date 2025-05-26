#!/bin/bash
# Write a shell script which takes as parameters two file names (a file that contains usernames and a file that contains any text). 
# The script will send a mail to each user in the first file (the mail message will be the text in the second file).



if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <usernames_file> <message_file>"
    exit 1
fi

USERNAMES_FILE="$1"
MESSAGE_FILE="$2"

if [ ! -f "$USERNAMES_FILE" ]; then
    echo "Error: Usernames file '$USERNAMES_FILE' not found!"
    exit 1
fi

if [ ! -f "$MESSAGE_FILE" ]; then
    echo "Error: Message file '$MESSAGE_FILE' not found!"
    exit 1
fi

MESSAGE_CONTENT=$(cat "$MESSAGE_FILE")

while IFS= read -r USERNAME; do
    echo "$MESSAGE_CONTENT" | mail -s "Notification" "$USERNAME"
    echo "Mail sent to: $USERNAME"
done < "$USERNAMES_FILE"

echo "All emails sent successfully."
