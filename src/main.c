#include "../lib/headers/blockchain.h"
#include "../lib/headers/sha256.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  unsigned int i = 0;

  // -------------------------------- USERS -----------------------------------

  unsigned int num_users = 4;

  struct User *users[num_users];

  printf("\n\n\t\t\t---------------- WELCOME TO TWIN PEAKS ----------------\n");
  printf("\n\t\t\t\t\t   Population 51,201\n");
  printf("\nSay hello to our users!\n");

  users[0] = User_create((unsigned char *)"BOB");
  users[1] = User_create((unsigned char *)"Windom Earle");
  users[2] = User_create((unsigned char *)"Laura Palmer");
  users[3] = User_create((unsigned char *)"Dale Cooper");

  printf(
      "\nTransaction 0: BOB (AKA... SATOSHI NAKAMOTO!) creates the first 100 "
      "coins...\n");

  users[0]->wallet->balance = 100;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[0]);

  //------------------------------ TRANSACTIONS --------------------------------

  unsigned int num_transactions = 2;

  struct Transaction *transactions[num_transactions];

  printf("\nTransaction 1: BOB sends Windom Earle 25 coins...\n");

  transactions[0] = Transaction_create(users[0], users[1], 25);

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[1]);

  printf("\nTransaction 2: BOB sends Laura 10 coins...\n");

  transactions[1] = Transaction_create(users[0], users[2], 10);

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[2]);

  /*

  //-------------------------------- BLOCKS ------------------------------------

  unsigned int num_blocks = 2;

  struct Block *blockchain[num_blocks];

  unsigned int bits = rand() % (4 + 1 - 0) + 0;

  blockchain[0] = Block_create(genesis, bits, transactions);

  if (blockchain[0] == NULL) {
    free(genesis);
    exit(1);
  }

  free(signature);

  bits = rand() % (4 + 1 - 0) + 0;

  transactions = "David sent Bob 12 bitcoin, Windom sent Bob 5 "
                 "bitcoin, Audrey sent Donna 6 bitcoin";

  blockchain[1] = Block_create(bits, blockchain[0]->hash, transactions);

  if (blockchain[1] == NULL) {
    Block_destroy(blockchain[0]);
    exit(1);
  }

  bits = rand() % (4 + 1 - 0) + 0;

  transactions = "Shelly sent Bobby 2 bitcoin";

  blockchain[2] = Block_create(bits, blockchain[1]->hash, transactions);

  if (blockchain[2] == NULL) {
    Block_destroy(blockchain[0]);
    Block_destroy(blockchain[1]);
    exit(1);
  }

  bits = rand() % (4 + 1 - 0) + 0;

  transactions = "Bob sent Laura 10 bitcoin, Dale sent Harry 7 bitcoin";

  blockchain[3] = Block_create(bits, blockchain[2]->hash, transactions);
  */

  // --------------------------------- CLEANUP ---------------------------------

  printf("\n");

  for (i = 0; i < num_users; i++) {
    User_destroy(users[i]);
  }

  for (i = 0; i < num_transactions; i++) {
    free(transactions[i]->payee_address);
    free(transactions[i]->payer_public_key);
    free(transactions[i]->payer_signature);
    free(transactions[i]);
  }

  /*
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
