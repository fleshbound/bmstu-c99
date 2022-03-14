#!/bin/bash

files="../../*.gcno"

for file in $files; do
	if [ ! \( -f "$file" \) ]; then
		# echo "$0: No .gcno files were found"
		
		exit 1
	fi
done


gcov "$1" > temp_gcov.txt 2> err_gcov.txt

coverage="$( grep -o "[0-9][0-9]*\.[0-9][0-9]*%" temp_gcov.txt )"

rm temp_gcov.txt

echo "Current COVERAGE: $coverage"

rm err_gcov.txt
rm *.c.gcov

exit 0
