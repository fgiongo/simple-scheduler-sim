#!/bin/bash

rm test.exe
gcc -O0 -ggdb -Wall -ansi -pedantic -o test.exe ../modules/*.c $1
./test.exe
