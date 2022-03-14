#!/bin/bash

flag_val=0
if [ "$1" = "-v" ]; then
	flag_val=1
	shift
fi

file_stream_in="$1"
file_stream_out_except="$2"
shift
shift
file_app_args="$@"

file_stream_out_current="tmp.txt"


if [ -z "$1" ] || [ -z "$2" ]; then
	echo "No tests were found, quitting..."
	exit 3
fi

touch $file_stream_out_current
{
	../../*.exe "$file_app_args" < "$file_stream_in"
} > $file_stream_out_current

if [ $flag_val -eq 1 ]; then
	valgrind --tool=memcheck ../../*.exe "$file_app_args" < "$file_stream_in"
fi

if [ "$?" != "0" ]; then
	rm $file_stream_out_current

	exit 2
else
	./comparator.sh "$file_stream_out_current" "$file_stream_out_except"
	
	rm $file_stream_out_current
	
	if [ $? -eq 0 ]; then
		exit 0
	else
		exit 1
	fi
fi
