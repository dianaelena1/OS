#!/bin/bash

#10	Write a shell script which takes as parameter an existing group number (ex: 821). The script will display the details about that group.

echo "Enter group number:"
read group 

group_info=$(getent group $group) 

if [ -n "$group_info" ]; then 

    echo "Group info: $group_info" 
else
    echo "Group not found" 
