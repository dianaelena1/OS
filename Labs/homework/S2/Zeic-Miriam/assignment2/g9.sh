#Write a shell script which takes as parameters several user accounts (ex: gmae0221
#jpae0229). The script will display the user accounts (from those given as parameters)
#that are currently connected to the server.
#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 user1 [user2 ... userN]"
  exit 1
fi

who_output=$(who)

logged_in_users=()


for word in $who_output; do
  user=$word
  exists=0
  for u in "${logged_in_users[@]}"; do
    if [ "$u" = "$user" ]; then
      exists=1
      break
    fi
  done

  if [ $exists -eq 0 ]; then
    logged_in_users+=("$user")
  fi
  
  skip=0

  for _ in 1 2 3 4; do
    read -r _
  done
done <<< "$who_output"

for given_user in "$@"; do
  connected=0

  for u in "${logged_in_users[@]}"; do
    if [ "$u" = "$given_user" ]; then
      connected=1
      break
    fi
  done

  if [ $connected -eq 1 ]; then
    echo "$given_user is currently connected."
  else
    echo "$given_user is NOT connected."
  fi

done
