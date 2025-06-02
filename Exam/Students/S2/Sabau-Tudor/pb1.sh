#Write a shell script that reads numbers from the keyboard until the number 1 is entered.
#The script will print the square of each number entered before 1.
#!/bin/bash

echo "Enter numbers, to stop enter 1:"

while true; do
    read -p "Number: " num

    if [ "$num" -eq 1 ]; then
        break
    fi

    if [[ "$num" =~ ^-?[0-9]+$ ]]; then 
        square=$((num * num))
        echo "Square: $square"
    else
        echo "Invalid input"
    fi
done

echo "The program is done."
