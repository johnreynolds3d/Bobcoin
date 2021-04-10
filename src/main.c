#include "../lib/headers/bobcoin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));

  printf("\n\n\n\n\n\t\t  ------------------  WELCOME TO TWIN PEAKS  "
         "------------------\n\n");
  printf("\t\t\t\t       Population 51,201\n\n\n\n\n");
  printf("Hi there! Say hello to our friendly local users...\n\n");

  int num_users = 4;
  int num_transactions = 5;
  int num_blocks = 2;

  User *users[num_users];
  Transaction *transactions[num_transactions];
  Block *blockchain[num_blocks];

  char *user_names[] = {"BOB", "Windom Earle", "Laura Palmer", "Dale Cooper"};

  int i;

  for (i = 0; i < num_users; i++) {
    users[i] = User_create(user_names[i], i);
  }

  printf("\n\n\t    ------  Transaction 0 (Genesis): BOB creates the first 100 "
         "bobcoin  ------\n\n");

  users[0]->wallet->balance = 100;

  transactions[0] = Transaction_create(users[0], users[0], 100);

  blockchain[0] = Block_create(&transactions[0], 1, 0);

  printf("\n\n\n\t\t -----  Transaction 1: BOB sends Windom Earle 25 bobcoin  "
         "-----\n\n");
  transactions[1] = Transaction_create(users[0], users[1], 25);

  printf("\n\n\n\t\t -----  Transaction 2: BOB sends Laura Palmer 15 bobcoin  "
         "-----\n\n");
  transactions[2] = Transaction_create(users[0], users[2], 15);

  printf("\n\n\n\t\t -----  Transaction 3: BOB sends Dale Cooper 15 bobcoin  "
         "-----\n\n");
  transactions[3] = Transaction_create(users[0], users[3], 15);

  printf(
      "\n\n\n\t      -----  Transaction 4: Laura Palmer sends Dale Cooper 11 "
      "bobcoin  "
      "-----\n\n");
  transactions[4] = Transaction_create(users[2], users[3], 11);

  blockchain[1] = Block_create(&transactions[1], 4, 1);

  printf("\n\n\n\n");

  for (i = 0; i < num_users; i++) {
    User_destroy(users[i]);
  }

  for (i = 0; i < num_transactions; i++) {
    Transaction_destroy(transactions[i]);
  }

  for (i = 0; i < num_blocks; i++) {
    Block_destroy(blockchain[i]);
  }

  return 0;
}
