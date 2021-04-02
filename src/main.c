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

  users[0] = User_create("BOB");
  assert(users[0] != NULL);

  users[1] = User_create("Windom Earle");
  assert(users[1] != NULL);

  users[2] = User_create("Laura Palmer");
  assert(users[2] != NULL);

  users[3] = User_create("Dale Cooper");
  assert(users[3] != NULL);

  //------------------------------ TRANSACTIONS --------------------------------

  unsigned int num_transactions = 3;

  struct Transaction *transactions[num_transactions];

  printf("\nTransaction 0 (Genesis): BOB (AKA... SATOSHI NAKAMOTO!) creates "
         "the first 100 "
         "coins...\n");

  users[0]->wallet->balance = 100;

  transactions[0] = Transaction_create(users[0], users[0], 100);
  assert(transactions[0] != NULL);

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[0]);

  printf("\nTransaction 1: BOB sends Windom Earle 25 coins...\n");

  transactions[1] = Transaction_create(users[0], users[1], 25);
  assert(transactions[1] != NULL);

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[1]);

  printf("\nTransaction 2: BOB sends Laura 10 coins...\n");

  transactions[2] = Transaction_create(users[0], users[2], 10);
  assert(transactions[2] != NULL);

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[2]);

  /*
  //-------------------------------- BLOCKS ------------------------------------

  unsigned int num_blocks = 2;

  struct Block *blockchain[num_blocks];

  unsigned long bits = rand() % (4 + 1 - 0) + 0;

  blockchain[0] = Block_create("", bits, transactions);
  assert(blockchain[0] != NULL);

  bits = rand() % (4 + 1 - 0) + 0;

  blockchain[1] = Block_create(bits, blockchain[0]->hash, transactions);
  assert(transactions[1] != NULL);
  */

  // ------------------------------ CLEANUP ------------------------------------

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
  for (int i = 0; i < num_blocks; i++) {
    Block_destroy(blockchain[i]);
  }
  */

  return 0;
}
