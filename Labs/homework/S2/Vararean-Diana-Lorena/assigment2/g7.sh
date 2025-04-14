#Pb g7 - Write a shell script which takes as parameters several host names
# (ex: www.cs.ubbcluj.ro www.google.ro). The script will display the host names 
# (from those given as parameters) that are alive. Use the ping command to verify 
# that a given host is alive. 

#!/bin/bash

for host in "$@"
do
    ping -c 1 -w 2 "$host" > /dev/null 2>&1

    if [ $? -eq 0 ]
    then
        echo "$host is alive."
    else
        echo "$host is unreachable."
    fi
done