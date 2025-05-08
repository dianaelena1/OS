#!/bin/bash

# Write a shell script which takes as parameters several file names. 
# For each given file, the script will display its name and the average number of words per line.
# At the end, the script will display also the average number of words per file.

# I check if there are any arguments
if [[ "$#" == 0 ]]; then
	echo "There are no argumets!"
	echo "The command should be like ${0} [file]"
	exit 1
fi

# I check if the file/files exist/s

files=( "$@" )
good_files=()
for file in ${files[@]}
do	
	if [[ ! -f "${file}" ]]; then
		echo "File ${file} doesn't exist!"
		#exit 1
	else 
		good_files+=( ${file} )	
	fi 
done

# If the good_files is empty it means none of the argument was a good file.

if [[ "${#good_files[@]}" == 0 ]]; then
	echo "There aren't any valid files, the program will stop!"
	exit 1
fi

# words per file
declare -i wpf=0
for file in ${good_files[@]}
do	
	echo "File: $file"
	if [[ -s  $file ]]; then
	# the file is not empty	
		words=$(wc -w $file | cut -d " " -f1)
		#echo "$words"
		lines=$(wc -l $file | cut -d " " -f1)	
		#echo "$lines"
		#average word per line
		awpl=$(($words / $lines))
		echo "Average number of words per line: ${awpl}"
		wpf+=$words
		#echo "$wpf"
	else 
		echo "The file is empty"
	fi
		echo ""
done
#average words per file
awpf=$(($wpf / ${#good_files[@]}))
echo "Average words per files: $awpf"
