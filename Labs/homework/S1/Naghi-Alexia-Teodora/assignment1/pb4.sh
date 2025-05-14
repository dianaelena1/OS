#!/bin/bash
#write a shell script that reads numbers from the keyboard 
#(the reading stops when the user has entered the number 0)
#the script will display the sum of numbers entered from the keyboard. 


sum=0

while true; do
    read -p "Enter a number (0 to stop): " num

    if [ "$num" -eq 0 ]; then
        break
    fi
    
    sum=$((sum + num))
done

echo "Total sum: $sum"
