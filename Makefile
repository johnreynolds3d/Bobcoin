bin/blockchain : src/main.c build/blockchain.o
	gcc -Wall -o bin/blockchain src/main.c build/blockchain.o

build/blockchain.o : src/blockchain.c src/blockchain.h
	gcc -c -Wall -Werror -fpic -o build/blockchain.o src/blockchain.c

clean : 
	rm bin/blockchain build/blockchain.o
