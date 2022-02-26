#!/bin/bash

str=""
if [ $1 -lt 10 ]; then
	str="0$1"
else
	str="$1"
fi

pos_out_file="../data/pos_""$str""_out.txt"
touch "tmp.txt"
{
	 ./temp.exe < "$2"
} > "tmp.txt"

data1="$(grep -o "[0-9][0-9]*" "tmp.txt")"
data2="$(grep -o "[0-9][0-9]*" "$pos_out_file")"

rm "tmp.txt"

if [ "$data1" = "$data2" ]; then
	exit 0
else
	echo "[!] Test $1: expected '$data2', got '$data1'"
	exit 1
fi
