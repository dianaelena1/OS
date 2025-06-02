#Write a shell script that takes one or more tedxt file names as parameteres. The script will delete the second word from each line of the specified files.
#Assume each line has at least two words. It is assumed that words contain only letters or numbers and are separated by spaces

if [ "$#" -lt 2 ];
then
    echo "Usage: $0 [<file1> <file2> ...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; 
    then 
        echo "File '$file' not found. Skipping."
        continue
    fi

    sed -r -i 's/(\w+\s+)\w+\s+(.*)/\1\2/' "$file"
    echo "Deleted the second word in '$file'."
done