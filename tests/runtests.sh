# clean up previous object, shared library, and executable files
#rm -f blockchain lib_blockchain.o lib_blockchain.so 

# compile library into position-independent code (PIC)
#gcc -c -Wall -Werror -fpic blockchain.c

# turn the resulting object file into a shared library
#gcc -shared -o lib_blockchain.so blockchain.o

# compile main.c and link it with the shared library
#gcc -Wall -o blockchain main.c blockchain.o

# run program using valgrind to check for memory leaks
valgrind --leak-check=yes -s ./bin/blockchain
