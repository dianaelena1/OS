#Write a shell script which takes as parameters 
#two file names (a file that contains usernames and a file that contains any text). 
#The script will send a mail to each user in the first file 
#(the mail message will be the text in the second file).

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

