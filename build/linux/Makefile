CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/linux/blockchain : ../../src/main.c ../../build/linux/blockchain.o ../../build/linux/ecdsa.o ../../build/linux/sha256.o
	gcc -o ../../bin/linux/blockchain ../../src/main.c ../../build/linux/blockchain.o ../../build/linux/ecdsa.o ../../build/linux/sha256.o -lm

../../build/linux/blockchain.o : ../../lib/blockchain.c ../../lib/headers/blockchain.h
	gcc -c -fpic -o ../../build/linux/blockchain.o ../../lib/blockchain.c

../../build/linux/ecdsa.o : ../../lib/ecdsa.c ../../lib/headers/ecdsa.h
	gcc -c -fpic -o ../../build/linux/ecdsa.o ../../lib/ecdsa.c

../../build/linux/sha256.o : ../../lib/sha256.c ../../lib/headers/sha256.h
	gcc -c -fpic -o ../../build/linux/sha256.o ../../lib/sha256.c

clean : 
	rm ../../bin/linux/blockchain ../../build/linux/blockchain.o ../../build/linux/ecdsa.o ../../build/linux/sha256.o
