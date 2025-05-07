#!/bin/bash
#Write a shell script that takes a natural number as parameter.
#the script wil check if the given number is prime or not.

echo "Enter your number"
read nr

for ((i=2; i<=nr/2; i++))
do
	remainder=$(( nr%i ))
	if [ $remainder -eq 0 ]; then
		echo "Number is not prime"
		exit 0
	fi
done
echo "Number is prime"
