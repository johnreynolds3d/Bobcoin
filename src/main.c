#include "../lib/headers/bobcoin.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * A slightly Lynchian implementation of a blockchain, VERY loosely based on the
 * Bitcoin protocol.
 *
 * Author:  John Reynolds
 * Version: 16.01.22
 */

int main() {

  srand(time(NULL));

  puts("\n\n\n\n\t\t  ------------------  WELCOME TO TWIN PEAKS  "
       "------------------\n");
  puts("\t\t\t\t        Population 51,201\n\n\n");
  puts("\t\t   Hi there! Say hello to some of our friendly local users...\n\n");

  const uint_fast8_t num_users = 4;
  const uint_fast8_t num_transactions = 5;
  const uint_fast8_t num_blocks = 2;

  User *users[num_users];
  Transaction *transactions[num_transactions];
  Block *blockchain[num_blocks];

  char *user_names[] = {"BOB", "Windom Earle", "Laura Palmer", "Dale Cooper"};

  register uint_fast8_t i;

  for (i = 0; i < num_users; i++) {
    users[i] = User_create(user_names[i], i);
  }

  puts("\n\n\t    ------  Transaction 0 (Genesis): BOB creates the first 100 "
       "bobcoin  ------\n");

  users[0]->wallet->balance = 100;

  transactions[0] = Transaction_create(users[0], users[0], 100);

  blockchain[0] = Block_create(&transactions[0], 1, 0);

  puts("\n\n\n\t\t -----  Transaction 1: BOB sends Windom Earle 25 bobcoin  "
       "-----\n");

  transactions[1] = Transaction_create(users[0], users[1], 25);

  puts("\n\n\n\t\t -----  Transaction 2: BOB sends Laura Palmer 15 bobcoin  "
       "-----\n");

  transactions[2] = Transaction_create(users[0], users[2], 15);

  puts("\n\n\n\t\t -----  Transaction 3: BOB sends Dale Cooper 15 bobcoin  "
       "-----\n");

  transactions[3] = Transaction_create(users[0], users[3], 15);

  puts("\n\n\n\t      -----  Transaction 4: Laura Palmer sends Dale Cooper 11 "
       "bobcoin  -----\n");

  transactions[4] = Transaction_create(users[2], users[3], 11);

  blockchain[1] = Block_create(&transactions[1], 4, 1);

  puts("\n\n");

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
