#!/bin/bash

function make_all_postdata
{
    count=2
    numb_len=${#MAX_SIZE}

    for i in $( seq "$count" ); do
        if [ -d "./postdata"${i}"/" ]; then
            rm -rf ./postdata"${i}"/*
        else
            mkdir "./postdata"${i}"/"
        fi
    done
    
    fill_codes="RANDOM SORTED REVERSED"
    codecount=3
    q=1

    echo -e -n "Postdata status:\n"

    for i in $( seq "$count" ); do
        files=$( ls ./predata"${i}"/ -S )
        fcount="$( find ./predata"${i}"/ -type f | wc -l )"
        size_fcount=$(( fcount / codecount ))
        
        echo "$( ls ./predata"${i}"/ -1 )" > "./tmp.txt"
        k=0

        for code in $fill_codes; do
            echo -e -n "Count: $i/$count; file: $k/$codecount       \r"
            k=$(( k + 1 ))
            
            curr_n=$(( k * size_fcount ))
            files=$( head -n "$curr_n" "./tmp.txt" | tail -n "$size_fcount" )
           
            j="$q"

            if [ "$q" -lt "10" ]; then
                j="0$q"
            fi

            for file in $files; do
                x=$( echo "$file" | cut -d'_' -f2 )
                avg=$( head -n 1 ./predata"${i}"/"${file}" )
                echo "${x} ${avg}" >> "./postdata"${i}"/${j}_${i}_${code}_avg.txt"
            done
            
            q=$(( q + 1 ))
        done
    done

    echo "SUCCESS                             "
}

cd ..
make_all_postdata

if [ -z "./graphs/" ]; then
    mkdir "./graphs/"
fi

echo "Graph 1 status:"
./stat_scripts/all_simple_lines.gpi
echo "SUCCESS             "

