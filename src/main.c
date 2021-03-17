#include "../lib/headers/blockchain.h"
#include <stdio.h>

int main() {

  struct Block *blockChain[3];

  blockChain[0] =
      Block_create(0, "Bob sent Laura 10 bitcoin, Dale sent Harry 7 bitcoin");

  blockChain[1] =
      Block_create(blockChain[0]->hash,
                   "David sent Bob 12 bitcoin, Windom sent Bob 5 bitcoin");
  blockChain[2] =
      Block_create(blockChain[1]->hash,
                   "Gordon sent Sarah 4 bitcoin, Shelley sent Bobby 2 bitcoin");

  int i;

  for (i = 0; i < 3; i++) {
    printf("\nBlock #%d\n", i);
    Block_print(blockChain[i]);
    printf("\n");
  }

  printf("\n");

  for (i = 0; i < 3; i++) {
    Block_destroy(blockChain[i]);
  }

  return 0;
}
