#!/bin/bash
#Write a shell script that takes a command name as parameter. The script will display all the users acounts that running the given command.


#check if a command name is provided
if [ "$#" -lt 1 ]; then
	echo "Usage: $0 <command name>"
	exit 1
fi


command_name="$1"

#find processes running the command  and display users
ps -eo user,comm | awk -v cmd="$command_name" '$2 == cmd {print $1}' | sort -u
