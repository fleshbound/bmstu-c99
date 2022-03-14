#!/bin/bash

files="*.o *.exe *.gcda *.gcno *.out *.gcov *.txt"
i=0

if [ ! \( -z "$2" \) ]; then
	echo "$0: Wrong keys"

	exit 1
fi

if [ ! \( -z "$1" \) ]; then
	if [ "$1" != "-s" ] && [ "$1" != "--silent" ]; then
		echo "$0: Wrong silent key"

		exit 1
	fi
fi

for file in $files; do
	if [ -f "$file" ]; then
		rm "$file"
		i=$(( i + 1 ))
	fi
done

if [ -z "$1" ]; then
	echo "[$0] All trash files were deleted ($i)"

	exit 0
elif [ "$1" == "-s" ] || [ "$1" == "--silent" ]; then
	exit 0
fi
