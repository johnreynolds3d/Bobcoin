#include "../lib/headers/blockchain.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  int num_users = 4;

  struct User *users[num_users];

  users[0] = User_create("Laura Palmer");
  users[1] = User_create("Bob");
  users[2] = User_create("Dale Cooper");
  users[3] = User_create("Windom Earle");

  int i = 0;

  for (i = 0; i < num_users; i++) {
    User_print(users[i]);
    Wallet_print(users[i]->wallet);
  }
  printf("\n");

  for (i = 0; i < num_users; i++) {
    User_destroy(users[i]);
  }

  /*
  int num_blocks = 4;

  struct Block *blockchain[num_blocks];

  unsigned char *genesis = calloc((size_t)32, sizeof(char));
  assert(genesis != NULL);


  int num_leading_zeros = rand() % (4 + 1 - 0) + 0;

  char *transactions = "";

  blockchain[0] = Block_create(num_leading_zeros, genesis, transactions);

  if (blockchain[0] == NULL) {
    free(genesis);
    exit(1);
  }

  free(genesis);

  num_leading_zeros = rand() % (4 + 1 - 0) + 0;

  transactions = "David sent Bob 12 bitcoin, Windom sent Bob 5 "
                 "bitcoin, Audrey sent Donna 6 bitcoin";

  blockchain[1] =
      Block_create(num_leading_zeros, blockchain[0]->hash, transactions);

  if (blockchain[1] == NULL) {
    Block_destroy(blockchain[0]);
    exit(1);
  }

  num_leading_zeros = rand() % (4 + 1 - 0) + 0;

  transactions = "Shelly sent Bobby 2 bitcoin";

  blockchain[2] =
      Block_create(num_leading_zeros, blockchain[1]->hash, transactions);

  if (blockchain[2] == NULL) {
    Block_destroy(blockchain[0]);
    Block_destroy(blockchain[1]);
    exit(1);
  }

  num_leading_zeros = rand() % (4 + 1 - 0) + 0;

  transactions = "Bob sent Laura 10 bitcoin, Dale sent Harry 7 bitcoin";

  blockchain[3] =
      Block_create(num_leading_zeros, blockchain[2]->hash, transactions);

  if (blockchain[3] == NULL) {
    Block_destroy(blockchain[0]);
    Block_destroy(blockchain[1]);
    Block_destroy(blockchain[2]);
    exit(1);
  }

  for (int i = 0; i < num_blocks; i++) {
    Block_destroy(blockchain[i]);
  }
  */

  return 0;
}
