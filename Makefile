CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2 

bin/bobcoin : src/main.c obj/bobcoin.o obj/ecdsa.o obj/sha256.o
	@mkdir -p bin
	gcc -o bin/bobcoin src/main.c obj/bobcoin.o obj/ecdsa.o obj/sha256.o

obj/bobcoin.o : src/bobcoin.c lib/bobcoin.h
	gcc -c -fpic -o obj/bobcoin.o src/bobcoin.c

obj/ecdsa.o : src/ecdsa.c lib/ecdsa.h
	gcc -c -fpic -o obj/ecdsa.o src/ecdsa.c

obj/sha256.o : src/sha256.c lib/sha256.h
	@mkdir -p obj
	gcc -c -fpic -o obj/sha256.o src/sha256.c

.PHONY: clean
clean : 
	rm bin/bobcoin obj/bobcoin.o obj/ecdsa.o obj/sha256.o
