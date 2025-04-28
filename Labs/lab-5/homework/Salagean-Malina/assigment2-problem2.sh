#Write a shell script which takes as parameters several user accounts (ex: gmae0221 jpae0229). The script will display all directories in each user's home directory that have write permission for the group of which the owner belongs.
#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <username1> [username2 ...]"
    exit 1
fi

for USER in "$@"; do
    HOME_DIR=$(eval echo ~$USER)

    if [ ! -d "$HOME_DIR" ]; then
        echo "Home directory for user $USER not found! Skipping..."
        continue
    fi

    echo "Directories with group write permission in $USER's home directory:"

    ls -ld "$HOME_DIR"/*/ 2>/dev/null | grep '^d....w....'

    echo "--------------------------------------------------"
done
