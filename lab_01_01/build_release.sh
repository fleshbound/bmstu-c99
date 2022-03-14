#!/bin/bash

# Принимает на вход 1) имя исполняемого 2-N) имена объектных файлов

ERR_ARGS=1
ERR_EXT=2
ERR_EXIST=3

check_reg="^*.o"
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

	gcc -o "$exe_name" "$@"
	echo "[$0] Executable file was created"
	exit 0
else
	echo "$0: Wrong executable file extension (.exe expected)"
	exit $ERR_EXT
fi
