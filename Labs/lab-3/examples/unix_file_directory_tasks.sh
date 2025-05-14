#!/bin/bash

# Verify structure using ls
echo "Verifying structure using ls:"
ls -R ~/lab_2

# Try tree command; install if necessary
if ! command -v tree &> /dev/null; then
    echo "tree command not found. Installing..."
    sudo apt-get install tree -y || sudo yum install tree -y
fi

# Show tree structure
echo "Displaying tree structure of lab_2:"
tree ~/lab_2

# Create directories with different permissions
echo "Creating directories with specific permissions..."
mkdir -m 000 ~/lab_2/dir3
mkdir -m 777 ~/lab_2/dir4

# List directories with permissions
echo "Listing directories with permissions:"
ls -ld ~/lab_2/dir3 ~/lab_2/dir4

# Try entering dir3 (should fail)
echo "Trying to enter dir3:"
cd ~/lab_2/dir3 2>/dev/null || echo "Permission denied for dir3"

# Create file1.txt in dir1
echo "Creating file1.txt in dir1..."
touch ~/lab_2/dir1/file1.txt

# Add text using cat
echo "Adding text to file1.txt..."
echo "This is file1 content" | cat > ~/lab_2/dir1/file1.txt

# Display content of file1.txt
echo "Content of file1.txt:"
cat ~/lab_2/dir1/file1.txt
