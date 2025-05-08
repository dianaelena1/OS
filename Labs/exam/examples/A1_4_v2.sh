#!/bin/bash
echo "This is a script that will compute all the numbers given from the keyboard until 0 when the program stops and shows the result"

read -p "Enter the first number: " number

if [[ -z "$number" ]]; then
	echo "Error: Number cannot be empty"
	exit 1
fi 

if [[ "$number" =~ ^[0-9]+$ ]]; then
	sum=$number
	i=2

else 
	echo "Error: Invalid number input"
	exit 1
fi

while [[ $number -ne 0 && "$number" =~ ^[0-9]+$ ]];

do
	
	read -p "Number $i: " number

	if [[ -z "$number" ]]; then
        	echo "Error: Number cannot be empty"
        	exit 1

	fi

	if [[ "$number" =~ ^[0-9]+$ ]]; then
	        sum=$((sum+number))
		let i+=1

	else
        	echo "Error: Invalid number input"
		exit 1

	fi
done

echo "The result is:" $sum 

