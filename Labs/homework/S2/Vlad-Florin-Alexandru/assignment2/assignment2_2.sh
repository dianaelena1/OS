#!/bin/bash

#Write a shell script that takes a group name (ex: gr821) as a parameter. The script will display the given group name followed by the list of all users that belong to that group.

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 group_name"
    exit 1
fi

group=$1

if ! grep -q "^${group}:" /etc/group; then
    echo "Error: Group '$group' not found."
    exit 1
fi

line=$(grep "^${group}:" /etc/group)

users=$(echo "$line" | cut -d: -f4)

echo "$group: $users"
