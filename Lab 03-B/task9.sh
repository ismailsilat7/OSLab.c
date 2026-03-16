#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage: <directory_path> <pattern>"
	exit 1
fi

pattern=$2
path=$1

count=0

for file in "$path"/*
do
	if [ -f "$file" ]; then
		((count++))
		ext="${file##*.}"
		mv "$file" "${path}/${pattern}${count}.${ext}"
		echo "Renamed '$file' to'$path/${pattern}${count}.${ext}'"
	fi
done
