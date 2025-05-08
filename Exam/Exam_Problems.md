### A1_2.sh
# Write a shell script which takes as parameters two names of text files. The script will compare the two text files line by line and display the first 3 text lines that differ.

**Solution:**
```sh
#!/bin/bash

filepath="$1"
for file in "$filepath"/*; do
    if [ -f "$file" ] && [ "$(file -b --mime-type "$file")" = "text/plain" ]; then  #check if file and mime type text
        head -n 3 "$file"
        #display the first 3 lines
    fi
done
```

---

### A1_4_v2.sh
# Write a shell script that reads numbers from keyboard (the reading stops when the user has entered the number 0). The script will display the sum of numbers entered from the keyboard.

**Solution:**
```sh
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
```

---

### A1_4.sh
# Write a shell script which displays all files in the current directory and its subdirectories that
# have write permission for the group of which the owner belongs.

**Solution:**
```sh
#!/bin/bash

check_permission() {
    file="$1"
    if [ -w "$file" ]; then
        echo "$file"
    fi
}

traverse_dir() {
    directory="$1"
    for item in "$directory"/*; do
        if [ -d "$item" ]; then
            traverse_dir "$item"
        elif [ -f "$item" ]; then
            check_permission "$item"
        fi
    done
}
traverse_dir "$(pwd)"
```

---

### A1_2.sh

**Solution:**
```sh
#!/bin/bash

# Check if correct number of arguments provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 file1 file2"
    exit 1
fi

file1="$1"
file2="$2"

# Check if files exist
if [ ! -e "$file1" ] || [ ! -e "$file2" ]; then
    echo "Error: One or both files do not exist."
    exit 1
fi

# Compare files line by line until the end of either file or 3 differences are found
line_num=1
count=0
while IFS= read -r line1 && IFS= read -r line2 <&3; do
    if [ "$line1" != "$line2" ]; then
        echo "Line $line_num:"
        echo "$file1: $line1"
        echo "$file2: $line2"
        count=$((count+1))
        if [ "$count" -eq 3 ]; then
            break
        fi
    fi
    line_num=$((line_num+1))
done < "$file1" 3< "$file2"

# Display message based on number of differences found
if [ "$count" -eq 0 ]; then
    echo "No differences found."
elif [ "$count" -eq 1 ]; then
    echo "Only one difference found."
elif [ "$count" -eq 2 ]; then
    echo "Only two differences found."
fi
```

---

### A1_4.sh

**Solution:**
```sh
#!/bin/sh

echo "Enter the numbers"
suma=0

while true;
do
    read x
    if [ "$x" -eq 0 ];
    then
        break
    fi
    suma=$((suma+x))
done

echo "Suma: $suma"
```

---

### A1_4_v2.sh

echo "This is a scrip that will compute all the numbers given from the keyboard until 0 when the program stops and shows the result"

**Solution:**
```sh
#!/bin/bash
echo "This is a script that will compute all the numbers given from the keyboard until 0 when the program stops and shows the result"

read -p "Enter the first number: " number

if [[ -z "$number" ]]; then
	echo "Error: Number cannot be empty"
	exit 1
fi 

if [[ "$number" =~ ^[0-9]+$ ]]; then
	sum=$number
	i=2

else 
	echo "Error: Invalid number input"
	exit 1
fi

while [[ $number -ne 0 && "$number" =~ ^[0-9]+$ ]];

do
	
	read -p "Number $i: " number

	if [[ -z "$number" ]]; then
        	echo "Error: Number cannot be empty"
        	exit 1

	fi

	if [[ "$number" =~ ^[0-9]+$ ]]; then
	        sum=$((sum+number))
		let i+=1

	else
        	echo "Error: Invalid number input"
		exit 1

	fi
done

echo "The result is:" $sum
```

---

### A1_8.sh

**Solution:**
```sh
#!/bin/bash

if [ ! -f $1 ] && [ ! -f $2 ] 
then echo "One or both files doesn't exist"
exit 1
fi

IFS=""
while read line
do
 
  echo $(<"$2") | mail -s "Mail sent through command line" "$line"
  echo "mail sent to $line" 
  IFS=""
done < $1
```

---

### A2_10s.sh

