# Check if string is not empty
#!/bin/bash

my_string="Linuxsimply"

if [ -n "$my_string" ]; then
    echo "The string is not empty."
fi



# Check if string is empty
#!/bin/bash

my_string=""

if [ -z "$my_string" ]; then
    echo "The string is empty."
fi
