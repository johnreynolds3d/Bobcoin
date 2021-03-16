CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

apps/blockchain : src/main.c build/blockchain.o
	gcc -o apps/blockchain src/main.c build/blockchain.o

build/blockchain.o : libs/blockchain.c libs/headers/blockchain.h
	gcc -c -fpic -o build/blockchain.o libs/blockchain.c

clean : 
	rm apps/blockchain build/blockchain.o
