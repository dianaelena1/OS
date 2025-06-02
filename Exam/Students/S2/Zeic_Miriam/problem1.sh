#Write a shell script that reads numbers from the keyboard until the number 1
#is entered. The script will print the square of each number entered before 1.

#!/bin/bash

#sum=0;
while true;
do
    read -p "Enter a number (1 will stop the entering): " number
    if ! [[ "$number" =~ ^-?[0-9]+$ ]]; then
        echo "Error: provide numbers"
        continue
    fi

    if [[ "$number" == "1" ]]; then
        break;
    fi

    square=$(($number*number))
   
    echo "Number $number: $square"
done 

