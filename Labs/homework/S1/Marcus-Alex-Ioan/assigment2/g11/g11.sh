#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <user1> <user2> ... <userN>"
    exit 1
fi

for user in "$@"; do
    if id "$user" &>/dev/null; then
        if ! last "$user" | grep -q "still logged in" && ! last "$user" | grep -q "logged in"; then
            echo "User '$user' has never logged into the server." 
        fi
    else
        echo "User '$user' does not exist." 
    fi
done
