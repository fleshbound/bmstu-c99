#!/bin/bash

if [ -z "$2" ]; then
    echo "No tests were found, quitting..."
    
    exit 1
fi

file_stream_in="$1"
file_stream_out_except="$2"
file_app_args="$3"

file_stream_out_current="tmp.txt"

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

if [ "$FLAG_VAL" = "1" ]; then
    touch trash.txt
    {
        valgrind --tool=memcheck --log-file=log.txt --quiet ../../app.exe "$file_app_args" < "$file_stream_in"
    } > trash.txt

    if [ -s "log.txt" ]; then
        echo "VALGRIND:"
        cat log.txt
    else
        echo "VALGRIND: No errors were detected."
    fi
fi

if [ "$res_code" != "0" ]; then
    exit 2
else
    ./comparator.sh "$file_stream_out_current" "$file_stream_out_except"
    result=$?
    
    if [ $result -eq 0 ]; then
        exit 0
    else
        exit 1
    fi
fi
