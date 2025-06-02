# Write a shell script that reads numbers from keyboard (the reading stops when the user has entered the number 1). The script will display each number squared.

#!/bin/bash

input=0
square=0
echo "Enter numbers (enter 1 to stop):"

while [ "$input" -ne 1 ]
do
  read -p "Number: " input


  if ! [[ "$input" =~ ^-?[0-9]+$ ]]; then 
    echo "Invalid input. Please enter an integer."
    input=0  
    continue
  else
    square=$((input*input))
    if [ "$input" -ne 1 ]; then
      echo "$square"
    fi
  fi
done

# ./problem1.sh 