#!/bin/bash
name="Ismail Silat"
section="BCS-4H"
num=5
echo $name $section $num
echo "Modifying values..."
name="Ismail"
section="4H"
num=6
echo $name $section $num
array=( "Ismail" "Ali" "Khan" "meow" "Duh" )
echo "${array[*]}"
array+=( 5 )

i=0
for item in "${array[@]}"
do
	(( i++ ))
	echo $i $item
done
