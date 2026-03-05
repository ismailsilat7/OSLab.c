#!/bin/bash
read -p "Enter num1: " num1
read -p "Enter num2: " num2
echo "Addition: num1 + num2 = $((num1 + num2))"
echo "Multiplication: num1 x num2 = $((num1 * num2))"
echo "Subtraction: num1 - num2 = $((num1 - num2))"
if [ $num2 == 0 ]; then
	echo "Divison: cannot divide or take modulo as num2 is 0"
else
	echo "Division: num1/num2 = $((num1 / num2))"
	echo "Modulo: num1 % num2 = $((num1 % num2))"
fi
if [ $num1 == $num2 ]; then
	echo "num1 is equal to num2"
elif [ $num1 -gt $num2 ]; then
	echo "num1 is greater than num2"
else
	echo "num1 is less than num2"
fi
