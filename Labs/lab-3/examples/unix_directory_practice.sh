#!/bin/bash

# Step 1: Create a new directory called lab_2 in the home directory
mkdir -p ~/lab_2

# Step 2: Create dir1 inside lab_2
mkdir -p ~/lab_2/dir1

# Step 3: Navigate to dir1
cd ~/lab_2/dir1

# Step 4: From dir1, go back to lab_2 in one command
cd ~/lab_2

# Step 5: Create directory dir1_1 inside dir1 in one line
mkdir -p dir1/dir1_1

# Step 6: Try to create dir2/dir2_1 in one line without -p
mkdir dir2/dir2_1 2>/dev/null || echo "mkdir dir2/dir2_1 failed because dir2 does not exist."

# Step 7: Create dir2/dir2_1 correctly using -p
mkdir -p dir2/dir2_1

# Step 8: Display directory structure
echo "Directory structure of lab_2:"
ls -R ~/lab_2

echo "Unix directory practice script completed!"
