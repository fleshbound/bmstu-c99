#!/bin/bash

# Запуск: ./имя_скрипта.sh номер_лабораторной_NN
# Скрипт должен находиться в папке "scripts"

if [ -z "$1" ]; then
	echo "Invalid script code"
	exit 1
else
	code="$1"
	main_code="../../lab_01_""$code""_01.c"
	tests_dir="../data"
	pos_in_files=$tests_dir"/pos_**_in.txt"

	gcc -std=c99 -Wall -Werror -Wpedantic -o "temp.exe" "$main_code" -lm
	
	i=0
	q_neg=0
	for file in $pos_in_files; do
		i=$(( i + 1 ))
		
		numbers="$(grep -o "[0-9][0-9]* [0-9][0-9]*" "$file")"
		
		./vroom1.sh "$i" "$file"
		
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
