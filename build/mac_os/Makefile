CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/mac_os/blockchain : ../../src/main.c ../../build/mac_os/blockchain.o ../../build/mac_os/sha256.o
	gcc -o ../../bin/mac_os/blockchain ../../src/main.c ../../build/mac_os/blockchain.o ../../build/mac_os/sha256.o

../../build/mac_os/blockchain.o : ../../lib/blockchain.c ../../lib/headers/blockchain.h
	gcc -c -fpic -o ../../build/mac_os/blockchain.o ../../lib/blockchain.c

../../build/mac_os/sha256.o : ../../lib/sha256.c ../../lib/headers/sha256.h
	gcc -c -fpic -o ../../build/mac_os/sha256.o ../../lib/sha256.c

clean : 
	rm ../../bin/mac_os/blockchain ../../build/mac_os/blockchain.o ../../build/mac_os/sha256.o
