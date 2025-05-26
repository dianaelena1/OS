
if [ $# -ne 1 ]; then
    echo "Usage: $0 directory_name"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "$1 is not a directory"
    exit 1
fi

for file in "$1"/*; 
do
    if [ -f "$file" ] && [ "$(file -b --mime-type "$file")" = "text/plain" ]; then
        echo "Filename: $file"
        head -n 3 "$file"
        echo
    fi
done
