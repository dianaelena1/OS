
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 directory1 [directory2 ...]"
    exit 1
fi

for dir in "$@"; do
    if [ ! -d "$dir" ]; then
        echo "Directory '$dir' not found. Skipping."
        continue
    fi


    find "$dir" -type f | while read -r file; do
        if file "$file" | grep -q "ASCII text"; then
            echo -e "\nFile: $file"
            head -n 5 "$file"
        fi
    done
done
