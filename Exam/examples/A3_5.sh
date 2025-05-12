#!/bin/bash

for file in $@
do
	if [ -s $file ]
       	then
		awk 'length > 10 {sum++; print NR; print substr($0, 11)} END { print sum } ' $file
		echo $file
	fi
done
