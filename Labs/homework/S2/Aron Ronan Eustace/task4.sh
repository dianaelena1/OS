#!/bin/bash

#Write a Shell program that supervises the system, such that: the program saves in a file all the users that launch the command ftp, specifying the time and (if available) the server from which the ftp connection is being attempt.


log_file="ftp_log.txt"

if [ "$#" -ne 0 ]; then
  echo "Usage: $0 (no arguments needed)"
  exit 1
fi

echo "Monitoring started... Press Ctrl+C to stop."

while true; do
  who | while read -r user terminal date time rest; do
    ps -u "$user" | grep -w ftp > /dev/null 2>&1
    if [ $? -eq 0 ]; then
      server=$(who | grep "$user" | awk '{ print $5 }' | tr -d '()')
      current_time=$(date '+%Y-%m-%d %H:%M:%S')
      echo "$current_time - $user started ftp (server: $server)" >> "$log_file"
    fi
  done
  sleep 10
done

