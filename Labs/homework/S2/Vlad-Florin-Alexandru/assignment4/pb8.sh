#|8|A C++ program is given. Determine for each class defined in the program the number of instances where new objects are being created,
# printing the line numbers.|

#!/bin/bash


file="program.cpp"

for class in $(grep -E '^\s*class\s+\w+' "$file" \
                | awk '{print $2}' \
                | tr -d '{'); do

  echo "Class: $class"
  
  grep -n "new $class" "$file"
  
  grep -n -E "\b$class\s+\w+" "$file" \
    | grep -v "^\s*class\s\+$class"
  
  echo
done
