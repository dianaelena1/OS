#!/bin/bash
# Given Pi a process that checks if i is a divisor of a number N given, and determines the multiplicity order of this divisor. 
# Launch a suitable structure of such processes to decompose the number N given in prime factors.

read -p "Enter a number N: " N
num=$N

tmpfile=$(mktemp)

factorize() {
  local i=$1
  local count=0
  while (( num % i == 0 )); do
    ((count++))
    num=$((num / i))
  done
  if (( count > 0 )); then
    echo "$i $count" >> "$tmpfile"
  fi
}

export -f factorize
export num tmpfile

for ((i = 2; i <= N / 2; i++)); do
  bash -c "factorize $i" &
done

wait

sort -n "$tmpfile"
rm "$tmpfile"
