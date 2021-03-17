CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/linux/blockchain : ../../src/main.c ../../build/linux/blockchain.o
	gcc -o ../../bin/linux/blockchain ../../src/main.c ../../build/linux/blockchain.o

../../build/linux/blockchain.o : ../../lib/blockchain.c ../../lib/headers/blockchain.h
	gcc -c -fpic -o ../../build/linux/blockchain.o ../../lib/blockchain.c

clean : 
	rm ../../bin/linux/blockchain ../../build/linux/blockchain.o
