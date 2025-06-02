#Square of numbers entered before 1

#!/bin/bash
echo "Introduce numbers:"


while true;
do
    square=0
    read x
    if [ "$x" -eq 1 ];
    then
        break
    else 
    square= x*x
    echo "Square: $square"
    fi
done

