#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Usage: $0 glossary.txt"
    exit 1
fi

mapfile -t lines < "$1"

for (( i=${#lines[@]}-1; i>=0; i-- )); do
    echo "${lines[i]}"
done


