#!/bin/bash

# Принимает на вход 1) имя исполняемого 2-N) имена файлов с кодом

ERR_ARGS=1
ERR_EXT=2
ERR_EXIST=3

check_reg="^*.c"
if [ -z "$2" ]; then
	echo "$0: Wrong number of arguments (expected 2 or more, got $#)"
	exit $ERR_ARGS
elif ( echo "$1" | grep -Eq "^*.exe$"  ); then
	exe_name="$1"
	shift
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

	gcc -std=c99 -Wall -Werror -Wpedantic -g3 -c "$@"
	gcc -o "$exe_name" *.o -lm
	echo "[$0] Build debug was created"
	exit 0
else
	echo "$0: Wrong executable file extension (.exe expected)"
	exit $ERR_EXT
fi
