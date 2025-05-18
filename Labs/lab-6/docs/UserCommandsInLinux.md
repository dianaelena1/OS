**User Commands in Linux 🐧**

**1️. Creating and Managing Users**

-   **Create a new user:\
    sudo adduser \[username\]\
    *Creates a new user with a home directory and prompts for a password
    setup.***

-   **Change a user's password:\
    passwd \[username\]\
    *Changes the password of the specified user.***

-   **Delete a user (without removing their home directory):\
    sudo deluser \[username\]\
    *Removes a user but keeps their home directory.***

-   **Remove a user and their home directory:\
    sudo deluser \--remove-home \[username\]\
    *Deletes the user and their home directory.***

**2️. Viewing User and Group Information**

-   **See which groups a user belongs to:\
    groups \[username\]**

-   **View detailed user information (ID, groups, etc.):\
    id \[username\]**

-   **List all existing users:\
    cat /etc/passwd\
    *Displays all system users.***

-   **View all groups on the system:\
    cat /etc/group**

-   **Check users in a specific group:\
    getent group \[group-name\]**

**3️. Creating and Managing Groups**

-   **Create a new group:\
    sudo groupadd \[group-name\]\
    *Adds a new group to the system.***

-   **Add a user to a group:\
    sudo usermod -aG \[group-name\] \[username\]\
    *Appends the user to the specified group without removing them from
    existing groups.***

-   **Remove a user from a group:\
    sudo gpasswd -d \[username\] \[group-name\]**

-   **Delete a group:**

> **sudo groupdel \[group-name\]**

**4️. Managing User Privileges**

-   **Grant admin (sudo) privileges to a user:\
    sudo usermod -aG sudo \[username\]\
    *Adds the user to the sudo group, allowing them to execute
    administrative commands.***

-   **Check if a user has sudo privileges:\
    sudo -l**

-   **Switch to another user:\
    su \[username\]\
    *Temporarily logs in as another user.***

**5️. Working with File and Folder Permissions**

-   **Change the group ownership of a folder:\
    sudo chgrp \[group-name\] \[folder-name\]\
    *Changes the group ownership of a folder to a specified group.***

-   **Change group ownership recursively (for all subfolders and
    files):\
    sudo chgrp -R \[group-name\] \[folder-name\]**

-   **Modify folder permissions:**

    -   **Allow group members to write to a folder:\
        sudo chmod g+w \[folder-name\]**

    -   **Grant full access to a folder for all users:\
        sudo chmod 777 \[folder-name\]**

    -   **Restrict access to group members only:\
        sudo chmod 770 \[folder-name\]**

-   **Check permissions of a file or folder:\
    ls -ld \[folder-name\]**

**6️. Deleting Users and Groups**

-   **Delete a user from the system:\
    sudo deluser \[username\]**

-   **Delete a user along with their home directory:\
    sudo deluser \--remove-home \[username\]**

-   **Delete only home directory**

> **sudo rm -r /home/\[username\]**

-   **Delete a group:\
    sudo groupdel \[group-name\]**

**7️. Additional Useful Commands**

-   **Kill all processes belonging to a user:\
    sudo killall -u \[username\]**

-   **Check active logged-in users:\
    who**

-   **Check last login time of a user:\
    lastlog -u \[username\]**
