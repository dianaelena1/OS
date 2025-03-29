#!/bin/bash

#10	Write a shell script which takes as parameter an existing group number (ex: 821). The script will display the details about that group.

echo "Enter group number:"
read group #citeste numarul grupului de la tastatura

group_info=$(getent group $group) #cauta grupul in /etc/group

if [ -n "$group_info" ]; then #daca grupul exista

    echo "Group info: $group_info" #afiseaza informatiile despre grup
else
    echo "Group not found" #daca grupul nu exista, afiseaza un mesaj de eroare
fi
