CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/windows/bobcoin.exe : ../../src/main.c ../../build/windows/bobcoin.o ../../build/windows/ecdsa.o ../../build/windows/sha256.o
	gcc -o ../../bin/windows/bobcoin.exe ../../src/main.c ../../build/windows/bobcoin.o ../../build/windows/ecdsa.o ../../build/windows/sha256.o

../../build/windows/bobcoin.o : ../../lib/bobcoin.c ../../lib/headers/bobcoin.h
	gcc -c -fpic -o ../../build/windows/bobcoin.o ../../lib/bobcoin.c

../../build/windows/ecdsa.o : ../../lib/ecdsa.c ../../lib/headers/ecdsa.h
	gcc -c -fpic -o ../../build/windows/ecdsa.o ../../lib/ecdsa.c

../../build/windows/sha256.o : ../../lib/sha256.c ../../lib/headers/sha256.h
	gcc -c -fpic -o ../../build/windows/sha256.o ../../lib/sha256.c

clean : 
	rm ../../bin/windows/bobcoin.exe ../../build/windows/bobcoin.o ../../build/windows/ecdsa.o ../../build/windows/sha256.o
