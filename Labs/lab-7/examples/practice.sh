# 1. Write a bash script that reads filenames and checks for each file:
#    - How many words are in the first line?
#    - The total file size.
#    - Perform all required validations on the input data.

#!/bin/bash

# Check if at least one filename is provided as an argument
if [ $# -lt 1 ]; then
    echo "No filenames provided"
    exit 1
fi

# Iterate over all provided filenames
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "$file is not a valid file"
        continue
    fi
    
    # Get the word count in the first line
    words=$(head -n 1 "$file" | wc -w)
    
    # Get the file size in bytes
    size=$(wc -c < "$file")
    
    # Print the results
    echo "$file: First line words = $words, Size = $size bytes"
done

# 2. Write a bash script that receives filenames as command-line arguments and checks:
#    - How many words are in the first line?
#    - The total file size.
#    - Perform all required validations.

#!/bin/bash

# Check if at least one filename is provided as an argument
if [ $# -lt 1 ]; then
    echo "No filenames provided"
    exit 1
fi

# Iterate over all provided filenames
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "$file is not a valid file"
        continue
    fi
    
    # Get the word count in the first line
    words=$(head -n 1 "$file" | wc -w)
    
    # Get the file size in bytes
    size=$(wc -c < "$file")
    
    # Print the results
    echo "$file: First line words = $words, Size = $size bytes"
done

# 3. Write a shell script that receives a natural number N and generates N text files:
#    - The filenames will be of the form: file_X, where X = {1,2,…, N}.
#    - Each file will contain lines X to X+5 from /etc/passwd.

#!/bin/bash

# Check if exactly one argument is provided and if it is a number
if [ $# -ne 1 ] || ! [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "Please provide a valid natural number"
    exit 1
fi

# Loop from 1 to N and create the files
for (( i=1; i<=$1; i++ )); do
    filename="file_$i"
    
    # Create the file
    touch "$filename"
    
    # Extract lines from /etc/passwd and write them into the file
    sed -n "$i,$((i+5))p" /etc/passwd > "$filename"
    
    echo "Created $filename"
done

# 4. Calculate the average of all process IDs in the system per user.
#    - Retrieve all process IDs grouped by user.
#    - Compute the average PID per user.

#!/bin/bash

# Use ps to get the user and PID list, process with awk
ps -eo user,pid | awk '
{
    user_count[$1]++; 
    user_sum[$1] += $2;
} 
END {
    for (u in user_count) 
        print u, "Average PID:", user_sum[u] / user_count[u];
}'

# 5. Write a shell script that checks each command-line argument:
#    - If it’s a file, print its name, number of characters, and lines.
#    - If it’s a directory, print its name and count the number of files it contains (including subdirectories).

#!/bin/bash

# Iterate through all provided arguments
for item in "$@"; do
    if [ -f "$item" ]; then
        # If it's a file, count characters and lines
        chars=$(wc -c < "$item")
        lines=$(wc -l < "$item")
        echo "$item: $chars characters, $lines lines"
    elif [ -d "$item" ]; then
        # If it's a directory, count the number of files (including subdirectories)
        count=$(find "$item" -type f | wc -l)
        echo "$item: $count files"
    else
        echo "$item is neither a file nor a directory"
    fi
done

# 6. Write a script that receives triplets of command-line arguments (filename, word, number) and:
#    - Validates input data.
#    - Prints all lines in the filename that contain the word exactly K times.

#!/bin/bash

# Ensure arguments are provided in triplets
if (( $# % 3 != 0 )); then
    echo "Provide arguments in triplets: <filename> <word> <count>"
    exit 1
fi

# Process each triplet
while [ $# -gt 0 ]; do
    file=$1
    word=$2
    count=$3

    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "File $file does not exist"
    else
        # Use awk to find lines where the word appears exactly count times
        awk -v word="$word" -v count="$count" '{gsub(word, "&"); if (gsub(word, "&") == count) print}' "$file"
    fi

    shift 3
done


# 7. Write a script that:
#    - Finds all users in /etc/passwd.
#    - Creates a file with their username as the filename.
#    - Stores all IP addresses from which that user has logged in.

#!/bin/bash

# Iterate through each user in /etc/passwd
for user in $(cut -d: -f1 /etc/passwd); do
    # Create a file with the username
    touch "$user"
    
    # Use the last command to get login history and extract IP addresses
    last "$user" | awk '{print $3}' | grep -E "([0-9]{1,3}\.){3}[0-9]{1,3}" > "$user"
    
    echo "Created log file for $user"
done

# 8. Write a script that:
#    - Finds recursively in the current folder all the regular files that have write permissions for everybody (owner, group, other).
#    - Displays them.
#    - Removes write permissions from everybody.

#!/bin/bash

# Find all regular files with write permissions for everyone
files=$(find . -type f -perm -o=w)

# Check if any such files exist
if [ -z "$files" ]; then
    echo "No files found with write permissions for everyone."
else
    echo "Files with write permissions for everyone:"
    echo "$files"

    # Remove write permissions for others
    chmod o-w $files
    echo "Write permissions removed."
fi

# 9. Create a bash script that:
#    - Displays every second the process count per user, sorted in descending order by process count.
#    - If no arguments are given, displays results for all users.
#    - If usernames are provided, validates them before displaying results.

#!/bin/bash

# Function to get the process count per user
get_process_count() {
    ps -eo user= | sort | uniq -c | sort -nr
}

# Validate if provided usernames exist
valid_users=()
for user in "$@"; do
    if id "$user" &>/dev/null; then
        valid_users+=("$user")
    else
        echo "Invalid username: $user"
    fi
done

# Run in an infinite loop, updating every second
while true; do
    clear
    echo "Process count per user:"
    if [ ${#valid_users[@]} -eq 0 ]; then
        # No valid users provided, show all users
        get_process_count
    else
        # Show only for valid users
        for user in "${valid_users[@]}"; do
            count=$(ps -u "$user" | wc -l)
            echo "$user: $count"
        done | sort -nr -k2
    fi
    sleep 1
done


# 10. Write a shell script that:
#    - Receives any number of words as command-line arguments.
#    - Continuously reads from the keyboard one file name at a time.
#    - Ends when all words received as parameters have been found at least once across the given files.

#!/bin/bash

# Ensure at least one word is provided
if [ $# -lt 1 ]; then
    echo "Provide at least one search word."
    exit 1
fi

# Store words in an array
search_words=("$@")

# Create an array to track found words
found=()
for word in "${search_words[@]}"; do
    found["$word"]=0
done

# Function to check if all words have been found
all_found() {
    for word in "${search_words[@]}"; do
        if [ "${found[$word]}" -eq 0 ]; then
            return 1  # Not all words found
        fi
    done
    return 0  # All words found
}

# Read filenames until all words are found
while true; do
    read -p "Enter a file name: " filename

    # Check if the file exists
    if [ ! -f "$filename" ]; then
        echo "File does not exist."
        continue
    fi

    # Search for each word in the file
    for word in "${search_words[@]}"; do
        if grep -q -w "$word" "$filename"; then
            found["$word"]=1
        fi
    done

    # Check if all words have been found
    if all_found; then
        echo "All words found. Exiting."
        break
    fi
done
