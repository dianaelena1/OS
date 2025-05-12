

#Write a shell script that takes as parameters a short month name followed by a day number and a time interval (ex: Mar 8 11.00-12.00). 
#The script will display the usernames and the total number of users that were connected to the server on that date and within that time frame.

#!bin/bash


read -p "Enter short month name (e.g., Apr): " month
read -p "Enter day number (e.g., 14): " day
read -p "Enter time interval (e.g., 11.00-12.00): " interval

if [ -z "$month" ] || [ -z "$day" ] || [ -z "$interval" ]; then
    echo "Error: All inputs must be provided."
    exit 1
fi

# Remove dots and colons for numeric comparison.
start_time=$(echo "$interval" | cut -d '-' -f1 | sed 's/\.//g' | sed 's/://g')
end_time=$(echo "$interval" | cut -d '-' -f2 | sed 's/\.//g' | sed 's/://g')

echo "Entries for ${month} ${day} between ${interval}:"

last | awk -v mon="$month" -v d="$day" -v st="$start_time" -v et="$end_time" '
{
    # Field 6 = Month, Field 7 = Day, Field 8 = Time.
    if (NF < 8) next;
    if ($6 == mon && $7 == d) {
        login_time = $8;
        gsub(":", "", login_time);
        if (login_time >= st && login_time <= et) {
            print $0;
        }
    }
}'
