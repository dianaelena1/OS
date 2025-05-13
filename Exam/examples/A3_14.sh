#!/bin/bash

if [[ $# -ne 1 || ! $1 =~ ^[0-2][0-9]:[0-5][0-9]-[0-2][0-9]:[0-5][0-9]$ ]]; then
  echo "Usage: $0 <hh:mm-hh:mm>" >&2
  exit 1
fi

start_time=$(echo "$1" | cut -d'-' -f1)
end_time=$(echo "$1" | cut -d'-' -f2)

start_timestamp=$(date -d "$start_time" +"%b %d %H:%M")
end_timestamp=$(date -d "$end_time" +"%b %d %H:%M")

last_output=$(last | awk -v start="$start_timestamp" -v end="$end_timestamp" '$5 " " $6 >= start && $5 " " $6 <= end')

num_users=$(echo "$last_output" | awk '{print $1}' | sort -u | wc -l)
num_sessions=$(echo "$last_output" | wc -l)

if [ "$num_sessions" -gt 0 ]; then
    average_users=$(echo "scale=2; $num_sessions / $num_users" | bc)
else
    average_users=0
fi


echo "Average number of users connected between $start_time and $end_time: $average_users"
