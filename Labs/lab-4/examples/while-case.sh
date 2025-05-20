#!/bin/bash

while getopts ":ab" opt; do
    case ${opt} in
    a)
        echo "Option -a is triggered."
        ;;
    b)
        echo "Option -b is triggered."
        ;;
    ?)
        echo "Invalid option: -${OPTARG}."
        exit 1
        ;;
    esac
done