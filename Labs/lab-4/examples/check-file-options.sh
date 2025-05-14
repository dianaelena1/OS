
# Check if file is empty
#!/bin/bash

file_path="/home/xdianaelena1/color.txt"
if [ ! -s "$file_path" ]; then
    echo "The file 'color.txt' is empty."
fi



# Check if is regular file
#!/bin/bash

if [ -f "linux.txt" ]; then
    echo "The file 'linux.txt' exists."
fi



# Check existence of a file
#!/bin/bash

file_path="/home/xdianaelena1/Documents/notice.txt" #Providing information in /path/to/file_name

if [ -e "$file_path" ]; then
    echo "'notice.txt' exists"
fi


# Check path exists and is a directory
#!/bin/bash

directory_path="/home/xdianaelena1/Desktop/Bash global variable" #Providing information in /path/to/directory

if [ -d "$directory_path" ]; then
    echo "The directory exists."
fi


# Checks file has read permission, otherwise set it with chmod
#!/bin/bash

file_name="color.txt"

#Checking if the file has read access
if [ -r "$file_name" ]; then
    echo "The file '$file_name' is readable."
fi


# Checks file has write permission, otherwise set it with chmod
#!/bin/bash

file_path="/home/nadiba/Pictures/animal.txt" #Providing information in /path/to/file_name

#Checking if the file has write access
if [ -w "$file_path" ]; then
    echo "The file 'animal.txt' is writable."
fi


# Checks file has executable permission, otherwise set it with chmod
#!/bin/bash

file_name="argument.sh"

#Checking if the file has execute permission
if [ -x "$file_name" ]; then
    echo "The file '$file_name' is executable."
fi