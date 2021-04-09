#include "../lib/headers/bobcoin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  printf("\n\n\n\n\n\t\t  ------------------  WELCOME TO TWIN PEAKS  "
         "------------------\n");
  printf("\n\t\t\t\t        Population 51,201\n\n\n\n");
  printf("\nHi there! Say hello to our friendly local users...\n");
  
  int num_users = 4;
  int num_transactions = 8;
  int num_blocks = 4;

  User *users[num_users];
  Transaction *transactions[num_transactions];
  Block *blockchain[num_blocks];

  char **user_names = {"BOB", "Windom Earle", "Laura Palmer", "Dale Cooper"};

  int i;

  for (i = 0; i < num_users; i++) {
    users[i] = User_create(user_names[i]);
    printf("\nUser %d:", i);
    User_print(users[i]);
  }

  for (i = 0; i < num_transactions; i++) {

    printf("\n\n\t    ------  Transaction %d (Genesis): BOB creates the first 100 "
           "bobcoin  ------\n\n", i);

    users[i]->wallet->balance = 100;
    transactions[i] = Transaction_create(users[i], users[i], 100);
    users[i]->wallet->transactions[i] = transactions[i];
    Transaction_print(transactions[i];
  
    printf("\n\n\t\t\t      -------------------------------------\n");
    printf("\t\t\t                    BLOCK %d\n", block_counter);
    printf("\t\t\t      -------------------------------------");
  
    blockchain[i] = Block_create(&transactions[i], i+1);
    Block_print(blockchain[i]);

  printf("\n\n\t\t -----  Transaction 1: BOB sends Windom Earle 25 bobcoin  "
         "-----\n\n");
  transactions[1] = Transaction_create(users[0], users[1], 25);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[1]);

  printf("\n\n\t\t -----  Transaction 2: BOB sends Laura Palmer 15 bobcoin  "
         "-----\n\n");
  transactions[2] = Transaction_create(users[0], users[2], 15);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[2]);

  printf("\n\n\t\t -----  Transaction 3: BOB sends Dale Cooper 15 bobcoin  "
         "-----\n\n");
  transactions[3] = Transaction_create(users[0], users[3], 15);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[0]);
  printf("\nPayee:");
  User_print(users[3]);

  printf("\n\n\t      -----  Transaction 4: Laura Palmer sends Dale Cooper 11 "
         "bobcoin  "
         "-----\n\n");
  transactions[4] = Transaction_create(users[2], users[3], 11);
  transaction_counter++;

  printf("\nPayer:");
  User_print(users[2]);
  printf("\nPayee:");
  User_print(users[3]);

  printf("\n\n\t\t\t      -------------------------------------\n");
  printf("\t\t\t                    BLOCK %d\n", block_counter);
  printf("\t\t\t      -------------------------------------");
  blockchain[1] = Block_create(
      &transactions[blockchain[block_counter - 1]->transaction_counter],
      transaction_counter - blockchain[block_counter - 1]->transaction_counter);
  Block_print(blockchain[block_counter]);
  block_counter++;

  printf("\n\n\n");

  for (i = 0; i < user_counter; i++) {
    User_destroy(users[i]);
  }

  for (i = 0; i < transaction_counter; i++) {
    free(transactions[i]->payee_address);
    free(transactions[i]->payer_public_key);
    free(transactions[i]->payer_signature);
    free(transactions[i]);
  }

  for (i = 0; i < block_counter; i++) {
    free(blockchain[i]->transactions);
    free(blockchain[i]);
  }

  return 0;
}
