#!/bin/bash

gcc -Wall -ansi -pedantic -o test.exe ../modules/*.c $1

./test.exe
