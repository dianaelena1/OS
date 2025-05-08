
#!/bin/bash

# Write a Shell program that received as parameters two directory names
# and will copy the branch specified by the second directory to be a subbranch
# in the first directory, but it will copy only .txt files.

# I check if there are any arguments
if [[ "$#" == 0 ]]; then
        echo "There are no argumets!"
        echo "The command should be like ${0} [directory1] [directory2]"
        exit 1
fi

if [[ "$#" == 1 ]]; then
	echo "There is only one directory"
	echo "The command should be like ${0} [directory1] [directory2]"
	exit 1
fi

if [[ "$#" > 2 ]]; then
	echo "There are more arguments!"
	echo "The command should be like ${0} [directory1] [directory2]"
	exit 1
fi


# I check if the directories exist

directories=( "$@" )

for directory in ${directories[@]}

do
        if [[ ! -d "${directory}" ]]; then
                echo "The directory ${directory} doesn't exist!"
                exit 1
        fi
done

directories=( $(find $2 -type d) )

for directory in ${directories[@]}
do
	mkdir $1/$directory
done

files=( $(find $2 -type f | grep ".*\.txt$") )

for file in ${files[@]}
do
	cp ./$file $1/$file

done
