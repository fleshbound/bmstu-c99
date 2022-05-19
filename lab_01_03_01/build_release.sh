#!/bin/bash

ERR_EXIST=1
 
files=$( find . -regextype posix-egrep -regex "\.*/[a-zA-Z_0-9]+\.c" )

if [ -z "$files" ]; then
    echo "$0: No .c files were found."

    exit $ERR_EXIST
fi

gcc -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O3 -g0 -c main.c
gcc -o app.exe ./*.o -lm

if [ -s app.exe ]; then
    echo "[$0] Release build was created"
    exit 0
else
    exit 1
fi

