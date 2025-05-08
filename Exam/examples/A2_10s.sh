#!/bin/bash

# first we need to check if all arguments provided to program are valid
# file paths
for argument in $*
do
if !(test -r $argument)
then
echo "Argument $argument is not a valid file path"
exit 1
fi
done


# if all the arguments represent valid file paths, we iterate them again
# in each iteration we change the first word with the third one
# i chose this aproach because I wanted to be sure that the script does its job on all files, therefore the output will be consistent. Either all files are changed, or none

# I split the regular expression in 4 groups, the first is the separators from the beginning, the second is the first word, the third is composed by separators + word + separators and
#the last group is the third word.
for file in $*
do
sed 's/^\([^A-Za-z0-9]*\)\([A-Za-z0-9]\+\)\([^A-Za-z0-9]*[A-Za-z0-9]\+[^A-Za-z0-9]*\)\([A-Za-z0-9]\+\)/\1\4\3\2/' $file >  "$file modified"
done