#!/bin/bash


# Check if correct arguments
if [ $# -ne 2 ]; then
    echo "Usage: $0 winter_file summer_file"
    exit 1
fi

winter_file="$1"
summer_file="$2"

# Temporary file to store new data
temp_file=$(mktemp)

# Read each line from winter file
while read -r student winter_avg; do
    # Find the corresponding line in summer file
    summer_line=$(grep "^$student " "$summer_file")

    if [ -n "$summer_line" ]; then
        # Get only the grades
        grades=$(echo "$summer_line" | cut -d' ' -f2-)

        # Calculate summer average
        sum=0
        count=0
        for grade in $grades; do
            sum=$(echo "$sum + $grade" | bc)
            count=$((count + 1))
        done

        summer_avg=$(echo "scale=2; $sum / $count" | bc)

        # Calculate new yearly average
        yearly_avg=$(echo "scale=2; ($winter_avg + $summer_avg) / 2" | bc)

        # Write to temporary file
        echo "$student $yearly_avg" >> "$temp_file"
    else
        # If no summer grades, keep winter average
        echo "$student $winter_avg" >> "$temp_file"
    fi
done < "$winter_file"

# Sort by average descending and overwrite the original winter file
sort -k2 -nr "$temp_file" > "$winter_file"

# Remove the temporary file
rm "$temp_file"
