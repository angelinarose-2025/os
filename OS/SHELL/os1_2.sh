#!/bin/bash
DIR="/home/$USER/class/batch"
mkdir -p "$DIR"
touch "$DIR/newfile_$(date +%s).txt"
ls -l "$DIR"
