#!/bin/bash

DIR="./$USER/class/batch"
HASH_FILE="file_hashes.txt"

# Generate initial hashes
if [ "$1" == "init" ]; then
    mkdir -p "$DIR"
    find "$DIR" -type f -exec sha256sum {} \; > "$HASH_FILE"
    echo "Initial hashes stored."
    exit 0
fi

# Check integrity
if [ ! -f "$HASH_FILE" ]; then
    echo "No hash file found. Run: $0 init"
    exit 1
fi

while read -r hash file; do
    if [ -f "$file" ]; then
        new_hash=$(sha256sum "$file" | awk '{print $1}')
        if [ "$hash" != "$new_hash" ]; then
            echo "Warning: $file has changed!"
        fi
    else
        echo "Warning: $file is missing!"
    fi
done < "$HASH_FILE"

