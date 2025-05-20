#!/bin/bash

# Step 13: Try to create a directory inside test_user1_1 home directory
echo "Attempting to create testdir in /home/test_user1_1 (should fail)..."
sudo -u test_user1_2 mkdir /home/test_user1_1/testdir 2>/dev/null || echo "Permission denied."

# Step 14: Modify group permissions to allow writing
echo "Modifying group write permissions for /home/test_user1_1..."
sudo chmod g+w /home/test_user1_1
ls -ld /home/test_user1_1

# Step 15: Try again to create the directory (should succeed)
echo "Attempting again to create testdir in /home/test_user1_1 (should work now)..."
sudo -u test_user1_2 mkdir /home/test_user1_1/testdir
ls -l /home/test_user1_1

# Step 16: Attempt to access test_user1_1's home from test_user2 (should fail)
echo "Trying to access /home/test_user1_1 from test_user2..."
sudo -u test_user2 ls /home/test_user1_1 2>/dev/null || echo "Access denied for test_user2."

# Step 17: Change permissions to allow others to read & execute (774)
echo "Changing permissions for /home/test_user1_1 to 774..."
sudo chmod 774 /home/test_user1_1

# Step 18: Change permissions to fully open access (777)
echo "Changing permissions for /home/test_user1_1 to 777..."
sudo chmod 777 /home/test_user1_1

# Verify test_user2 can now access
echo "Checking if test_user2 can now access and create files..."
sudo -u test_user2 ls /home/test_user1_1
sudo -u test_user2 mkdir /home/test_user1_1/testdir2

# Step 19: Remove test_user1_2 from group1
echo "Removing test_user1_2 from group1..."
sudo gpasswd -d test_user1_2 group1

# Step 20: Test access again as test_user1_2
echo "Testing access to /home/test_user1_1 as test_user1_2..."
sudo -u test_user1_2 ls /home/test_user1_1 2>/dev/null || echo "Access denied."

# Step 21: Delete test_user2 and remove home directory
echo "Deleting test_user2 and its home directory..."
sudo deluser --remove-home test_user2

# Verify user removal
ls /home | grep test_user2 || echo "test_user2 home removed successfully."

echo "Script execution completed!"
