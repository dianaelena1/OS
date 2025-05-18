#!/bin/bash

# Step 1: Create three new users
echo "Creating users test_user1_1, test_user1_2, and test_user2..."
sudo adduser test_user1_1
sudo adduser test_user1_2
sudo adduser test_user2

# Step 2: Check groups of new users and current user
echo "Checking groups of users..."
cat /etc/group
groups $USER
id test_user1_1
id test_user1_2
id test_user2

# Step 3: Create two new groups
echo "Creating new groups group1 and group2..."
sudo groupadd group1
sudo groupadd group2

# Verify groups exist
getent group group1
getent group group2

# Step 4: Add users to groups
echo "Adding users to groups..."
sudo usermod -aG group1 test_user1_1
sudo usermod -aG group1 test_user1_2
sudo usermod -aG group2 test_user2

# Verify users in groups
getent group group1
getent group group2

# Step 5: Open three terminals 

# Step 6: Try to create a user from test_user1_1 (should fail)

# Step 7: Add test_user1_1 to sudo group
echo "Adding test_user1_1 to sudo group..."
sudo usermod -aG sudo test_user1_1

# Step 8: Log out test_user1_1 and log in again
su your_user
su test_user1_1

# Step 9: Create lab_3 folder in test_user1_1 home directory
echo "Creating folder lab_3 in test_user1_1 home directory..."
sudo -u test_user1_1 mkdir /home/test_user1_1/lab_3

# Step 10: Try accessing home directory of test_user1_1 as test_user1_2 (should fail)
su test_user1_2
cd -

# Step 11: Change group ownership of test_user1_1 home folder to group1
echo "Changing group of test_user1_1 home folder to group1..."
sudo chgrp group1 /home/test_user1_1

# Step 12: Try accessing test_user1_1 home directory again (should work)

# Step 13: Change ownership of lab_3 with recursive flag
echo "Changing ownership of lab_3 recursively..."
sudo chgrp -R group1 /home/test_user1_1/lab_3

# Verify permissions
ls -ld /home/test_user1_1
ls -ld /home/test_user1_1/lab_3

echo "User management script execution completed!"
