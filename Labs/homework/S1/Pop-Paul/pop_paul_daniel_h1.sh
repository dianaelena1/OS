#!/bin/bash
#Write a shell script which displays all files in the current directory and its subdirectories that have write permission for the group of which the owner belongs.S
# Search for all files in the current directory and subdirectories
# that have write permission for the group of the owner.
# we execute ./pop_paul_daniel_h1.sh
#chmod g+w ____.txt togive write permision for a file
#chmod 000 ____.txt to delete any permision 
#ls -l ____.txt to check manually the prmision
#Owner | Group | Others permisions

# Create two files in the current directory
touch file_with_group_write.txt file_without_group_write.txt

# Give group write permission to one file
chmod 664 file_with_group_write.txt  # -rw-rw-r--

# Remove group write permission from the other file
chmod 644 file_without_group_write.txt  # -rw-r--r--

# Create a subdirectory
mkdir -p test_subdir

# Create two files inside the subdirectory
touch test_subdir/subfile_with_group_write.txt
touch test_subdir/subfile_without_group_write.txt

# Give group write permission to one file in the subdirectory
chmod 664 test_subdir/subfile_with_group_write.txt  # -rw-rw-r--

# Remove group write permission from the other file
chmod 644 test_subdir/subfile_without_group_write.txt  # -rw-r--r--

# Print a message
echo "Files and directory created successfully!"

echo "Files with group write permission for the owner's group:"

find . -type f -perm -020 -exec sh -c '
    for file; do     
        owner=$(stat -c "%U" "$file")   # Get file owner
        group=$(stat -c "%G" "$file")   # Get file group
        user_groups=$(id -Gn "$owner")  # Get all groups the owner belongs to

        if echo "$user_groups" | grep -qw "$group"; then    #check if the group is part of the groups the owner belongs to
            echo "$file"
        fi
    done
' sh {} +
