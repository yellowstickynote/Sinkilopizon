#!/bin/bash
ulimit -s 524288
mkdir stress
rm -rf stress/*
g++ gen.cpp -o stress/gen
g++ brt.cpp -o stress/brt
g++ sol.cpp -o stress/sol
g++ verif.cpp -o stress/verif
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
	echo "$input $brtout $solout"
	ver=$(./verif <<< "$input $brtout $solout")
	if [ "$ver" != "0" ]; then
		echo -e "\e[31mfailed on test $i\e"
		echo -e "$input" > failed.in
		echo -e "$brtout" > correct.txt
		echo -e "$solout" > wrong.txt
		break
	fi
	echo -e "\e[32maccepted on test $i\e"
done
