#!/bin/bash
#Given a C program, write a Shell script that finds how many times each
# function defined in the program is called,
# and prints the line number for each function call in the program.

# Check if a C source file is provided
if [ $# -ne 1 ]; then
  echo "Usage: $0 source_file.c"
  exit 1
fi

file="$1"

if [ ! -f "$file" ]; then
  echo "File not found: $file"
  exit 1
fi

echo "Analyzing function calls in $file"
echo

# Find function definitions (not prototypes or calls)
# e.g., int foo(...) {
grep -nE '^[a-zA-Z_][a-zA-Z0-9_ \t\*]*[ \t]+[a-zA-Z_][a-zA-Z0-9_]*[ \t]*\([^\)]*\)[ \t]*\{' "$file" |
while IFS=: read -r def_line def_code; do
  # Extract function name from the definition line
  func_name=$(echo "$def_code" | sed -nE 's/.*[ \t]([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*\(.*/\1/p')

  if [ -n "$func_name" ]; then
    echo "Function: $func_name"

    # Find all calls to this function (skip definition line itself)
    grep -nE "\b$func_name[ \t]*\(" "$file" | grep -v "^$def_line:" |
    while IFS=: read -r line_number line_text; do
      echo "  Called at line $line_number"
    done | tee /tmp/"$func_name"_calls.tmp

    count=$(wc -l < /tmp/"$func_name"_calls.tmp)
    echo "  Total calls: $count"
    echo
    rm /tmp/"$func_name"_calls.tmp
  fi
done
