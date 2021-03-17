#include "../lib/headers/blockchain.h"
#include <stdio.h>

int main() {

  struct Block *blockchain[3];

  blockchain[0] =
      Block_create(0, "Bob sent Laura 10 bitcoin, Dale sent Harry 7 bitcoin");

  blockchain[1] =
      Block_create(blockchain[0]->hash,
                   "David sent Bob 12 bitcoin, Windom sent Bob 5 bitcoin");
  blockchain[2] =
      Block_create(blockchain[1]->hash,
                   "Gordon sent Sarah 4 bitcoin, Shelley sent Bobby 2 bitcoin");

  int i;

  for (i = 0; i < 3; i++) {
    printf("\nBlock %d:\n", i);
    Block_print(blockchain[i]);
    printf("\n");
  }

  printf("\n");

  for (i = 0; i < 3; i++) {
    Block_destroy(blockchain[i]);
  }

  return 0;
}
