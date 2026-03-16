#!/bin/bash

function fact() {
	num=$1
	for (( i=num-1; i>=2; i-- ))
	do
		(( num = num*i ))
	done
	echo $num
}

for arg in "$@"
do
	factorial=$(fact "$arg")
	echo "$arg's Factorial: $factorial"
done


