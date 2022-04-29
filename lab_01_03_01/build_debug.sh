#!/bin/bash

ERR_EXIST=1

files=$( find . -regextype posix-egrep -regex "\.*/[a-zA-Z_0-9]+\.c" )

if [ -z "$files" ]; then
    echo "$0: No .c files were found."

    exit $ERR_EXIST
fi

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 --coverage -c "$files"
gcc -o app.exe ./*.o --coverage -lm

if [ -s app.exe ]; then
    echo "[$0] Debug build was created"
    exit 0
else
    exit 1
fi
