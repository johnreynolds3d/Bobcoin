rm -f blockchain   

gcc -c -Wall -Werror -fpic lib_blockchain.c
gcc -shared -o lib_blockchain.so lib_blockchain.o
gcc -Wall -o blockchain blockchain.c lib_blockchain.o

valgrind --leak-check=yes -s ./blockchain
