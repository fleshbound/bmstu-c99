#!/bin/bash

file_stream_in="$1"
file_app_args="$2"
app_args=""

if [ "$#" = "3" ]; then
    file_stream_out_except="$2"
    file_app_args="$3"
fi

if [ ! \( -z "$file_app_args"  \) ]; then
    app_args=$( grep -F "" "$file_app_args" )
fi

{
../../app.exe "$app_args" < "$file_stream_in"
res_code=$?
} > tmp.txt

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

if [ -z "$file_stream_out_except" ]; then
    if [ "$res_code" != "0" ]; then      
        exit 0
    else
        exit 1
    fi
else    
    data=$( grep -o "[0-9][0-9]*" "$file_stream_out_except" )

    if [ "$res_code" = "$data" ]; then
        exit 0
    else
        exit 1
    fi
fi
