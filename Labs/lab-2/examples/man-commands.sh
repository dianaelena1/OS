#!/bin/bash

# Display the help menu for the 'man' command
echo "Displaying help for 'man' command:"
man --help

# Search for commands that contain a specific keyword
keyword="network"
echo "Searching for commands related to '$keyword' using apropos:"
man --apropos "$keyword"

# Get a short description for a command
command="ls"
echo "Getting a short description for '$command' using whatis:"
man --whatis "$command"

# Search for occurrences of 'ip' in all man pages and output results to 'pwd'
search_term="ip"
output_file="man_search_results.txt"
echo "Searching for '$search_term' in man pages and saving output to $output_file"
man -K "$search_term" -o "$output_file"

# Displaying details about the 'history' command
echo "Displaying details about 'history' command from man:"
man history

# # Using the history command to see past commands
# echo "Showing recent command history:"
# history | tail -10
