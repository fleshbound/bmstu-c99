#!/bin/bash

#cd ../../

EXIT_SUCCESS=0
EXIT_FAILURE=1

file1="$1" # got
file2="$2" # except

reg_check="^.*$"

data1="$( grep -o "$reg_check" "$file1" )"
data2="$( grep -o "$reg_check" "$file2" )"

# echo "|$data1|$data2|"

if [ "$data1" != "$data2" ]; then
    exit $EXIT_FAILURE
fi

exit $EXIT_SUCCESS

