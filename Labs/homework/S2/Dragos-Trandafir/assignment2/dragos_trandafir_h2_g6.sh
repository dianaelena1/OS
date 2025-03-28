#!/bin/bash

# G6.Write a shell script which takes as parameters a short month name followed by a day number (ex: Mar 8). The script will display all user accounts that were connected to the server that day of month.

if [ $# -le 1 ]; then
  echo "Number of arguments is invalid, input 2 parameters"
else

month=$1  #gen the parameters
day=$2

if [ $day -lt 10 ]; then
  last | grep "${month}  ${day}"  # if we have a <10 day, shell will put 2 spaces
else [ $day -ge 10 ]
  last | grep "${month} ${day}"  # else, eg. 17, we will have only one space between the parameters when we search
fi

fi