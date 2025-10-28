#!/usr/bin/env bash
set -euo pipefail

t=$1

g++ gen.cpp -o gen
g++ A.cpp -o A
g++ A__Good.cpp -o A__Good

for ((i=1; i<=t; i++)); do
    ./gen > in.txt
    ./A < in.txt > out.txt
    ./A__Good < in.txt > ans.txt

    if diff -q out.txt ans.txt > /dev/null; then
        echo "Accepted"
    else
        echo "Input"
        cat in.txt
        echo " "
        echo "Output"
        cat out.txt
        echo " "
        echo "Answer"
        cat ans.txt
        exit 1
    fi
done
