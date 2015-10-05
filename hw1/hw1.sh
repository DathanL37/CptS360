#!/bin/sh

gcc -w -m32 t.c
clear

./a.out one two three > outfile
cat outfile
