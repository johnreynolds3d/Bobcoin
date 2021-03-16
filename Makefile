apps/blockchain : src/main.c build/blockchain.o
	gcc -Wall -o apps/blockchain src/main.c build/blockchain.o

build/blockchain.o : libs/blockchain.c libs/headers/blockchain.h
	gcc -c -Wall -Werror -fpic -o build/blockchain.o libs/blockchain.c

clean : 
	rm apps/blockchain build/blockchain.o
