#!/bin/bash

# Check if a group name is provided as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <group_name>"
    exit 1
fi

group_name=$1

# Check if the group exists
group_entry=$(grep "^$group_name:" /etc/group)
if [ -z "$group_entry" ]; then
    echo "Group '$group_name' does not exist."
    exit 1
fi

# Get the list of users in the group
users=$(echo "$group_entry" | cut -d: -f4)

# Display the group name and its users
echo "Group: $group_name"
if [ -z "$users" ]; then
    echo "No users in this group."
else
    echo "Users: $users"
fi