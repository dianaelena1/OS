#!/bin/bash

dir=${!#}

for ((i=1; i<$#; i++)); do
    file=${!i}
    echo "$file:"

	find "$dir" -type f -name "$file" -exec stat -c"%s %n" {} \; | sort -nr | awk '{print $2, "(" $1 " bytes)"}'

    echo
done
