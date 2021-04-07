CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/mac/bobcoin : ../../src/main.c ../../build/mac/bobcoin.o ../../build/mac/ecdsa.o ../../build/mac/sha256.o
	gcc -o ../../bin/mac/bobcoin ../../src/main.c ../../build/mac/bobcoin.o ../../build/mac/ecdsa.o ../../build/mac/sha256.o

../../build/mac/bobcoin.o : ../../lib/bobcoin.c ../../lib/headers/bobcoin.h
	gcc -c -fpic -o ../../build/mac/bobcoin.o ../../lib/bobcoin.c

../../build/mac/ecdsa.o : ../../lib/ecdsa.c ../../lib/headers/ecdsa.h
	gcc -c -fpic -o ../../build/mac/ecdsa.o ../../lib/ecdsa.c

../../build/mac/sha256.o : ../../lib/sha256.c ../../lib/headers/sha256.h
	gcc -c -fpic -o ../../build/mac/sha256.o ../../lib/sha256.c

clean : 
	rm ../../bin/mac/bobcoin ../../build/mac/bobcoin.o ../../build/mac/ecdsa.o ../../build/mac/sha256.o
