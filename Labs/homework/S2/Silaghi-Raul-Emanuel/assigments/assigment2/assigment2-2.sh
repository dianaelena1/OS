#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <group_name>"
    exit 1
fi

group_name=$1

group_info=$(getent group "$group_name")

if [ -z "$group_info" ]; then
    echo "Error: Group '$group_name' not found."
    exit 1
fi

users=$(echo "$group_info" | cut -d: -f4)

echo "Group: $group_name"
if [ -z "$users" ]; then
    echo "No users found in this group."
else
    echo "Users: $users"
fi
