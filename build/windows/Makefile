CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/windows/blockchain_win64.exe : ../../src/main.c ../../build/windows/blockchain.o ../../build/windows/sha256.o
	x86_64-w64-mingw32-gcc -o ../../bin/windows/blockchain_win64.exe ../../src/main.c ../../build/windows/blockchain.o ../../build/windows/sha256.o

../../build/windows/blockchain.o : ../../lib/blockchain.c ../../lib/headers/blockchain.h
	x86_64-w64-mingw32-gcc -c -fpic -o ../../build/windows/blockchain.o ../../lib/blockchain.c

../../build/windows/sha256.o : ../../lib/sha256.c ../../lib/headers/sha256.h
	x86_64-w64-mingw32-gcc -c -fpic -o ../../build/windows/sha256.o ../../lib/sha256.c

clean : 
	rm ../../bin/windows/blockchain_win64.exe ../../build/windows/blockchain.o ../../build/windows/sha256.o
