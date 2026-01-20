#!/bin/bash
ulimit -s 524288
mkdir stress
rm -rf stress/*
g++ gen.cpp -o stress/gen
g++ brt.cpp -o stress/brt
g++ sol.cpp -o stress/sol
cd stress
for i in {1..500}; do
	input=`./gen`
	brtout=$(./brt <<< "$input")
	solout=$(./sol <<< "$input")
	exit_code=$?
    if [ $exit_code -ne 0 ]; then
		echo -e "\e[31mexited with code $exit_code on test $i\e"
        echo "$input" > failed.in
        break
    fi
	if [ "$brtout" != "$solout" ]; then
		echo -e "\e[31mfailed on test $i\e"
		echo $input > failed.in
		echo $brtout > correct.txt
		echo $solout > wrong.txt
		break
	fi
	echo -e "\e[32maccepted on test $i\e"
done
