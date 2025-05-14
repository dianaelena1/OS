# First Option -  we use wc. With the help of pipe we send the output of the echo cmd as an input to the wc command

#!/bin/bash
arr=("hello" "world" "universe")
#print array
echo ${arr[@]}
#check if array is empty
result=`echo ${arr[@]} | wc -w`
if [ $result -gt 0 ]
then
   echo array Not empty
else
   echo array empty
fi

arr2=()
#print array
echo ${arr2[@]}

#check if array is empty
result=`echo ${arr2[@]} | wc -w`
if [ $result -gt 0 ]
then
   echo array Not empty
else
   echo array empty
fi


# Second Option -  we use grep, set the blank space as a pattern, and then count the occurences.
#!/bin/bash

arr=("hello" "world" "multiverse")
result=$(echo ${arr[@]} | grep -o " " | grep -c " ")
echo ${arr[@]}
#check if array is empty using grep command
if [ $result -gt 0 ]
then
   echo "Not empty"
else
    if [ ! -z "${arr[0]}" ]
        then
                echo "Not empty"
        else
                echo "empty"
        fi
fi