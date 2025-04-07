#!/bin/bash

# Write a shell script which takes as parameters several host
# names (ex: www.cs.ubbcluj.ro www.google.ro). The script will
# display the host names (from those given as parameters) that are alive.
# Use the ping command to verify that a given host is alive.

for site in "$@"; do
	ping -c 1 -W 1 "$site" > /dev/null 2>&1 
	if [ $? -eq 0 ]; then
		echo "The site $site is alive"
	else
		echo "The site $site is not alive"
	fi

done
