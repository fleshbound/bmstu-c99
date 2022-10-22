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

min_size=1
sizes="$min_size "
i=$min_size
q=1
step=1
mid_step=200
middle=600

while [ "$i" -lt "$MAX_SIZE" ]; do
    if [ "$i" -lt "$step" ]; then
        i=$(( i + step - min_size ))
    else
        i=$(( i + step ))
    fi

    #if [ "$i" -eq "$middle" ]; then
    #    step=$mid_step
    #fi

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

        make stat
        i=$(( i + 1 ))
    done
done

echo -e "SUCCESS                                                                  "
