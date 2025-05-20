# Multiple options within a single line
#!/bin/bash

file_name="example.txt"

if [ -e "$file_name" ] 
&& [ -f "$file_name" ]; 
then
    echo "The file '$file_name' exists and is a regular file."
fi

