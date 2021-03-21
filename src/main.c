#include "../lib/headers/blockchain.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  int num_blocks = 4;

  struct Block *blockchain[num_blocks];

  char *transactions = "";

  int num_leading_zeros = rand() % (7 + 1 - 0) + 0;

  printf("\thash 0:\t\t");

  blockchain[0] =
      Block_create(num_leading_zeros, (unsigned char *)"", transactions);

  transactions = "David sent Bob 12 bitcoin, Windom sent Bob 5 "
                 "bitcoin, Audrey sent Donna 6 bitcoin";

  num_leading_zeros = rand() % (31 + 1 - 0) + 0;

  printf("\thash 1:\t\t");

  blockchain[1] =
      Block_create(num_leading_zeros, blockchain[0]->hash, transactions);

  transactions = "Shelly sent Bobby 2 bitcoin";

  num_leading_zeros = rand() % (31 + 1 - 0) + 0;

  printf("\thash 2:\t\t");

  blockchain[2] =
      Block_create(num_leading_zeros, blockchain[1]->hash, transactions);

  transactions = "Bob sent Laura 10 bitcoin, Dale sent Harry 7 bitcoin";

  num_leading_zeros = rand() % (31 + 1 - 0) + 0;

  printf("\thash 3:\t\t");

  blockchain[3] =
      Block_create(num_leading_zeros, blockchain[2]->hash, transactions);

  int i = 0;

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
