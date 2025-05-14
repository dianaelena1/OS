# Count number of bytes of a file with word count and c flag for bytes
#!/bin/bash

file_name=emoji.txt

#Checking if file has any lines
if [ $(wc -c < "${file_name}") -eq 0 ]; then
    echo "'$file_name' is empty."
fi