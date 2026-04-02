#!/bin/bash
ulimit -s 524288
mkdir stress
rm -rf stress/*
g++ gen.cpp -o stress/gen
g++ brt.cpp -o stress/brt
g++ sol.cpp -o stress/sol
g++ verif.cpp -o stress/verif
cd stress
for i in {1..50000}; do
    input=`./gen`
    brtout=$(./brt <<< "$input")
    solout=$(./sol <<< "$input")
    exit_code=$?
    RED='\033[0;31m'
    GREEN='\033[0;32m'
    NC='\033[0m' # No Color
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}runtime error on test $i ${NC}"
        printf "fuck"
        echo "$input" > failed.in
        break
    fi
    ver=$(./verif <<< "$input $brtout $solout")
    if [ "$ver" != "1" ]; then
        echo -e "${RED}wrong answer on test $i ${NC}"
        echo -e "$input" > failed.txt
        echo -e "$brtout" > correct.txt
        echo -e "$solout" > wrong.txt
        break
    fi
    echo -e "${GREEN}accepted on test $i ${NC}"
done
