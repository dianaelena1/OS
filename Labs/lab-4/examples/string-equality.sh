# 5 Methods

#### 1. Use = Operator

#!/bin/bash

#Define two strings
string1="Linuxsimply"
string2="Linuxsimply"

#Print the declared strings
echo "Frist string: $string1"
echo "Second String: $string2"

# Check if string1 is equal to string2
if [ "$string1" = "$string2" ]; then
    echo "Strings are equal."
else
    echo "Strings are not equal."
fi



#### 2. Use == Operator

#!/bin/bash

#Define two strings
string1="Linuxsimply"
string2="Bash"

#Print the declared strings
echo "Frist string: $string1"
echo "Second String: $string2"
#Check the strings
if [ "$string1" == "$string2" ]; then
    echo "Strings are equal."
else
    echo "Strings are not equal."
fi



#### 3. Use != Operator

#!/bin/bash

#Define two strings
string1="Linux"
string2="linux"

#Print the declared strings
echo "Frist string: $string1"
echo "Second String: $string2"

#check the string's equality
if [ "$string1" != "$string2" ]; then
    echo "Strings are not Equal."
else
    echo "Strings are Equal."



#### 4. Use test Operator

#!/bin/bash

#Define two strings
string1="LinuxSimply"
string2="Linux"

#Print the declared strings
echo "Frist string: $string1"
echo "Second String: $string2"

#check two strings equality
if test "$string1" = "$string2"; then
    echo "Strings are equal."
else
    echo "Strings are not equal."
fi




#### 5. Use case Statement

#!/bin/bash

#!/bin/bash

#Define two strings
string1="Linux"
string2="LinuxSimply"

#Print the declared strings
echo "Frist string: $string1"
echo "Second String: $string2"

#Check the strings
case "$string1" in
    $string2)
        echo "Strings are equal"
    ;;
    *)
        echo "Strings are not equal."
    ;;
esac
