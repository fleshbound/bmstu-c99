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

#echo "$sizes"

fill_codes="RANDOM SORTED REVERSED"
q=$(( 3 * q ))
i=0

echo "Compilation status:"

cd ..
for code in $fill_codes; do
    for size in $sizes; do
        echo -e -n "$i/$q (code: $code; size: $size) \r"
        lzero "$MAX_SIZE" "$size"
        export STAT_APP=./apps"$NUM_OF_MAIN"/app_"${code}"_"${curr_size}"_.exe
        export CURR_SIZE="${size}"
        export CURR_CODE="${code}"
        export SORTC="1"

        if [ "$NUM_OF_MAIN" -eq 2 ]; then
            export SORTC="0"
        fi

        make stat >tmp.txt
        i=$(( i + 1 ))
    done
done

echo -e "SUCCESS                                                                  "
