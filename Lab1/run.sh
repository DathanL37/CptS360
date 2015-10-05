#!/bin/sh

clear
gcc -w -m32 lab1.c s.s

./a.out one two three four > outfile
cat outfile