**Solution:**
```sh
#!/bin/bash

# first we need to check if all arguments provided to program are valid
# file paths
for argument in $*
do
if !(test -r $argument)
then
echo "Argument $argument is not a valid file path"
exit 1
fi
done


# if all the arguments represent valid file paths, we iterate them again
# in each iteration we change the first word with the third one
# i chose this aproach because I wanted to be sure that the script does its job on all files, therefore the output will be consistent. Either all files are changed, or none

# I split the regular expression in 4 groups, the first is the separators from the beginning, the second is the first word, the third is composed by separators + word + separators and
#the last group is the third word.
for file in $*
do
sed 's/^\([^A-Za-z0-9]*\)\([A-Za-z0-9]\+\)\([^A-Za-z0-9]*[A-Za-z0-9]\+[^A-Za-z0-9]*\)\([A-Za-z0-9]\+\)/\1\4\3\2/' $file >  "$file modified"
done
```

---

### A2_12s.sh
# s12
# Write a shell script which takes as parameters a lowercase letter followed by several file names.
# The script will replace each digit with the letter given as a parameter in all given files.

**Solution:**
```sh
#!/bin/bash

# I check if there are any arguments
if [[ "$#" == 0 ]]; then
	echo "There are no argumets!"
	echo "The command should be like ${0} [lowercase_letter] [file]"
	exit 1
fi

# I check if there are any files specified
if [[ "$#" == 1 ]]; then
	echo "There are no files in the arguments!"
	echo "The command should be like ./script.sh [lowercase_letter] [file]"
	exit 1
fi

# I check if the input of the first argument is valid
if [[ "$1" != [a-z] ]]; then
	echo "The first argument $1 should be lowercase and a letter"
	exit 1
fi

# I assign the first argument to letter variable
letter="$1"

# I declare an empty array in which the files that can be edited will be stored
files=()

# I check if the files exist
for ((args=2; args<=$#; args++));
do

	if [[ -e "${!args}" && -f "${!args}" ]]; then
		files+=( ${!args} )


	else
		echo "File ${!args} does not exist!"
	fi 

done
 
# If the array files is empty it means that there aren't files that exist
if [[ "${#files[@]}" == 0 ]]; then
	echo "There aren't any files that exist, the program will stop!"
	exit 1
fi

# Listing the files to be edited
echo "There will be replacemnts done for the following files if there is anything to replace:"
for file in ${files[@]};

do
	echo "$file"
done

# Checking if you want to proceed so you can stop if something is wrong
read -p "Do you want to continue? (y/n): " answer

# Running the commands so the files will be edited
if [[ "$answer" == 'y' || "$answer" == 'Y' ]]; then
	for file in ${files[@]};
	do
		sed -i 's/[0-9]/'"$letter"'/g' $file 
	done
	echo "The files have been succesfully edited!"
	exit 0

else 
	echo "No changes have been made!"
	exit 0
fi
```

---

### A2_15g.sh

**Solution:**
```sh
#!/bin/bash

if [ $# -eq 0 ];
then
   echo "Usage: $0 file1 [file2 ...]"
   exit 1
fi

for file in "$@"; do
    grep -v '[[:upper:]]' "$file"
done
```

---

### A2_5s.sh

**Solution:**
```sh
#!/bin/bash

for file in "$@"; do
    if [ -f "$file" ]; then
        # Use sed to delete words containing at least one digit
        sed -i -E 's/\b[[:alpha:]]*[[:digit:]][[:alnum:]]*\b//g' "$file"
        echo "Words containing digits deleted from $file"
    else
        echo "File $file not found."
    fi
done
```

---

### A2_6s.sh

**Solution:**
```sh
#!/bin/bash

# first arg is letter -> validate lowercase
letter=$1 

# == for exact string comparison, =~ for pattern matching with regular expr
if ! [[ $letter =~ [a-z] ]];then
	echo "The first argument should be a lowercase letter!"	
fi

for file in "${@:2}"; do
	# check if the files exist  -f
	if [ ! -f "$file" ]; then
		echo "File $file not found!"
	fi

	# replace all that are not a-z, A-Z, or digits  /g globally
	# -i to use file in-place
	sed -i "s/[^a-zA-Z0-9]/$letter/g" "$file"
done
```

---

### A2_6s_v2.sh

