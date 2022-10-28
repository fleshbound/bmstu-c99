#!/bin/bash

curr_size=""

function lzero
{
    max_str="$1"
    max_len=${#max_str}
    var="$2"
    curr_len=${#var}
    while [ "$curr_len" -lt "$max_len" ]; do
        var="0$var"
        curr_len=${#var}
    done
    curr_size="$var"
}

#MIN_SIZE=1
sizes="$MIN_SIZE "

if [ -z "${MAX_SIZE+x}" ]; then
	MAX_SIZE=1000
fi

i=$MIN_SIZE
q=1
#STEP=50
#MID_STEP=200
#MIDDLE=600

while [ "$i" -lt "$MAX_SIZE" ]; do
    if [ "$i" -lt "$STEP" ]; then
        i=$(( i + STEP - MIN_SIZE ))
    else
        i=$(( i + STEP ))
    fi

    if [ "$i" -eq "$MIDDLE" ]; then
        STEP=$MID_STEP
    fi

    q=$(( q + 1 ))
    sizes="$sizes$i "
done


if [ -n "$1" ]; then
    sizes="$1"
fi

fill_codes="RANDOM SORTED REVERSED"
if [ -n "$2" ]; then
    fill_codes="$2"
fi

count=20
if [ -n "$3" ]; then
    count="$3"
fi

c=$NUM_OF_MAIN
if [ -z "${NUM_OF_MAIN+x}" ]; then
    NUM_OF_MAIN=1
    c=2
else
    NUM_OF_MAIN=1
fi

echo "Dataset status:"

cd ..
for j in $( seq "$c" ); do
    NUM_OF_MAIN="$j"
    for i in $( seq "$count" ); do
        for code in $fill_codes; do
            for size in $sizes; do
                echo -e -n "Count: $i/$count; code: $code; size: $size           \r"
                lzero "$MAX_SIZE" "$size"
                ./apps"$NUM_OF_MAIN"/app_"${code}"_"${curr_size}"_.exe >> \
                    ./data"$NUM_OF_MAIN"/"$code"_"$curr_size"_.txt
            done
        done
    done
done

echo -e "SUCCESS                                                                  "
