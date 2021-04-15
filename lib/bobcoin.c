#include "headers/bobcoin.h"
#include "headers/ecdsa.h"
#include "headers/sha256.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char *GetHash(unsigned char *buffer, unsigned char *text) {

  assert(buffer != NULL && text != NULL);

  unsigned char hash[SHA256_BLOCK_SIZE] = {
      0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 0x41, 0x41, 0x40,
      0xde, 0x5d, 0xae, 0x22, 0x23, 0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17,
      0x7a, 0x9c, 0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};

  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, text, strlen((const char *)(text)));
  sha256_final(&ctx, buffer);

  if (!memcmp(hash, buffer, SHA256_BLOCK_SIZE)) {
    printf("Hashing of '%s' failed\n", text);
    exit(1);
  }

  return buffer;
}

User *User_create(char *name, int user_counter) {

  assert(name != NULL);

  User *user = malloc(sizeof(User));
  assert(user != NULL);

  user->name = malloc((strlen((const char *)(name)) + 1) * sizeof(char));
  assert(user->name != NULL);

  user->public_key = malloc(((SHA256_BLOCK_SIZE * 2) + 1) * sizeof(char));
  assert(user->public_key != NULL);

  user->private_key = malloc((SHA256_BLOCK_SIZE + 1) * sizeof(char));
  assert(user->private_key != NULL);

  memcpy(user->name, name, strlen((const char *)(name)) + 1);

  char alphanum[] = "0123456789abcdef";

  user->public_key[0] = 'b';
  user->public_key[1] = 'c';
  user->public_key[2] = '1';

  int i;

  for (i = 3; i < SHA256_BLOCK_SIZE * 2; i++) {
    user->public_key[i] =
        alphanum[rand() % ((strlen((char *)(alphanum)) - 1) - 0 + 1) + 0];
  }
  user->public_key[SHA256_BLOCK_SIZE * 2] = '\0';

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    user->private_key[i] = rand() % (255 - 0 + 1) + 0;
  }
  user->private_key[SHA256_BLOCK_SIZE] = '\0';

  user->wallet = Wallet_create(user);

  User_print(user, user_counter);

  return user;
}

Wallet *Wallet_create(User *user) {

  assert(user != NULL);

  Wallet *wallet = malloc(sizeof(Wallet));
  assert(wallet != NULL);

  wallet->address = malloc((SHA256_BLOCK_SIZE + 1) * sizeof(char));
  assert(wallet->address != NULL);

  wallet->public_key = malloc((SHA256_BLOCK_SIZE + 1) * sizeof(char));
  assert(wallet->public_key != NULL);

  wallet->private_key = malloc((SHA256_BLOCK_SIZE + 1) * sizeof(char));
  assert(wallet->private_key != NULL);

  wallet->transactions = malloc(8 * sizeof(Transaction));
  assert(wallet->transactions != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'0'};

  GetHash(buffer, user->public_key);
  memcpy(wallet->address, buffer, SHA256_BLOCK_SIZE);

  GetHash(buffer, user->private_key);
  memcpy(wallet->public_key, buffer, SHA256_BLOCK_SIZE);

  GetHash(buffer, wallet->address);
  memcpy(wallet->private_key, buffer, SHA256_BLOCK_SIZE);

  wallet->balance = 0;

  return wallet;
}

