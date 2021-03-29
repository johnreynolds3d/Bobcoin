CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/windows/blockchain : ../../src/main.c ../../build/windows/blockchain.o ../../build/windows/ecdsa.o ../../build/windows/sha256.o
	gcc -o ../../bin/windows/blockchain ../../src/main.c ../../build/windows/blockchain.o ../../build/windows/ecdsa.o ../../build/windows/sha256.o

../../build/windows/blockchain.o : ../../lib/blockchain.c ../../lib/headers/blockchain.h
	gcc -c -fpic -o ../../build/windows/blockchain.o ../../lib/blockchain.c

../../build/windows/ecdsa.o : ../../lib/ecdsa.c ../../lib/headers/ecdsa.h
	gcc -c -fpic -o ../../build/windows/ecdsa.o ../../lib/ecdsa.c

../../build/windows/sha256.o : ../../lib/sha256.c ../../lib/headers/sha256.h
	gcc -c -fpic -o ../../build/windows/sha256.o ../../lib/sha256.c

clean : 
	rm ../../bin/windows/blockchain ../../build/windows/blockchain.o ../../build/windows/ecdsa.o ../../build/windows/sha256.o
