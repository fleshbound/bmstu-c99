#!/bin/bash

count=2

function make_dirs
{
    cd ..
    for i in $( seq "$count" ); do
        if [ -d "./apps$i/" ]; then 
            rm -rf "./apps$i/"
        fi

        if [ -d "./data$i/" ]; then 
            rm -rf "./data$i/"
        fi

        if [ -d "./predata$i/" ]; then 
            rm -rf "./predata$i/"
        fi
        
        if [ -d "./postdata$i/" ]; then 
            rm -rf "./postdata$i/"
        fi

        mkdir "./apps$i/" "./data$i/" "./predata$i/" "./postdata$i/"
    done
    cd stat_scripts/
}

export MIN_SIZE=1
export MIDDLE=600
export STEP=1
export MID_STEP=200
export NUM_OF_MAIN=1
export MAX_SIZE=100

q=1

make_dirs
for i in $( seq "$count" ); do
    NUM_OF_MAIN="$i"
    echo -e -n "\tstat_main$q.c ($NUM_OF_MAIN):\n"
    ./build_apps.sh
    ./update_data.sh
    cd ..
    python3 ./stat_scripts/make_preproc.py "$NUM_OF_MAIN"
    cd stat_scripts/
done

./make_postproc.sh

echo "DONE"
