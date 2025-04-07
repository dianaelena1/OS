#!/bin/bash

# Check if at least one user is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 user1 [user2 ...]"
    exit 1
fi

# Loop through all provided users
for user in "$@"; do
    # Get the home directory of the user
    home_dir=$(getent passwd "$user" | cut -d: -f6)

    # Check if the user and home directory exist
    if [ -z "$home_dir" ] || [ ! -d "$home_dir" ]; then
        echo "User '$user' not found or home directory doesn't exist."
        continue
    fi

    # Get the primary group of the user
    group=$(id -gn "$user" 2>/dev/null)

    # Print the user's name and home directory
    echo "Checking directories for user: $user"
    echo "Home directory: $home_dir"
    echo "Primary group: $group"

    # Find only directories and check group-write permission
    ls -ld "$home_dir"/*/ 2>/dev/null | \
    grep "^d.*w" | \
    grep " $group " | \
    awk '{print "Group-writeable directory: " $9}'

    echo ""
done
