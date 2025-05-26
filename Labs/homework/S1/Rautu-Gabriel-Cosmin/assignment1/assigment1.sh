#!/bin/bash



if [[ $# -ne 2 ]]; then
  echo "Usage: $0 <int1> <int2>"
  exit 1
fi

int_re='^-?[0-9]+$'
if ! [[ $1 =~ $int_re && $2 =~ $int_re ]]; then
  echo "Error: both arguments must be integers."
  exit 1
fi

a=$1
b=$2

echo "Sum:        $(( a + b ))"
echo "Difference: $(( a - b ))"
echo "Product:    $(( a * b ))"
