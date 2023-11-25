
CC := gcc
CFLAGS = -ggdb -ansi -Wall -pedantic -O0
module_sources := $(wildcard ./src/modules/*.c)
sources := ./src/main.c $(module_sources)

default:
	$(CC) -o ./build/scheduler.exe $(CFLAGS) $(sources)