**Solution:**
```sh
#!/bin/bash

# Check if the number of arguments is less than 2
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <lowercase_letter> <file1> [<file2> ...]"
    exit 1
fi

# Extract the lowercase letter from the first argument
letter="$1"

# Check if the first argument is a lowercase letter
if ! [[ "$letter" =~ ^[a-z]$ ]]; then
    echo "Error: First argument must be a lowercase letter."
    exit 1
fi

# Check if the lowercase letter is not a single character
if [ ${#letter} -ne 1 ]; then
    echo "Error: First argument must be a single lowercase letter."
    exit 1
fi

# Check if the remaining arguments are files
for file in "${@:2}"; do
    if [ ! -f "$file" ]; then
        echo "Error: '$file' is not a file."
        exit 1
    fi
done

# Shift to skip the first argument (the letter)
shift

# Loop through each file provided as argument
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist. Skipping..."
        continue
    fi

    # Perform the replacement
    sed -i "s/[^a-zA-Z0-9]/$letter/g" "$file"
    echo "Replaced special characters with '$letter' in file '$file'."
done
```

---

### A2_9s.sh

**Solution:**
```sh
#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Please input file names when using the script."
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi

	sed -i -E 's/\b([[:alnum:]]+)\b[[:space:]]+([[:alnum:]]+)\b([[:space:]]+[[:alnum:]]+\b)[[:space:]]+([[:alnum:]]+)\b/\1 \3/g' "$file"
echo "Words removed succesfully"
done
```

---

### A3_11.sh

# Write a shell script which takes as parameters several file names. The script will display the name of file which contains the highest number of words and the word count.

**Solution:**
```sh

#!/bin/bash

if [ $# -eq 0 ]; then
        echo "No files provided!"
	exit 1
fi

max_word_count=0
max_word_file=""


for filename in "$@"; do
	if [ ! -f "$filename" ];then
		echo "File $filename not found!"
        fi

	# count the number of words in the current file
	# awk to print the number of fields (words) in each line of the file. NF =  the nr of fields (words) in the current line
	# word_count=$(awk {print NF} $filename

	# wc = count nr lines/ words    -w = count nr of words   < filename  = where to count

	word_count=$(wc -w < "$filename")

	if [ "$word_count" -gt "$max_word_count" ]; then
        	max_word_count="$word_count"
        	max_word_file="$filename"
	fi
done


echo "File with the highest word count is $max_word_file"
echo "Word Count is $max_word_count"
```

---

### A3_12.sh


**Solution:**
```sh
#!/bin/bash

if [ "$#" -lt 3 ];
then
    echo "Usage: $0 <word_to_replace> <replacement_word> <file1> [<file2> ...]"
    exit 1
fi

word_to_replace=$1
replacement_word=$2
shift 2

for file in "$@"; do
    if [ ! -f "$file" ]; 
    then 
        echo "File '$file' not found. Skipping."
        continue
    fi

    sed  -i "s/$word_to_replace/$replacement_word/g" "$file"

    echo "Replaced occurrences of '$word_to_replace' with ' $replacement_word' in '$file'."
done
```

---

### A3_14.sh

**Solution:**
```sh
#!/bin/bash

if [[ $# -ne 1 || ! $1 =~ ^[0-2][0-9]:[0-5][0-9]-[0-2][0-9]:[0-5][0-9]$ ]]; then
  echo "Usage: $0 <hh:mm-hh:mm>" >&2
  exit 1
fi

start_time=$(echo "$1" | cut -d'-' -f1)
end_time=$(echo "$1" | cut -d'-' -f2)

start_timestamp=$(date -d "$start_time" +"%b %d %H:%M")
end_timestamp=$(date -d "$end_time" +"%b %d %H:%M")

last_output=$(last | awk -v start="$start_timestamp" -v end="$end_timestamp" '$5 " " $6 >= start && $5 " " $6 <= end')

num_users=$(echo "$last_output" | awk '{print $1}' | sort -u | wc -l)
num_sessions=$(echo "$last_output" | wc -l)

if [ "$num_sessions" -gt 0 ]; then
    average_users=$(echo "scale=2; $num_sessions / $num_users" | bc)
else
    average_users=0
fi


echo "Average number of users connected between $start_time and $end_time: $average_users"
```

---

### A3_3.sh

**Solution:**
```sh
#!/bin/bash

# Handle the case when no file is provided
if [ "$#" -eq 0 ]; then
    echo "Please enter at least one file."
    exit 1
fi

# Iterate through each file provided as argument
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "$file does not exist."
        continue
    fi

    awk '
         BEGIN {lower = 0; upper = 0}
         {
       	# $0 - current line
          for ( i = 1; i <= length($0); i++) {
		char = substr($0, i , 1) # saving each character
		if(char ~ /[a-z]/) lower++; #check if char is L/U case
		if(char ~ /[A-Z]/) upper++;
	  }
	}
	END {ratio = (lower "/" upper)
	print FILENAME " l/U = " ratio }' $file
done
```

