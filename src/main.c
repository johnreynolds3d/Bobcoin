#include "../lib/headers/blockchain.h"
#include "../lib/headers/sha256.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  printf("\n\n\t\t\t---------------- WELCOME TO TWIN PEAKS ----------------\n");
  printf("\n\t\t\t\t\t   Population 51,201\n");
  printf("\nSay hello to our users!\n");

  struct User *users[4];
  struct Transaction *transactions[3];
  struct Block *blockchain[2];

  unsigned long user_counter = 0;
  unsigned long transaction_counter = 0;
  unsigned long block_counter = 0;

  users[0] = User_create((unsigned char *)"BOB");
  assert(users[0] != NULL);
  user_counter++;

  users[1] = User_create((unsigned char *)"Windom Earle");
  assert(users[1] != NULL);
  user_counter++;

  users[2] = User_create((unsigned char *)"Laura Palmer");
  assert(users[2] != NULL);
  user_counter++;

  users[3] = User_create((unsigned char *)"Dale Cooper");
  assert(users[3] != NULL);
  user_counter++;

  unsigned int i = 0;

  for (i = 0; i < user_counter; i++) {
    User_print(users[i]);
  }

  printf("\nTransaction 0 (Genesis): BOB (AKA... SATOSHI NAKAMOTO!) creates "
         "the first 100 "
         "coins...\n");
  users[0]->wallet->balance = 100;
  transactions[0] = Transaction_create(users[0], users[0], 100);
  assert(transactions[0] != NULL);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[0]);

  blockchain[0] = Block_create(&transactions[0], transaction_counter);
  assert(blockchain[0] != NULL);
  Block_print(blockchain[block_counter]);
  block_counter++;

  printf("\nTransaction 1: BOB sends Windom Earle 25 coins...\n");
  transactions[1] = Transaction_create(users[0], users[1], 25);
  assert(transactions[1] != NULL);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[1]);

  printf("\nTransaction 2: BOB sends Laura 10 coins...\n");

  transactions[2] = Transaction_create(users[0], users[2], 10);
  assert(transactions[2] != NULL);

  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[2]);

  blockchain[1] = Block_create(
      &transactions[blockchain[block_counter - 1]->transaction_counter],
      transaction_counter - blockchain[block_counter - 1]->transaction_counter);
  assert(blockchain[1] != NULL);
  Block_print(blockchain[block_counter]);
  block_counter++;

  printf("\n");

  for (i = 0; i < user_counter; i++) {
    User_destroy(users[i]);
  }

  for (i = 0; i < transaction_counter; i++) {
    free(transactions[i]->payee_address);
    free(transactions[i]->payer_public_key);
    free(transactions[i]->payer_signature);
    free(transactions[i]);
  }

  for (int i = 0; i < block_counter; i++) {
    // Block_destroy(blockchain[i]);
    free(blockchain[i]->transactions);
    free(blockchain[i]);
  }

  return 0;
}
