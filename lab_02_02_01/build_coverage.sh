#!/bin/bash

ERR_ARGS=1
ERR_EXT=2
ERR_EXIST=3

check_reg="^*.c$"

if [ -z "$2" ]; then
	echo "$0: Wrong number of arguments (expected 2 or more, got $#)"
	exit $ERR_ARGS
else
	if ( echo "$1" | grep -Eq "^*.exe$" ); then
		ex_name="$1"
		shift

		files="$@"

		for file in $files; do
			if ( echo "$file" | grep -Eq "$check_reg" ); then
				if [ ! \( -f "$file" \) ]; then
					echo "$0: File $file doesn't exist"
					exit $ERR_EXIST
				fi
			else
				echo "$0: Wrong files extension"
				exit $ERR_EXT
			fi
		done

		gcc -std=c99 -Wall -Werror "$@" --coverage -O0 -o "$ex_name" -lm 2> errors.txt

		if [ ! \( -s errors.txt \) ]; then
			echo "[$0] Debug .exe file was created"
			
			rm errors.txt

			exit 0
		else
			echo -e "$0: Some errors were detected:\n"
			
			cat errors.txt
			
			echo -e "\n$0: Quitting..."

			# ./clean_dir.sh "-s"

			exit 4
		fi
	else
		echo "$0: Wrong executable file extension (.exe expected)"

		exit $ERR_EXT
	fi
fi
