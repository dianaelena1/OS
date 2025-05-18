#!/bin/bash

# Navigate to dir1
cd ~/lab_2/dir1

# Open file1.txt using vi, vim, joe, emacs, and nano
echo "Try opening file1.txt with different text editors."

# Create file1.txt if it doesn't exist
touch file1.txt

# Open with vi (manual action required)
echo "Opening file1.txt with vi. Press INS to edit, ESC to finish, :w to save, :q to quit."
vi file1.txt

# Open with vim (same as vi)
echo "Opening file1.txt with vim."
vim file1.txt

# Open with joe (install if missing)
if ! command -v joe &> /dev/null; then
    echo "joe editor not found. Installing..."
    sudo apt-get install joe -y
fi
echo "Opening file1.txt with joe (exit with Ctrl+C)."
joe file1.txt

# Open with emacs (install if missing)
if ! command -v emacs &> /dev/null; then
    echo "emacs not found. Installing..."
    sudo apt-get install emacs -y
fi
echo "Opening file1.txt with emacs."
emacs file1.txt

# Open with nano
echo "Opening file1.txt with nano (exit with Ctrl+X)."
nano file1.txt

# Navigate to lab_2 and create multiple directories in one command
cd ~/lab_2
mkdir dir5 dir6 dir7

# Create files inside each directory
touch dir5/dir5_file1.txt dir6/dir6_file1.txt dir7/dir7_file1.txt

# Copy dir5_file1.txt to dir6 without renaming
cp dir5/dir5_file1.txt dir6/

# Move dir6_file1.txt to dir7 without renaming
mv dir6/dir6_file1.txt dir7/

# Move dir5_file1.txt to dir6 with a new name
mv dir5/dir5_file1.txt dir6/dir5indir6_file.txt

# Display directory structure
echo "Displaying the directory structure:"
tree ~/lab_2

# Remove directories dir5 and dir6
rmdir ~/lab_2/dir5
rm -r ~/lab_2/dir6

echo "Script execution completed!"
