#!/bin/bash

ERR_ARGS=1
ERR_EXT=2
ERR_EXIST=3

check_reg="^*.c$"
if [ -z "$1" ]; then
	echo "$0: Wrong number of arguments (expected 1 or more, got $#)"
	exit $ERR_ARGS
else
	files="$@"	       
	
	for file in $files; do
		if ( echo "$file" | grep -Eq "$check_reg" ); then
			if [ ! \( -f "$file" \) ]; then
				echo "$0: File $file doesn't exist"
				exit $ERR_EXIST
			fi
		else
			echo "$0: Wrong object file(s) extension"
			exit $ERR_EXT
		fi
	done

	gcc -std=c99 -Wall -Werror -g0 -c "$@"
	echo "[$0] Object file(s) was created"
	exit 0
fi
