
echo "Enter the numbers"
square=0
numbers=()
while true;
do
    read x
    numbers+=("$x")
    if [ "$x" -eq 1 ];
    then
        break
    fi
done

for num in "${numbers[@]}"; do
    square=$((num*num))
    echo "Square of $num is $square"
done
