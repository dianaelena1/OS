#grep is used for pattern matching

# Check if file is empty
#!/bin/bash

file_name=example.txt

if ! grep -q . "${file_name}"; then
echo "'example.txt' is empty."
fi