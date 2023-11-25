default:
	mkdir -p ./build
	gcc -ansi -Wall -pedantic -o ./build/scheduler.exe ./src/modules/*.c ./src/main.c
