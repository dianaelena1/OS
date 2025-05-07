#Pb 1 - Write a shell script which takes as parameters a short month name
# followed by a day number (ex: Mar 8). 
# For each possible 4 hours interval, the script will display the time
# interval (hh:mm-hh:mm) and the average number of users that were connected
# to the server on that date and within that time frame.


#!/bin/bash

if [ "$#" -ne 2 ]
then
    echo "Usage: $0 [month_abbrev] [day]"
    exit 1
fi

month_abbrev="${1,,}"
day="$2"
year=$(date +%Y)

declare -A months=(
    [jan]=01 [feb]=02 [mar]=03 [apr]=04 [may]=05 [jun]=06
    [jul]=07 [aug]=08 [sep]=09 [oct]=10 [nov]=11 [dec]=12
)

month_num="${months[$month_abbrev]}"
if [ -z "$month_num" ]
then
    echo "Invalid month abbreviation: $month_abbrev"
    exit 1
fi

echo "Average users connected on $year-$month_num-$day:"

for (( hour=0; hour<24; hour+=4 ))
do
    start_time=$(printf "%02d:00" "$hour")

    next_hour=$((hour + 4))
    if [ "$next_hour" -eq 24 ]
    then
        end_time="00:00"
        end_date=$(date -d "$year-$month_num-$day +1 day" +%Y-%m-%d)
    else
        end_time=$(printf "%02d:00" "$next_hour")
        end_date="$year-$month_num-$day"
    fi

    interval="$start_time-$end_time"

    users=$(last -s "$year-$month_num-$day $start_time" -t "$end_date $end_time" \
        | grep -vE '^(reboot|wtmp)' | awk '{print $1}' | sort | uniq | wc -l)

    printf "Interval: %s, Average users: %d\n" "$interval" "$users"
done