---

### A3_5.sh

**Solution:**
```sh
#!/bin/bash
for file in $@
do
	if [ -s $file ]
       	then
		awk 'length > 10 {sum++; print NR; print substr($0, 11)} END { print sum } ' $file
		echo $file
	fi
done
```

---

### A3_6.sh

**Solution:**
```sh
#!/bin/bash

# Function to calculate average number of words per line in a file
average_words_per_line() {
    local file="$1"
    local total_lines=$(wc -l < "$file")
    local total_words=$(wc -w < "$file")
    if [ "$total_lines" -gt 0 ]; then
        echo "Average words per line in $file: $((total_words / total_lines))"
    else
        echo "File $file is empty."
    fi
}

# Initialize variables for total words and total files
total_words=0
total_files=0

# Iterate over each file passed as parameter
for file in "$@"; do
    if [ -f "$file" ]; then
        average_words_per_line "$file"
        total_words_in_file=$(wc -w < "$file")
        total_words=$((total_words + total_words_in_file))
        total_files=$((total_files + 1))
    else
        echo "File $file not found."
    fi
done

# Calculate and display average number of words per file
if [ "$total_files" -gt 0 ]; then
    echo "Average number of words per file: $((total_words / total_files))"
else
    echo "No valid files provided."
fi
```

---

### A3_6_v2.sh

# Write a shell script which takes as parameters several file names. 
# For each given file, the script will display its name and the average number of words per line.
# At the end, the script will display also the average number of words per file.

**Solution:**
```sh
#!/bin/bash

# I check if there are any arguments
if [[ "$#" == 0 ]]; then
	echo "There are no argumets!"
	echo "The command should be like ${0} [file]"
	exit 1
fi

# I check if the file/files exist/s

files=( "$@" )
good_files=()
for file in ${files[@]}
do	
	if [[ ! -f "${file}" ]]; then
		echo "File ${file} doesn't exist!"
		#exit 1
	else 
		good_files+=( ${file} )	
	fi 
done

# If the good_files is empty it means none of the argument was a good file.

if [[ "${#good_files[@]}" == 0 ]]; then
	echo "There aren't any valid files, the program will stop!"
	exit 1
fi

# words per file
declare -i wpf=0
for file in ${good_files[@]}
do	
	echo "File: $file"
	if [[ -s  $file ]]; then
	# the file is not empty	
		words=$(wc -w $file | cut -d " " -f1)
		#echo "$words"
		lines=$(wc -l $file | cut -d " " -f1)	
		#echo "$lines"
		#average word per line
		awpl=$(($words / $lines))
		echo "Average number of words per line: ${awpl}"
		wpf+=$words
		#echo "$wpf"
	else 
		echo "The file is empty"
	fi
		echo ""
done
#average words per file
awpf=$(($wpf / ${#good_files[@]}))
echo "Average words per files: $awpf"
```

---

### A4_11.sh

**Solution:**
```sh
#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Error: No parameters provided."
    exit 1
fi

directory="${@: -1}"

if [ ! -d "$directory" ]; then
        echo "Error: No directory provided."
        exit 1
fi


echo directory

for ((param=1;param<$#;param++));
 do

        if ! find ~/ -name "${!param}" -quit 2>/dev/null; then
    echo "Error: ${!param} does not exist."
    exit 1

	else 
        directories=$(find "$directory" -name "${!param}" -exec du -h {} +)

         # Sort directories based on file size (the size is the first column in the output of 'du -h')
         sorted_directories=$(echo "$directories" | sort -rh)
        # Output sorted directories
        echo "$sorted_directories"
         fi
done
```

---

### A4_12.sh


**Solution:**
```sh
#!/bin/bash

# Check if directory exists
if [ -d "$1" ]; then
    for file in $(find "$1" -type d); do
        echo "Directory: $file"
    done
    # List all files in directory and its subdirectories
    for file in $(find "$1" -type f); do
        echo "File: $file"
        # Print the maximum number of repeating lines
        sort "$file" | uniq -c | sort -nr | head -n 1
    done

else
    echo "Directory does not exist."
fi
```

---

### A4_12_v2.sh

