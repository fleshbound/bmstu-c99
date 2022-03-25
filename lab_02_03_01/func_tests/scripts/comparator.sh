#!/bin/bash

# Compairing integers

file1="$1"
file2="$2"

reg_check="[+,-]*[0-9][0-9]*\.*[0-9]*"

data1="$( grep -o "$reg_check" "$file1" )"
data2="$( grep -o "$reg_check" "$file2" )"

#echo "$data1" "||" "$data2"

if [ "$data1" != "$data2" ]; then
	exit 1
else
	exit 0
fi
