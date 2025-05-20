#!/bin/bash

# 1. Variables and User Input
echo "Enter your name:"
read name
echo "Enter your age:"
read age
echo "Hello $name! I am $age years old."
if [ $age -ge 18 ]; then
  echo "You are an adult."
else
  echo "You are a minor."
fi

# 2. Arithmetic Operations
echo "Enter first number:"
read num1
echo "Enter second number:"
read num2
echo "Sum: $((num1 + num2))"
echo "Difference: $((num1 - num2))"
echo "Product: $((num1 * num2))"
echo "Quotient: $((num1 / num2))"
echo "Modulo: $((num1 % num2))"

# 3. Positional Parameters
echo "Enter the filename:"
read filename
if [ -f "$filename" ]; then
  echo "Number of lines: $(wc -l < "$filename")"
  echo "Number of words: $(wc -w < "$filename")"
  echo "Number of characters: $(wc -c < "$filename")"
else
  echo "File does not exist."
fi

# 4. Conditional Statements
echo "Enter file/directory name:"
read entity
if [ -d "$entity" ]; then
  echo "$entity is a directory."
elif [ -f "$entity" ]; then
  echo "$entity is a regular file."
else
  echo "$entity is not accessible."
fi

# 5. Loops (For, While, Until)
echo "For Loop:"
for i in {1..10}; do echo $i; done

echo "While Loop:"
i=1
while [ $i -le 10 ]; do
  echo $i
  ((i++))
done

echo "Until Loop:"
i=1
until [ $i -gt 10 ]; do
  echo $i
  ((i++))
done

# 6. File Permissions
mkdir -p lab5_test
touch lab5_test/file.txt
chmod 444 lab5_test/file.txt
ls -l lab5_test

# 7. User and Group Management
sudo useradd labuser
sudo groupadd labgroup
sudo usermod -aG labgroup labuser
sudo mkdir /home/labuser_dir
sudo chown labuser:labgroup /home/labuser_dir
ls -ld /home/labuser_dir

# 8. Group Ownership and Permissions
sudo groupadd projectgroup
sudo useradd devuser
sudo usermod -aG projectgroup devuser
sudo mkdir -p /opt/shared_project
sudo chgrp projectgroup /opt/shared_project
sudo chmod 770 /opt/shared_project
ls -ld /opt/shared_project

# 9. File Ownership and Access Control
mkdir ~/secure-files
touch ~/secure-files/confidential.txt
sudo chown labuser ~/secure-files/confidential.txt
sudo chmod 700 ~/secure-files/confidential.txt
ls -l ~/secure-files

# 10. Bonus
# Archive a directory
echo "Enter directory to archive:"
read archive_dir
tar -czf archive.tar.gz "$archive_dir"
echo "Directory archived as archive.tar.gz"

# List and kill processes
echo "Listing running processes for current user:"
ps -u "$(whoami)"
echo "Enter PID to kill:"
read pid
kill "$pid"
echo "Process $pid terminated."

echo "All tasks completed successfully!"
