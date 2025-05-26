#Write a shell script which takes as parameters several file names. 
#The script will display the number of files, the average number of words per file and the total word count.
#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 file1 [file2 ... fileN]"
  exit 1
fi

total_words=0
file_count=0

for file in "$@"; do
  if [ -f "$file" ]; then
    words_in_file=$(awk '{ total += NF } END { print total }' "$file")
    total_words=$((total_words + words_in_file))
    file_count=$((file_count + 1))
  else
    echo "Warning: '$file' is not a valid file."
  fi
done

if [ $file_count -eq 0 ]; then
  echo "No valid files provided."
  exit 2
fi

average_words=$((total_words / file_count))

echo "Number of files: $file_count"
echo "Total word count: $total_words"
echo "Average number of words per file: $average_words"
