#!/bin/bash

# Step 1: Create a file users.txt with some information
echo "Alice" > users.txt
echo "Bob" >> users.txt
echo "Charlie" >> users.txt
echo "David" >> users.txt

# Step 2: Use sort with stdin redirection
echo "Sorting contents of users.txt:"
sort < users.txt

# Step 3: Create the directory structure
mkdir -p dir1/dir1_1 dir1/dir1_2 dir1/dir1_3 dir2/dir2_1

# Step 4: Redirect ls output to stdout1.txt
ls -ls dir1 dir2 > stdout1.txt
echo "Contents of stdout1.txt:"
cat stdout1.txt

# Step 5: Use file descriptor 1 to redirect output
ls -l 1> list.txt

# Step 6: Append output to stdout1.txt
ls -ls dir1 dir2 >> stdout1.txt
ls -ls dir1 dir2 1>> stdout1.txt

# Step 7: Redirect error output to stderr1.txt
ls -ls /something 2> stderr1.txt

# Step 8: Append error output to stderr1.txt twice
ls -ls /something 2>> stderr1.txt
ls -ls /something 2>> stderr1.txt

# Step 9: Redirect stdout and stderr separately
ls -l dir1 dir2 /something 1> stdout1_1.txt 2> stderr1_1.txt

# Step 10: Redirect both stdout and stderr to the same file
ls -ls dir1 dir2 /something > output.txt 2>&1

# Step 11: Append both stdout and stderr to the same file twice
ls -ls dir1 dir2 /something >> output.txt 2>&1
ls -ls dir1 dir2 /something >> output.txt 2>&1

echo "Script execution completed!"
