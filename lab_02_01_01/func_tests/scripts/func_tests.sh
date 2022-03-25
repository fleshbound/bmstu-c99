#!/bin/bash

# --FLAGS--

flag_val=0
flag_silent=0
flag_coverage=0

# Updates flags (ignores incorrect)
function update_flags
{
	if [ "$1" = "-USE_VALGRIND" ] || [ "$2" = "-USE_VALGRIND" ] || [ "$3" = "-USE_VALGRIND" ]; then
		flag_val=1
	fi

	if [ "$1" = "-s" ] || [ "$2" = "-s" ] || [ "$3" = "-s" ]; then
                flag_silent=1
        fi

	if [ "$1" = "-c" ] || [ "$2" = "-c" ] || [ "$3" = "-c" ]; then
                flag_coverage=1
        fi
}

# Checks positive tests and returns number of failures
function check_positive
{
	if [ $flag_silent -eq 0 ]; then
		echo -e "\n---POSITIVE-TESTS---\n"
	fi

	files_pos_in=$main_dir"/pos_**_in\.txt"
	i=1
	q_pos=0
	num=""
	for file in $files_pos_in; do
		# '0' -> '00', '10' -> '10' (correct number for test file name)
		if [ $i -lt 10 ]; then
			num="0$i"
		else
			num="$i"
		fi
	
		# Compairing ethalon and current output
		if [ $flag_val -eq 1 ]; then
			./pos_case.sh -v "$file" $main_dir/pos_"$num"_out.txt
			result=$?
		else
			./pos_case.sh "$file" $main_dir/pos_"$num"_out.txt
			result=$?
		fi

		# Single result output
		if [ $flag_silent -eq 0 ]; then
			if [ $result -eq 0 ]; then
				echo -e "Test $num: OK\n"
			else
				echo -e "Test $num: FAILED\n"
				q_pos=$(( q_pos + 1 ))
			fi
		fi

		i=$(( i + 1 ))
	done
	
	# Total output
	if [ $flag_silent -eq 0 ]; then
		echo -e "Failed $q_pos POSITIVE test(s) of total $(( i - 1 ))\n"
	fi

	return $q_pos
}

# Checks negative tests and returns number of failures
function check_negative
{
	if [ $flag_silent -eq 0 ]; then
		echo -e "\n---NEGATIVE-TESTS---\n"
	fi

	files_neg_in=$main_dir"/neg_**_in\.txt"
	i=1
	q_neg=0
	num=""
	for file in $files_neg_in; do
		# '0' -> '00', '10' -> '10' (correct number for test file name)
		if [ $i -lt 10 ]; then
			num="0$i"
		else
			num="$i"
		fi

		# Compairing ethalon and current output (by exit code or not)
		if [ $flag_val -eq 1 ]; then
			./neg_case.sh -v "$file" $main_dir/neg_"$num"_out.txt
			result=$?
		else
			./neg_case.sh "$file" $main_dir/neg_"$num"_out.txt
			result=$?
		fi
		
		# Single result output
		if [ $flag_silent -eq 0 ]; then
			if [ $result -eq 0 ]; then
				echo -e "TEST $num: OK\n"
			else
				echo -e "TEST $num: FAILED\n"
				q_neg=$(( q_neg + 1 ))
			fi
		fi

		i=$(( i + 1 ))
	done

	# Total output
	if [ $flag_silent -eq 0 ]; then
		echo -e "Failed $q_neg NEGATIVE test(s) of total $(( i - 1 ))\n"
	fi

	return $q_neg
}

# Shows current coverage by percent
function show_coverage
{
	if [ $flag_coverage -eq 1 ]; then
                ../../collect_coverage.sh ../../*.exe
		if [ ! \( $? -eq 0 \) ]; then
			echo "ERROR: No coverage info was found"
			echo "NOTE: Try rerun code with build_coverage.sh script"
		fi
        fi
}

# ---------------
# ---MAIN-CODE---
# ---v-v-v-v-v---

# cd "/func_tests/scripts/"
main_dir="../data"

if [ ! \( -f ../../*.exe \) ]; then
	echo "ERROR: No executable file(s) was(were) found"
	echo "NOTE: Try running a build script in one of parental directories"
	echo "Quitting..."
	exit 100
fi

update_flags "$1" "$2" "$3"

check_positive
pos=$?

check_negative
neg=$?

show_coverage

echo -e "\nTotal: $(( pos + neg )) test(s) was(were) failed\n"

exit $(( pos + neg ))
