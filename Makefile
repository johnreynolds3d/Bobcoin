CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

bin/blockchain : src/main.c build/blockchain.o
	gcc -o bin/blockchain src/main.c build/blockchain.o

build/blockchain.o : lib/blockchain.c lib/headers/blockchain.h
	gcc -c -fpic -o build/blockchain.o lib/blockchain.c

clean : 
	rm bin/blockchain build/blockchain.o
