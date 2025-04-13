#!/bin/bash
#Write a shell script that takes a group name (ex: gr821) as a parameter. 
#The script will display the given group name followed by the list of all students that belong to that group.
#Each line in the student list will contain the username of the student followed by its full name.



if [ -z "$1" ]; then
    echo "Usage: $0 <groupname>"
    exit 1
fi

GROUP_NAME="$1"
GROUP_FILE="fake_group"
PASSWD_FILE="fake_passwd"

if [ ! -f "$GROUP_FILE" ] || [ ! -f "$PASSWD_FILE" ]; then
    echo "Files not found!"
    exit 3
fi

GROUP_LINE=$(awk -F: -v group="$GROUP_NAME" '$1 == group {print}' "$GROUP_FILE")

if [ -z "$GROUP_LINE" ]; then
    echo "Group '$GROUP_NAME' not found."
    exit 2
fi

USER_LIST=$(echo "$GROUP_LINE" | awk -F: '{print $4}')

echo "Group: $GROUP_NAME"
echo "Students in group:"

IFS=',' read -ra USERS <<< "$USER_LIST"
for USER in "${USERS[@]}"; do
    USER=$(echo "$USER" | xargs)./A_O_h3.sh gr821

    [ -z "$USER" ] && continue

    FULL_NAME=$(awk -F: -v user="$USER" '$1 == user {print $5}' "$PASSWD_FILE" | xargs)

    if [ -z "$FULL_NAME" ]; then
        echo "$USER - Full name not found"
    else
        echo "$USER - $FULL_NAME"
    fi
done

