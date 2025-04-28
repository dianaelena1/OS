#Pb. 4 - Write a shell script that reads numbers from keyboard 
# (the reading stops when the user has entered the number 0). 
# The script will display the sum of numbers entered from the keyboard.

#!/bin/bash
sum=0
while true
do
        read val
        if [ $val -lt 0 ]
        then
                break
        fi
        sum=$((sum+val))
done
echo $sum