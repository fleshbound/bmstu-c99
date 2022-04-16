#!/bin/bash

EXIT_SUCCESS=0
ERROR_ANSWER=1
ERROR_MEMORY=2
EXIT_SUCCESS_VALGRIND=3

ERROR_NONE=255

file_stream_in="$1"
file_stream_out_except="$2"
file_app_args="$3"
file_stream_out_current="tmp.txt"


if [ -z "$file_stream_out_except" ]; then
    echo "No tests were found, quitting..."
    exit $ERROR_NONE
fi

if [ ! \( -z "$file_app_args"  \) ]; then
    app_args=$( grep -F "" "$file_app_args" )
else
    app_args=""
fi

touch $file_stream_out_current
{
    ../../app.exe "$app_args" < "$file_stream_in"
    res_code=$?
} > $file_stream_out_current

error_memory=0
if [ $FLAG_VAL -eq 1 ]; then
    {
        valgrind --tool=memcheck --log-file=log.txt --quiet ../../app.exe "$file_app_args" < "$file_stream_in"
    } > /dev/null 2>&1

    if [ -s "log.txt" ]; then
        error_memory=1
    fi
fi

error_answer=0
if [ $res_code -ne 0 ]; then
    error_answer=1
else
    ./comparator.sh "$file_stream_out_current" "$file_stream_out_except"
    result=$?
    
    if [ $result -ne $EXIT_SUCCESS ]; then
        error_answer=1
    fi
fi

if [ $error_answer -eq 0 ] && [ $error_memory -eq 0 ] && [ $FLAG_VAL -eq 1 ]; then
    exit $EXIT_SUCCESS_VALGRIND
elif [ $error_answer -eq 0 ] && [ $error_memory -eq 0 ]; then
    exit $EXIT_SUCCESS
elif [ $error_answer -ne 0 ] && [ $error_memory -eq 0 ]; then
    exit $ERROR_ANSWER
elif [ $error_memory -ne 0 ]; then
    exit $ERROR_MEMORY
fi
