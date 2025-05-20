#!/bin/bash

# array creation
cards=()


# check if array is empty
if [ ${#cards[@]} -eq 0 ]; then   # gives the number of elements in the array
    echo "The array is empty!"
else
    echo "The array is not empty"

fi


# #!/bin/bash

# arr=("hello" "world")

# if [ ${#arr[*]} -gt 0 ]   # gives the number of elements in the array
# then
#     echo "array Not empty"
# else
#     echo "array empty"
# fi
