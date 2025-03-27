#!/bin/bash
line_count=0
word_count=0
char_cound=0
echo "Enter text (Ctrl+D to stop):"
while IFS= read -r line; do
    ((line_count++))
    word_count=$((word_count + $(echo "$line" | wc -w)))
    char_cound=$((char_cound + ${#line}))
done
echo "No. of lines: $line_count"
echo "No. of Words: $word_count"
echo "No. of Characters: $char_cound"

