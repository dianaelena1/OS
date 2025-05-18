#Write a shell script that takes a group name (ex: gr821) as a parameter. The script will display the given group name followed by the list of all users that belong to that group.




#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <group_name>"
    exit 1
fi

group_name="$1"

group_entry=$(grep "^$group_name:" /etc/group)
if [ -z "$group_entry" ]; then
    echo "Group '$group_name' does not exist."
    exit 1
fi

users=$(echo "$group_entry" | cut -d: -f4)

echo "Group: $group_name"
if [ -z "$users" ]; then
    echo "No users in this group."
else
    echo "Users: $users"
fi