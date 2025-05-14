#!/bin/bash

# Navigate to root folder
cd ..

# List files with detailed information
ls -ls

# Store the output of pwd after navigating to the home directory
cd ~
home_directory=$(pwd)
echo "After cd ~, you are in: $home_directory"

# Store the output of pwd after navigating to the root directory
cd /
root_directory=$(pwd)
echo "After cd /, you are in: $root_directory"

# List files with detailed information
ls -ls

# Execute multiple commands and store results
cd ~
home_content=$(ls)
bin_root_content=$(ls /bin)
bin_relative_content=$(ls bin)

echo "Content of home directory: $home_content"
echo "Content of /bin directory: $bin_root_content"
echo "Content of bin in current directory (if exists): $bin_relative_content"
