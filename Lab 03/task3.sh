#!/bin/bash
echo "Enter name: "
read name
echo "Enter your fav color: "
read color
echo "Hello ${name}, your favorite color is ${color}"
echo ${#name}
echo ${color:0:3}
predefined=Purple
if [ "$color" == "$predefined" ]
then
	echo "Purple is also my favorite color"
else
	echo "Nice, my favorite color is diff, it's ${predefined} and not ${color}"
fi
