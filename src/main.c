#include "../lib/headers/blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  printf("\n\n\n\n\t\t\t----------------  WELCOME TO TWIN PEAKS  "
         "----------------\n");
  printf("\n\t\t\t\t\t    Population 51,201\n\n\n");
  printf("\nHi there! Say hello to our friendly local users...\n\n");

  struct User **users = calloc(1, sizeof(struct User));
  struct Transaction **transactions = calloc(1, sizeof(struct Transaction));
  struct Block **blockchain = calloc(1, sizeof(struct Block));

  unsigned long user_counter = 0;
  unsigned long transaction_counter = 0;
  unsigned long block_counter = 0;

  users[0] = User_create((unsigned char *)"BOB");
  user_counter++;

  users[1] = User_create((unsigned char *)"Windom Earle");
  user_counter++;

  users[2] = User_create((unsigned char *)"Laura Palmer");
  user_counter++;

  users[3] = User_create((unsigned char *)"Dale Cooper");
  user_counter++;

  unsigned int i = 0;

  for (i = 0; i < user_counter; i++) {
    User_print(users[i]);
  }

  printf(
      "\n\n\n  -----  Transaction 0 (Genesis): BOB (AKA... SATOSHI NAKAMOTO!) "
      "creates "
      "the first 100 "
      "coins  -----\n\n");
  users[0]->wallet->balance = 100;
  transactions[0] = Transaction_create(users[0], users[0], 100);
  users[0]->wallet->transactions[0] = transactions[0];
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[0]);

  blockchain[0] = Block_create(&transactions[0], transaction_counter);
  Block_print(blockchain[block_counter]);
  block_counter++;

  printf("\n\n\n\t\t -----  Transaction 1: BOB sends Windom Earle 25 coins  "
         "-----\n\n");
  transactions[1] = Transaction_create(users[0], users[1], 25);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[1]);

  printf("\n\n\n\t\t -----  Transaction 2: BOB sends Laura Palmer 15 coins  "
         "-----\n\n");
  transactions[2] = Transaction_create(users[0], users[2], 15);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[2]);

  printf("\n\n\n\t\t -----  Transaction 3: BOB sends Dale Cooper 15 coins  "
         "-----\n\n");
  transactions[3] = Transaction_create(users[0], users[3], 15);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[3]);

  /*
  printf("\n\n\n\t\t -----  Transaction 4: Laura Palmer sends Dale Cooper 11 "
         "coins  "
         "-----\n\n");
  transactions[4] = Transaction_create(users[2], users[3], 11);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[2]);
  printf("\nPayee:");
  User_print(users[3]);
  */

  blockchain[1] = Block_create(
      &transactions[blockchain[block_counter - 1]->transaction_counter],
      transaction_counter - blockchain[block_counter - 1]->transaction_counter);
  Block_print(blockchain[block_counter]);
  block_counter++;

  printf("\n\n\n");

  for (i = 0; i < user_counter; i++) {
    User_destroy(users[i]);
  }
  free(users);

  for (i = 0; i < transaction_counter; i++) {
    free(transactions[i]->payee_address);
    free(transactions[i]->payer_public_key);
    free(transactions[i]->payer_signature);
    free(transactions[i]);
  }
  free(transactions);

  for (int i = 0; i < block_counter; i++) {
    // Block_destroy(blockchain[i]);
    free(blockchain[i]->transactions);
    free(blockchain[i]);
  }
  free(blockchain);

  return 0;
}
