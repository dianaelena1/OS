#!/bin/bash

file_name=emoji.txt

if [ -z "$(cat ${file_name})" ]; then
    echo "The file is empty."
fi