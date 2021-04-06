CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g -O2

../../bin/mac_os/bobcoin : ../../src/main.c ../../build/mac_os/bobcoin.o ../../build/mac_os/ecdsa.o ../../build/mac_os/sha256.o
	gcc -o ../../bin/mac_os/bobcoin ../../src/main.c ../../build/mac_os/bobcoin.o ../../build/mac_os/ecdsa.o ../../build/mac_os/sha256.o

../../build/mac_os/bobcoin.o : ../../lib/bobcoin.c ../../lib/headers/bobcoin.h
	gcc -c -fpic -o ../../build/mac_os/bobcoin.o ../../lib/bobcoin.c

../../build/mac_os/ecdsa.o : ../../lib/ecdsa.c ../../lib/headers/ecdsa.h
	gcc -c -fpic -o ../../build/mac_os/ecdsa.o ../../lib/ecdsa.c

../../build/mac_os/sha256.o : ../../lib/sha256.c ../../lib/headers/sha256.h
	gcc -c -fpic -o ../../build/mac_os/sha256.o ../../lib/sha256.c

clean : 
	rm ../../bin/mac_os/bobcoin ../../build/mac_os/bobcoin.o ../../build/mac_os/ecdsa.o ../../build/mac_os/sha256.o
