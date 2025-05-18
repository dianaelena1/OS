#Write a script that receives program/process names as command line arguments. 
#The script will monitor all the processes in the system, and whenever a program with one of those names is run, 
#the script will kill it and display a message. (see commands ps, kill, killall). Alternativ, comenzile pkill/pgrep pot fi folosite.

#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Provide at least one name"
    exit 1
fi

while true; do

for process in $@; do
    PIDs=""
    PIDs=$(ps -ef | awk '{print $8" "$2}' | grep -E "\<$process " | awk '{print $2}')

if [ -n "$PIDs" ]; then
    kill -9 $PIDs
fi
done

sleep 3
done