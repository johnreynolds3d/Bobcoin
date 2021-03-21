#include "../lib/headers/blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  int num_blocks = 3;

  struct Block *blockchain[num_blocks];

  int num_leading_zeros;

  num_leading_zeros = rand() % (31 + 1 - 0) + 0;
  // blockchain[0] = Block_create(num_leading_zeros, (unsigned char *)"0", "");

  blockchain[0] =
      Block_create(num_leading_zeros, (unsigned char *)"0",
                   "Bob sent Laura 10 bitcoin, Dale sent Harry 7 bitcoin");

  num_leading_zeros = rand() % (31 + 1 - 0) + 0;
  blockchain[1] = Block_create(num_leading_zeros, blockchain[0]->hash,
                               "David sent Bob 12 bitcoin, Windom sent Bob 5 "
                               "bitcoin, Audrey sent Donna 6 bitcoin");

  num_leading_zeros = rand() % (31 + 1 - 0) + 0;
  blockchain[2] = Block_create(num_leading_zeros, blockchain[1]->hash,
                               "Shelly sent Bobby 2 bitcoin");

  int i;

  for (i = 0; i < num_blocks; i++) {
    printf("\nBlock %d:\n", i);
    Block_print(blockchain[i]);
  }
  printf("\n");

  for (i = 0; i < num_blocks; i++) {
    Block_destroy(blockchain[i]);
  }

  return 0;
}