**Solution:**
```sh
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
```

---

### A4_16.sh
# Write a Shell program that received as parameters two directory names
# and will copy the branch specified by the second directory to be a subbranch
# in the first directory, but it will copy only .txt files.

**Solution:**
```sh
#!/bin/bash

# I check if there are any arguments
if [[ "$#" == 0 ]]; then
        echo "There are no argumets!"
        echo "The command should be like ${0} [directory1] [directory2]"
        exit 1
fi

if [[ "$#" == 1 ]]; then
	echo "There is only one directory"
	echo "The command should be like ${0} [directory1] [directory2]"
	exit 1
fi

if [[ "$#" > 2 ]]; then
	echo "There are more arguments!"
	echo "The command should be like ${0} [directory1] [directory2]"
	exit 1
fi


# I check if the directories exist

directories=( "$@" )

for directory in ${directories[@]}

do
        if [[ ! -d "${directory}" ]]; then
                echo "The directory ${directory} doesn't exist!"
                exit 1
        fi
done

directories=( $(find $2 -type d) )

for directory in ${directories[@]}
do
	mkdir $1/$directory
done

files=( $(find $2 -type f | grep ".*\.txt$") )

for file in ${files[@]}
do
	cp ./$file $1/$file

done
```

---

### File: A4_4.sh

**Solution:**
```sh
#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory_name> <filename_list>"
    exit 1
fi

directory_name=$1
filename_list=$2

if [ ! -d "$directory_name" ]; then
    echo "Error: Directory '$directory_name' does not exist."
    exit 1
fi

if [ ! -f "$filename_list" ]; then
    echo "Error: File '$filename_list' does not exist."
    exit 1
fi

if [ -z "$(ls -A "$directory_name")" ]; then
    echo "Error: Directory '$directory_name' is empty."
    exit 1
fi

subdirectories=$(find "$directory_name" -mindepth 1 -type d 2>/dev/null)

while IFS= read -r subdirectory; do
    echo "Searching in directory: $subdirectory"
    if [ ! -r "$subdirectory" ]; then
        echo "Warning: No read permission for directory '$subdirectory'"
        continue
    fi
    while IFS= read -r filename; do
        if [ -e "$subdirectory/$filename" ]; then
            echo "File '$filename' found in subdirectory '$subdirectory'"
        fi
    done < "$filename_list"
done <<< "$subdirectories"
```

---

### A4_4_v2.sh

**Solution:**
```sh
#!/bin/bash

# directory name argument
dir_name=$1

# shifting to get to the other arguments which are all file names
shift
file_names=$@

for file_name in $file_names
do
    echo "File: $file_name"
    find $dir_name -name $file_name -exec dirname {} \; | while read line
    do
        ls -lt -- "$line" | awk -v file="$file_name" '$9 == file {printf "%s %s %s %s\n", $6, $7, $8, $line}'
    done | while read month day time dir
    do
        date=$(date -d"$month $day $time" +%s)
        echo $date $dir
    done | sort -nr | while read timestamp dir
    do
        date=$(date -d@$timestamp +"%b %d %T")
        echo $date $dir
    done
done
```

---

### A5_1.c

**Solution:**
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", argv[1]);
        return 1;
    }

    // Read and print the content of the file
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        printf("%s", line);
        printf("\n"); 
    }

    
    fclose(file);

    
    if (line)
        free(line);

    return 0;
}
```

---

### A5_1_v2.c

**Solution:**
```c
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "You have to pass the filename as an argument");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

  char c;
  char previous;

    while ((c = fgetc(file)) != EOF) {
        if (c != '\n') {
            printf("%c", c);
        } else {
            if (previous != '\n') { // Print an extra newline only if the line is not empty
                printf("\n\n");
        }
        }
        previous = c;
    }
    fclose(file);
    return 0;
}
```

---

### A5_10.c

**Solution:**
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    while ((read = getline(&line, &len, file)) != -1) 
    {
        size_t start = 0;
        while (start < read && (line[start] == ' ' || line[start] == '\t' || line[start] == '\n'))
        {
            start++;
        }

        size_t end = read - 1;
        while (end > start && (line[end] == ' ' || line[end] == '\t' || line[end] == '\n')) 
        {
            end--;
        }
        
        if (start <= end) 
        {
            for (size_t i = start; i <= end; i++) 
            {
                putchar(line[i]);
            }
            putchar('\n');
        }
    }

    if (ferror(file)) 
    {
        perror("Error reading file");
    }

    fclose(file);
    free(line);

    return 0;
}
```

