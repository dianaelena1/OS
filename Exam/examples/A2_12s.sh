#!/bin/bash

# Write a shell script which takes as parameters a lowercase letter followed by several file names.
# The script will replace each digit with the letter given as a parameter in all given files.

# I check if there are any arguments
if [[ "$#" == 0 ]]; then
	echo "There are no argumets!"
	echo "The command should be like ${0} [lowercase_letter] [file]"
	exit 1
fi

# I check if there are any files specified
if [[ "$#" == 1 ]]; then
	echo "There are no files in the arguments!"
	echo "The command should be like ./script.sh [lowercase_letter] [file]"
	exit 1
fi

# I check if the input of the first argument is valid
if [[ "$1" != [a-z] ]]; then
	echo "The first argument $1 should be lowercase and a letter"
	exit 1
fi

# I assign the first argument to letter variable
letter="$1"

# I declare an empty array in which the files that can be edited will be stored
files=()

# I check if the files exist
for ((args=2; args<=$#; args++));
do

	if [[ -e "${!args}" && -f "${!args}" ]]; then
		files+=( ${!args} )


	else
		echo "File ${!args} does not exist!"
	fi 

done
 
# If the array files is empty it means that there aren't files that exist
if [[ "${#files[@]}" == 0 ]]; then
	echo "There aren't any files that exist, the program will stop!"
	exit 1
fi

# Listing the files to be edited
echo "There will be replacemnts done for the following files if there is anything to replace:"
for file in ${files[@]};

do
	echo "$file"
done

# Checking if you want to proceed so you can stop if something is wrong
read -p "Do you want to continue? (y/n): " answer

# Running the commands so the files will be edited
if [[ "$answer" == 'y' || "$answer" == 'Y' ]]; then
	for file in ${files[@]};
	do
		sed -i 's/[0-9]/'"$letter"'/g' $file 
	done
	echo "The files have been succesfully edited!"
	exit 0

else 
	echo "No changes have been made!"
	exit 0
fi

