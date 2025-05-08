#!/bin/bash
# Write a shell script which takes as parameters two file names (a file that contains usernames and a file that contains any text). 
# The script will send a mail to each user in the first file (the mail message will be the text in the second file).

if [ ! -f $1 ] && [ ! -f $2 ] 
then echo "One or both files doesn't exist"
exit 1
fi

IFS=""
while read line
do
 
  echo $(<"$2") | mail -s "Mail sent through command line" "$line"
  echo "mail sent to $line" 
  IFS=""
done < $1