---

###  A5_13.c

**Solution:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_line_without_words(char *line, int argc, char *argv[])
{
    char *word = strtok(line, " ");
    int word_printed = 0;
    while (word != NULL)
    {
        int i;
        for (i = 2; i < argc; i++)
        {
            if (strcmp(word, argv[i]) == 0)
            {
                break;
            }
        }
        if (i == argc)
        {
            if (word_printed)
                printf(" ");
            printf("%s", word);
            word_printed = 1;
        }
        word = strtok(NULL, " ");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename> <word1> <word2> ...\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
        print_line_without_words(line, argc, argv);

    fclose(file);
    if (line)
        free(line);

    return 0;
}
```

---

### A5_15.c

**Solution:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // For isalpha()

int main(int argc, char *argv[], char *env[]) {
    if (argc == 1) {
        printf("Error: Insufficient number of arguments.\nPlease enter the name of the file.\n");
        return 1;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Read the file line by line
    int i = 1;
    while ((read = getline(&line, &len, file)) != -1) {

        int count = 0;
        for (int i = 0; i < read; i++) {
            if (isalpha(line[i])) { // Check if the character is a letter
                count++;
            }
        }
        printf("Number of letters in line %d: %d\n", i, count);
        i++;
    }

    // Clean up: free the allocated buffer and close the file
    free(line);
    fclose(file);

    return 0;
}
```

---

### A5_15_v2.c

**Solution:**
```c
#include <stdio.h>

int main(int args) {
    FILE* ptr;
    char ch;
    int count = 0;

    ptr = fopen("latin.txt", "r");

    if (ptr == NULL) {
        printf("file cannot be opened.\n");
        return 1;
    }

    printf("letter count on each line from file:\n");

    while ((ch = fgetc(ptr))) {
        if (ch != '\n') {
            if (ch != ' ') {
                count++;
            }
        } else {
            printf("%d\n", count);
            count = 0;
        }
    }

    fclose(ptr);
    return 0;
}
```

---

### A5_5.c


**Solution:**
```c
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]){

    if (argc != 4)
    {
        printf("Error: Insufficient number of arguments.\n");
        printf("Usage: tema5 file_name word1 word2\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        return 2;
    }

    char word1[100], word2[100];
    strcpy(word1, argv[2]);
    strcpy(word2, argv[3]);

    char buffer[100];


    // read the entire file and replace word1 with word2
    while (fscanf(file, "%s", buffer) != EOF)
    {
        if (strcmp(buffer, word1) == 0)
        {
            printf("%s ", word2);
        }
        else
        {
            printf("%s ", buffer);
        }
    }

    fclose(file);


    return 0;
}
```

---

### A6_10.c

**Solution:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARRAY_SIZE 10

char* delete_vowel(char array[], char vowel) {
    int i, j;
    char *result = (char *)malloc(ARRAY_SIZE * sizeof(char));
    for (i = 0, j = 0; array[i] != '\0'; i++) {
        if (array[i] != vowel) {
            result[j++] = array[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char array[ARRAY_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    int num_vowels = sizeof(vowels) / sizeof(vowels[0]);

    // Create separate processes for each vowel deletion
    for (int i = 0; i < num_vowels; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char *result = delete_vowel(array, vowels[i]);
            printf("Process for vowel '%c' completed. Array: %s\n", vowels[i], result);
            strcpy(array, result); // Assign the modified array back to the original array
            free(result); // Free the memory allocated for the result
            exit(0);
        } else if (pid < 0) {
            // Error handling
            perror("fork");
            exit(1);
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < num_vowels; i++) {
        wait(NULL);
    }

    return 0;
}
```

---

### File: A6_12.c

**Problem:**
# Compute the sum of an array of numbers using divide et impera method: a process splits the array in two sub-arrays and gives them to two other child processes to compute their sums, then adds the results obtained. The child processes use the same technique (split, etc.

**Solution:**
```c

#include <stdio.h>
#include <stdlib.h>

//functie pt a calcula suma din array cu divide et impera
int sumaArray(int arr[], int start, int end) {
    if (start == end) {
        return arr[start];
    } else {
        int mid = (start + end) / 2;
        //impartim array-ul in 2 parti si calculam suma recursiv pt fiecare parte 
        int leftSum = sumArray(arr, start, mid);
        int rightSum = sumArray(arr, mid + 1, end);
        // returnam suma totala a array-ului
        return leftSum + rightSum;
    }
}

int main() {
    int n;
    printf("enter the nr of elements in the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("memory allocation failed\n");
        return 1;
    }

    printf("enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int arraySum = sumaArray(arr, 0, n - 1);
    printf("sum of the array elements: %d\n", arraySum);

    free(arr);
    return 0;
}
```

---

### A6_13.c

**Solution:**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int arrayProduct(int arr[], int start, int end) {
    if (start == end) {
        // cand nu are decat unelement arrrayu
        return arr[start];
    } else {
        int mid = (start + end) / 2;

        int leftChild = fork();

        if (leftChild == 0) {
            int leftProduct = arrayProduct(arr, start, mid);
            _exit(leftProduct); // dai exit cu valorea produsului
        } else if (leftChild > 0) {
            // in parinte
            int rightChild = fork();
            if (rightChild == 0) {
                int rightProduct = arrayProduct(arr, mid + 1, end);
                _exit(rightProduct); 
            } else if (rightChild < 0) {
                perror("fork");
                return -1;
            }

            int leftProduct, rightProduct;
            waitpid(leftChild, &leftProduct, 0);
            waitpid(rightChild, &rightProduct, 0);

            return WEXITSTATUS(leftProduct) * WEXITSTATUS(rightProduct);
        } else {
            perror("fork");
            return -1;
        }
    }
}

int main() {
    int arr[] = {1, 2, 3,5};

    int n = sizeof(arr) / sizeof(arr[0]);

    int product = arrayProduct(arr, 0, n - 1);

    printf("Product of the array: %d\n", product);

    return 0;
}
```

---

### A6_3.c

**Solution:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int findMin(int arr[], int start, int end) {
    int min = arr[start];
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int findMax(int arr[], int start, int end) {
    int max = arr[start];
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int countLessThanOrEqual(int arr[], int n, int val) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] <= val) {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <k>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int k = atoi(argv[2]);
    int arr[100];

    int count = 0;
    
    while (fscanf(file, "%d", &arr[count]) == 1) {
        count++;
    }
    fclose(file);

    pid_t pid_min, pid_max;
    pid_min = fork();

    if (pid_min < 0) {
        perror("Error forking");
        return 1;
    } else if (pid_min == 0) {
        int min = findMin(arr, 0, count - 1);
        printf("Minimum value: %d\n", min);
        exit(0);
    } else {
        pid_max = fork();
        if (pid_max < 0) {
            perror("Error forking");
            return 1;
        } else if (pid_max == 0) {
            int max = findMax(arr, 0, count - 1);
            printf("Maximum value: %d\n", max);
            exit(0);
        } else {
            int status;
            waitpid(pid_min, &status, 0);
            waitpid(pid_max, &status, 0);

            int min = findMin(arr, 0, count - 1);
            int max = findMax(arr, 0, count - 1);
            int range = max - min + 1;
            int freq[range];
            for (int i = 0; i < range; i++) {
                freq[i] = 0;
            }
            for (int i = 0; i < count; i++) {
                freq[arr[i] - min]++;
            }
            int numLessThanOrEqual = 0;
            int kthSmallest = -1;
            for (int i = 0; i < range; i++) {
                numLessThanOrEqual += freq[i];
                if (numLessThanOrEqual >= k) {
                    kthSmallest = i + min;
                    break;
                }
            }
            printf("Kth smallest element: %d\n", kthSmallest);
        }
    }

    return 0;
}
```

---

### A6_9.c

**Solution:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#define N 5

int main() {

    int x[N] = {1, 2, 3, 4, 5};
   
    int *S = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (S == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    pid_t pids[N];

    void compute_partial_sum(int i) {
        int sum = 0;
        for (int j = 0; j <= i; j++) {
            sum += x[j];
        }
        S[i] = sum;
    }

    for (int i = 0; i < N; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            exit(1);
        } else if (pids[i] == 0) {
            compute_partial_sum(i);
	    munmap(S, N * sizeof(int));
            exit(0);
        }
    }

    for (int i = 0; i < N; i++) {
        waitpid(pids[i], NULL, 0);
    }

    printf("Partial sums: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", S[i]);
    }
    printf("\n");
   munmap(S, N * sizeof(int));
    return 0;
}
```

---
