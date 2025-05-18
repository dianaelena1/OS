#!/bin/bash

# echo "Searching for words with 's...r':"
# grep 's...r' fruits.txt  # Matches words starting with 's', 3 characters, then 'r'

# echo "Listing .txt files:"
# ls -lh | grep '\.txt'  # Ensures the dot is treated literally

# echo "Lines starting with 'c':"
# grep '^c' fruits.txt

# echo "Lines starting with 'c' or 'h':"
# grep '^[ch]' fruits.txt  

# echo "Lines NOT starting with 'c' or 'h':"
# grep '^[^ch]' fruits.txt  # Excludes lines starting with 'c' or 'h'

# echo "Lines ending with 'ies':"
# grep 'ies$' fruits.txt

# echo "Lines cotaining character 'u' any number of times:"
# grep 'colou*r' fruits.txt

# echo "Lines cotaining character 'u' limited number of times:" # EXTENDED REGULAR EXPRESSION
# grep -E 'colou?r' fruits.txt   # ? Returns only zero or one occurences, that’s why colouuur is not returned!

# echo "Lines cotaining cheese or salsa" # not original, but EXTENDED REGULAR EXPRESSION
# grep -E 'cheese|salsa'

#grep is used for pattern matching

# Check if file is empty
#!/bin/bash

# file_name=example.txt

# if ! grep -q . "${file_name}"; then
# echo "'example.txt' is empty."
# fi



#!/bin/bash

if [ -z "$1" ]; then
    echo "No parameters given"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "Parameter is not a folder"
    exit 1
fi










