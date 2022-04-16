#!/bin/bash

files="*.gcno"

for file in $files; do
    if [ ! \( -f "$file" \) ]; then
        # echo "$0: No .gcno files were found"
        
        exit 1
    fi
done

files="./*.c"

for file in $files; do
    gcov "$file"  > "temp_gcov.txt"

    coverage="$( grep -o "[0-9][0-9]*\.[0-9][0-9]*%" temp_gcov.txt )"

    echo "$file: CURRENT COVERAGE: $coverage"
done

exit 0
