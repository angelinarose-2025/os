#!/bin/bash

read -p "Enter username to check: " user

while true; do
    if who | grep -q "^$user "; then
        echo "$user has logged in!"
        break
    else
        echo "Checking again in 30 seconds..."
        sleep 30
    fi
done

