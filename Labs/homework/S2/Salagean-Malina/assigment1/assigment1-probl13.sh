#Write a shell script which takes as parameter a username (ex: bdae0198). 
#The script will determine the section (extract the letters on positions 3 and 4) and the sum of all digits in the username.

#!/bin/bash
if [ -z "$1" ]; then
    echo "Usage: $0 <username>"
    exit 1
fi

USERNAME="$1"

SECTION=$(echo "$USERNAME" | cut -c3-4)

SUM=0
for (( i=0; i<${#USERNAME}; i++ )); do
    CHAR="${USERNAME:$i:1}"
    if [[ "$CHAR" =~ [0-9] ]]; then
        SUM=$((SUM + CHAR))
    fi
done


echo "Section: $SECTION"
echo "Sum of digits: $SUM"
