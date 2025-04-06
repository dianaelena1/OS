#!/bin/bash

#Write a shell script that takes a group name (ex: gr821) as a parameter. The script will display the given group name followed by the list of all users that belong to that group.
group=$1


line=$(grep "^${group}:" /etc/group)


users=$(echo "$line" | cut -d: -f4)


echo "$group: $users"
