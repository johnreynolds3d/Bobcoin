CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/linux/bobcoin : ../../src/main.c ../../build/linux/bobcoin.o ../../build/linux/ecdsa.o ../../build/linux/sha256.o
	gcc -o ../../bin/linux/bobcoin ../../src/main.c ../../build/linux/bobcoin.o ../../build/linux/ecdsa.o ../../build/linux/sha256.o -lm

../../build/linux/bobcoin.o : ../../lib/bobcoin.c ../../lib/headers/bobcoin.h
	gcc -c -fpic -o ../../build/linux/bobcoin.o ../../lib/bobcoin.c

../../build/linux/ecdsa.o : ../../lib/ecdsa.c ../../lib/headers/ecdsa.h
	gcc -c -fpic -o ../../build/linux/ecdsa.o ../../lib/ecdsa.c

../../build/linux/sha256.o : ../../lib/sha256.c ../../lib/headers/sha256.h
	gcc -c -fpic -o ../../build/linux/sha256.o ../../lib/sha256.c

clean : 
	rm ../../bin/linux/bobcoin ../../build/linux/bobcoin.o ../../build/linux/ecdsa.o ../../build/linux/sha256.o
