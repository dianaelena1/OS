#Write a shell script that takes a file name as an argument. the script will display all the lines from that file that 
#contain at least one digit

if [ $# -ne 1 ]; then
    echo "Usage: $0 file"
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "The file doesn't exist"
    exit 1
fi

for file in "$1"; do
    if [ -f "$file" ]; then
        grep -E '[[:digit:]]'  "$file"
    else
        echo "File $file not found."
    fi
done