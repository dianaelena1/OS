#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file.c>"
    exit 1
fi

FILE="$1"

if [ ! -f "$FILE" ]; then
    echo "File not found: $FILE"
    exit 1
fi

function_names=$(grep -E '^[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\([^;]*\)[[:space:]]*\{' "$FILE" | \
    sed -E 's/^[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]+([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*\(.*/\1/')

for func in $function_names; do
    [ "$func" = "main" ] && continue

    echo "Function: $func"
    count=0

    call_lines=$(grep -n "\b$func[[:space:]]*(" "$FILE")

    while IFS= read -r line; do
        line_number="${line%%:*}"
        code_line="${line#*:}"

        if echo "$code_line" | grep -qE "\b$func[[:space:]]*\([^)]*\)[[:space:]]*\{"; then
            continue
        fi

        echo "  Called at line $line_number: $code_line"
        count=$((count + 1))
    done <<< "$call_lines"

    if [ "$count" -eq 0 ]; then
        echo "  No calls found."
    else
        echo "  Call count: $count"
    fi

    echo
done