Transaction *Transaction_create(User *payer, User *payee, unsigned int amount) {

  assert(payer != NULL && payee != NULL);

  Transaction *transaction = malloc(sizeof(Transaction));
  assert(transaction != NULL);

  transaction->payee_address = malloc((SHA256_BLOCK_SIZE + 1) * sizeof(char));
  assert(transaction->payee_address != NULL);

  transaction->payer_public_key =
      malloc(((SHA256_BLOCK_SIZE * 2) + 1) * sizeof(char));
  assert(transaction->payer_public_key != NULL);

  transaction->payer_signature = malloc(65 * sizeof(char));
  assert(transaction->payer_signature != NULL);

  memcpy(transaction->payee_address, payee->wallet->address, SHA256_BLOCK_SIZE);
  memcpy(transaction->payer_public_key, payer->public_key,
         SHA256_BLOCK_SIZE * 2);

  printf("\n  Transaction pending:\n\n");

  int size_amount = snprintf(NULL, 0, "%d", amount);
  assert(size_amount > 0);

  char amount_buffer[size_amount + 1];
  snprintf((char *)amount_buffer, size_amount + 1, "%d", amount);
  printf("\ttransaction amount:\t%s BOB\n", amount_buffer);

  int size_time = snprintf(NULL, 0, "%lu", (unsigned long)time(NULL));
  assert(size_time > 0);

  char time_buffer[size_time];
  snprintf((char *)time_buffer, size_time, "%lu", (unsigned long)time(NULL));
  printf("\ttransaction time:\t%s (seconds since 1970-01-01T00:00:00Z)\n",
         time_buffer);

  unsigned char *text_buffer =
      malloc((SHA256_BLOCK_SIZE + size_time + size_amount) * sizeof(char));
  assert(text_buffer != NULL);

  memcpy(text_buffer, transaction->payee_address, SHA256_BLOCK_SIZE);

  strncat((char *)text_buffer, (const char *)time_buffer,
          sizeof(text_buffer) - strlen((const char *)text_buffer) - 1);

  strncat((char *)text_buffer, (const char *)amount_buffer,
          sizeof(text_buffer) - strlen((const char *)text_buffer) - 1);

  unsigned char hash_buffer[SHA256_BLOCK_SIZE] = {'0'};

  GetHash(hash_buffer, text_buffer);

  printf("\ttransaction hash:\t");
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", hash_buffer[i]);
  }
  printf("\n");

  unsigned long *signature_buffer = malloc(2 * sizeof(long));
  assert(signature_buffer != 0);

  GetSignature((long)hash_buffer, signature_buffer);

  transaction->amount = amount;

  payee->wallet->balance += amount;
  payer->wallet->balance -= amount;

  if (payee->wallet->transactions[0] == NULL) {
    payee->wallet->transactions[0] = transaction;
  } else {
    payee->wallet->transactions[1] = transaction;
  }

  if (payer->wallet->transactions[0] == NULL) {
    payer->wallet->transactions[0] = transaction;
  } else {
    payer->wallet->transactions[1] = transaction;
  }

  free(text_buffer);
  free(signature_buffer);

  Transaction_print(transaction);

  return transaction;
}

Block *Block_create(Transaction **transactions, int transaction_counter,
                    int block_counter) {

  assert(transactions != NULL);

  Block *block = malloc(sizeof(Block));
  assert(block != NULL);

  *(unsigned long *)&block->magic_number = 0xD9B4BEF9UL;

  block->transaction_counter = transaction_counter;

  block->transactions = malloc(8 * sizeof(Transaction));
  assert(block->transactions != NULL);

  for (int i = 0; i < transaction_counter; i++) {
    block->transactions[i] = transactions[i];
  }

  Block_print(block, block_counter);

  return block;
}

void User_print(User *user, int user_counter) {

  assert(user != NULL);

  printf("\nUser %d:\n", user_counter);
  printf("\tuser name:\t\t%s\n", user->name);
  printf("\tuser public key:\t%s\n", user->public_key);
  printf("\tuser private key:\t");
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->private_key[i]);
  }
  printf("\n");

  Wallet_print(user);
}

void Wallet_print(User *user) {

  assert(user != NULL);

  int i;

  printf("\n\twallet address:\t\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->wallet->address[i]);
  }
  printf("\n");

  printf("\twallet public key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->wallet->public_key[i]);
  }
  printf("\n");

  printf("\twallet private key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->wallet->private_key[i]);
  }
  printf("\n");

  if (user->wallet->transactions[0] == NULL) {
    printf("\n      wallet transactions:\tN/A\n");
  } else {
    printf("\n      wallet transactions:\n");
    for (i = 0; user->wallet->transactions[i] != NULL; i++)
      Transaction_print(user->wallet->transactions[i]);
  }
  printf("\n");

  printf("      wallet balance:\t\t%d BOB\n\n", user->wallet->balance);
}

void Transaction_print(Transaction *transaction) {

  assert(transaction != NULL);

  printf("\n\n\tpayee wallet address:\t");
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", transaction->payee_address[i]);
  }
  printf("\n");

  printf("\ttransaction amount:\t%d BOB\n", transaction->amount);
  printf("\tpayer public key:\t%s\n", transaction->payer_public_key);
}

void Block_print(Block *block, int block_counter) {

  assert(block != NULL);

  printf("\n\n\t\t\t       -------------------------------------\n");
  printf("\t\t\t                     BLOCK %d\n", block_counter);
  printf("\t\t\t       -------------------------------------\n\n");

  // printf("\n    Transaction counter:\t%d\n\n", block->transaction_counter);

  printf("\n  Block transactions:");

  for (int i = 0; i < block->transaction_counter; i++) {
    Transaction_print(block->transactions[i]);
  }
}

void Transaction_destroy(Transaction *transaction) {

  assert(transaction != NULL);

  free(transaction->payer_signature);
  free(transaction->payer_public_key);
  free(transaction->payee_address);

  free(transaction);
}

void Block_destroy(Block *block) {

  assert(block != NULL);

  free(block->transactions);
  free(block);
}

void User_destroy(User *user) {

  assert(user != NULL);

  free(user->wallet->transactions);
  free(user->wallet->private_key);
  free(user->wallet->public_key);
  free(user->wallet->address);
  free(user->wallet);

  free(user->private_key);
  free(user->public_key);
  free(user->name);
  free(user);
}
