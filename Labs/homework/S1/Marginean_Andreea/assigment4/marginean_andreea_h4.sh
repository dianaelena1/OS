# A C++ program is given. Determine for each class defined in the program the number of 
# instances where new objects are being created, printing the line numbers.

#!/bin/bash
file="$1"

if [[ ! -f "$file" ]]; then
    echo "File $file not found!"
    exit 1
fi

class_names=$(grep -E '^\s*class\s+[A-Za-z_][A-Za-z0-9_]*' "$file" | sed -E 's/^\s*class\s+([A-Za-z_][A-Za-z0-9_]*).*/\1/')

for class in $class_names; do
    echo "Searching for instances of class: $class"
    
    new_instances=$(grep -nE "new\s+$class\b" "$file")
   
    stack_instances=$(grep -nE "\s$class\s+[A-Za-z_][A-Za-z0-9_]*\s*(\([^)]*\))?\s*;" "$file")
    
    all_instances="$new_instances"$'\n'"$stack_instances"

    instance_count=$(echo "$all_instances" | wc -l)

    if [[ "$instance_count" -gt 0 ]]; then
        echo "Found $instance_count instance(s) of class $class at lines:"
        echo "$all_instances" | sort -n
    else
        echo "No instances found for class $class."
    fi

    echo
done



