#!/bin/bash

v_flag=0
if [ "$1" = "-v" ]; then
	v_flag=1
	shift
fi

if [ -z "$1" ]; then
	echo "No tests were found, quitting..."
	exit 2
fi

file_stream_in="$1"
file_stream_out_except="$2"
shift
shift

file_app_args="$@"

touch tmp.txt
{
	../../*.exe "$file_app_args" < "$file_stream_in"
	result="$?"
} > tmp.txt
rm tmp.txt

if [ $v_flag -eq 1 ]; then
	valgrind --tool=memcheck ../../*.exe "$file_app_args" < "$file_stream_in"
fi

if [ -z "$file_stream_out_except" ]; then
        if [ "$result" = "0" ]; then 
		exit 1          
        else
		exit 0
        fi      
else    
	data="$( grep -o "[0-9][0-9]*" "$file_stream_out_except" )"
	
	#echo "$data" "$result"

	if [ "$result" == "$data" ]; then
		exit 0
	else
		exit 1
	fi
fi
