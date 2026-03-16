#!/bin/bash

search="Linux"
count=0
lines=0

while IFS= read -r line
do
	((lines++))
	if [[ "$line" == *"$search"* ]]
	then
		echo "Found Linux:[$lines]"
		((count++))
	fi
done < lines.txt

echo "Number of lines: $count" 
