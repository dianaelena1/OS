#Write a Shell program that supervises the system, such that:
# for each new connection in the system, on the terminal from which the connection was made,
# it will print a list of all active users from the system, and for each user it will print the number of launched processes by that user.

#!/bin/bash

who > users_old.txt

while true
do
  sleep 5
  who > users_new.txt

  new_connections=$(comm -13 users_old.txt users_new.txt)

  if [ ! -z "$new_connections" ]; then
    echo "$new_connections" | while read line
    do
      user=$(echo "$line" | awk '{print $1}')
      terminal=$(echo "$line" | awk '{print $2}')

      echo "A new user has connected!" > /dev/$terminal
      echo "Here are all active users and their process counts:" > /dev/$terminal

      who | awk '{print $1}' | sort | uniq | while read active_user
      do
        process_count=$(ps -u "$active_user" --no-headers | wc -l)
        echo "$active_user has $process_count process(es)" > /dev/$terminal
      done
    done
  fi

  mv users_new.txt users_old.txt
done
