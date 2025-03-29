#Write a shell script which lists the content of the current directory. 
#The script will list the files as follows: sorted by file names, sorted by last modified date and sorted by file size.

# list files sorted by name
echo "Files sorted by name:"
ls -l | awk 'NR>1' | sort -k9

echo ""

# list files sorted by last modified date
echo "Files sorted by last modified date:"
ls -lt

echo ""

# list files sorted by size
echo "Files sorted by size:"
ls -lS
