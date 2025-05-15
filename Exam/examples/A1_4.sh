#!/bin/sh
#Write a shell script that reads numbers from keyboard (the reading stops when the user has entered the number 0). 
#The script will display the sum of numbers entered from the keyboard.

echo "Enter the numbers"
suma=0

while true;
do
    read x
    if [ "$x" -eq 0 ];
    then
        break
    fi
    suma=$((suma+x))
done

echo "Suma: $suma"

