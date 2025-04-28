#!/bin/bash
# users_by_time.sh — list users who logged in on a given date/time window

if [[ $# -ne 3 ]]; then
  echo "Usage: $0 <Mon> <day> <start-end>"
  echo "  e.g. $0 Mar 8 11.00-12.00"
  exit 1
fi

month=$1
day=$2
interval=$3

# split interval and convert to HH:MM
start=${interval%-*}
end=${interval#*-}
start=${start//./:}
end=${end//./:}

# helper: HH:MM → minutes since midnight
to_min() {
  IFS=: read h m <<< "$1"
  # the 10# avoids octal
  echo $((10#$h * 60 + 10#$m))
}

start_min=$(to_min "$start")
end_min=$(to_min "$end")

declare -A seen

# read through `last` output
while read -r user tty host mon dayin time _rest; do
  # only care about lines matching our date
  [[ "$mon" == "$month" && "$dayin" == "$day" ]] || continue
  # skip system entries
  [[ "$user" =~ ^reboot|shutdown|wtmp ]] && continue

  login_min=$(to_min "$time")
  if (( login_min >= start_min && login_min <= end_min )); then
    seen["$user"]=1
  fi
done < <( last )

# output
echo "Users on $month $day between $start and $end:"
for u in "${!seen[@]}"; do
  echo "  $u"
done
echo "Total: ${#seen[@]}"
