#Write a shell script which lists the content of the current directory. 
#The script will list the files as follows: sorted by file names, sorted by last modified date and sorted by file size.


echo "Files sorted by name:"
ls -l | awk 'NR>1' | sort -k9

echo ""


echo "Files sorted by last modified date:"
ls -lt

echo ""


echo "Files sorted by size:"
ls -lS
