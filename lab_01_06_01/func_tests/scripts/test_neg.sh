#!/bin/bash

if [ -z "$1" ]; then
        echo "Invalid key(s) (number of lab)"
        exit 1
else
        code="$1"
        main_code="../../lab_01_""$code""_01.c"
        tests_dir="../data"
        neg_in_files=$tests_dir"/neg_**_in.txt"

        gcc -std=c99 -Wall -Werror -Wpedantic -o "temp.exe" "$main_code" -lm

        i=0
        q_neg=0
        for file in $neg_in_files; do
                i=$(( i + 1 ))

		./sub_test_neg.sh "$i" "$file"

                if [ $? -eq 0 ]; then
                        echo "Test $i: OK"
                else
                        q_neg=$(( q_neg + 1 ))
                        echo "Test $i: FAILED"
                fi
        done

        echo -e "\nFailed $q_neg test(s) of total $i. Quiting..."

        rm "temp.exe"

        exit 0
fi

