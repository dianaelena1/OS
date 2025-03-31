#!/bin/bash

# G6.Write a shell script which takes as parameters a short month name followed by a day number (ex: Mar 8). The script will display all user accounts that were connected to the server that day of month.

if [ $# -ne 2 ]; then
  echo "Number of arguments is invalid, input 2 parameters"
else

month=$1  
day=$2

if [ $day -lt 10 ]; then
  last | grep "${month}  ${day}"  
else 
  last | grep "${month} ${day}"  
fi

fi