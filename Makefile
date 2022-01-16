CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2 

bin/bobcoin : src/main.c build/bobcoin.o build/ecdsa.o build/sha256.o
	gcc -o bin/bobcoin src/main.c build/bobcoin.o build/ecdsa.o build/sha256.o

build/bobcoin.o : lib/bobcoin.c lib/headers/bobcoin.h
	gcc -c -fpic -o build/bobcoin.o lib/bobcoin.c

build/ecdsa.o : lib/ecdsa.c lib/headers/ecdsa.h
	gcc -c -fpic -o build/ecdsa.o lib/ecdsa.c

build/sha256.o : lib/sha256.c lib/headers/sha256.h
	gcc -c -fpic -o build/sha256.o lib/sha256.c

clean : 
	rm bin/bobcoin build/bobcoin.o build/ecdsa.o build/sha256.o
