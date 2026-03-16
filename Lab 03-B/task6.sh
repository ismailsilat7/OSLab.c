#!/bin/bash
"For Loop"
for (( i=1; i<=10; i++ ))
do
	echo "Number: $i"
done

echo "Displaying words from File"
for word in $(cat verysmall_list.txt)
do
	echo $word
done

echo "While Loop"
count=10
while [ $count -ge 1 ]
do
	echo "Number: $count"
	((count--))
done

echo "Until Loop"
count=1
until [ $count -gt 5 ]
do
	echo "Number: $count"
	((count++))
done

echo "Infinite Loop"
while true
do
	echo "Ctrl + C to stop"
	sleep 2
done
