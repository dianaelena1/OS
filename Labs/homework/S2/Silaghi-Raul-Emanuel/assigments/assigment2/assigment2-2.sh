#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <group_name> <filename>"
    exit 1
fi

group_name=$1
file=$2

if [ ! -f "$file" ]; then
    echo "Error: File '$file' not found."
    exit 1
fi

echo "Group: $group_name"
users=$(awk -v grp="$group_name" '$2 == grp { print $1 }' "$file")

if [ -z "$users" ]; then
    echo "No users found in this group."
else
    echo "Users:"
    echo "$users"
fi
