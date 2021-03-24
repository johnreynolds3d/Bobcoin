#include "headers/blockchain.h"
#include "headers/sha256.h"
#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char *Hash_create(unsigned char *buffer, char *text) {

  assert(buffer != NULL && text != NULL);

  BYTE hash[SHA256_BLOCK_SIZE] = {
      0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 0x41, 0x41, 0x40,
      0xde, 0x5d, 0xae, 0x22, 0x23, 0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17,
      0x7a, 0x9c, 0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};

  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, (unsigned char *)text, strlen(text));
  sha256_final(&ctx, buffer);

  if (!memcmp(hash, buffer, SHA256_BLOCK_SIZE)) {
    printf("Hashing of '%s' failed\n", text);
    exit(1);
  }

  return buffer;
}

struct User *User_create(char *user_name) {

  assert(user_name != NULL);

  struct User *user = calloc(1, sizeof(struct User));
  assert(user != NULL);

  user->user_name = calloc(strlen(user_name) + 1, sizeof(char));
  assert(user->user_name != NULL);
  strcpy(user->user_name, user_name);

  user->user_public_key = calloc(33, sizeof(char));
  assert(user->user_public_key != NULL);

  char user_public_key[33] = {'a'};

  user_public_key[0] = 'b';
  user_public_key[1] = 'c';
  user_public_key[2] = '1';

  char alphanum[] =
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  int i = 0;

  for (i = 3; i < 32; i++) {
    user_public_key[i] =
        alphanum[rand() % ((strlen(alphanum) - 1) - 0 + 1) + 0];
  }
  user_public_key[32] = '\0';

  strcpy(user->user_public_key, user_public_key);

  user->user_private_key = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(user->user_private_key != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'a'};

  for (i = 0; i < SHA256_BLOCK_SIZE - 2; i++) {
    buffer[i] = (unsigned char)rand() % (255 - 0 + 1) + 0;
  }
  buffer[SHA256_BLOCK_SIZE - 1] = '\0';

  memcpy(user->user_private_key, buffer, SHA256_BLOCK_SIZE);

  user->wallet = Wallet_create(user->user_public_key, user->user_private_key);

  return user;
}

struct Wallet *Wallet_create(char *user_public_key,
                             unsigned char *user_private_key) {

  struct Wallet *wallet = calloc(1, sizeof(struct Wallet));
  assert(wallet != NULL);

  wallet->wallet_address = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(wallet->wallet_address != NULL);

  wallet->wallet_public_key = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(wallet->wallet_public_key != NULL);

  wallet->wallet_private_key = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(wallet->wallet_private_key != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'a'};

  Hash_create(buffer, user_public_key);
  memcpy(wallet->wallet_address, buffer, SHA256_BLOCK_SIZE);

  char *text = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));

  int i = 0;

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    text[i] = user_private_key[i];
  }
  text[SHA256_BLOCK_SIZE] = '\0';

  Hash_create(buffer, text);
  memcpy(wallet->wallet_public_key, buffer, SHA256_BLOCK_SIZE);

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    text[i] = wallet->wallet_address[i];
  }
  text[SHA256_BLOCK_SIZE] = '\0';

  Hash_create(buffer, text);
  memcpy(wallet->wallet_private_key, buffer, SHA256_BLOCK_SIZE);

  free(text);

  wallet->balance = 0;

  // wallet->transactions = calloc(4, sizeof(struct Transaction));
  // assert(wallet->transactions != NULL);

  return wallet;
}

void User_print(struct User *user) {

  assert(user != NULL);

  printf("\nUser:\n");
  printf("\tuser name:\t\t%s\n", user->user_name);
  printf("\tuser public key:\t%s\n", user->user_public_key);
  printf("\tuser private key:\t");
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->user_private_key[i]);
  }
  printf("\n");
}

void Wallet_print(struct Wallet *wallet) {

  assert(wallet != NULL);

  printf("\nWallet:\n");

  int i = 0;

  printf("\twallet address:\t\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", wallet->wallet_address[i]);
  }
  printf("\n");

  printf("\twallet public key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", wallet->wallet_public_key[i]);
  }
  printf("\n");

  printf("\twallet private key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", wallet->wallet_private_key[i]);
  }
  printf("\n");

  printf("\twallet balance:\t\t%d\n", wallet->balance);
}

void User_destroy(struct User *user) {

  assert(user != NULL);

  free(user->wallet->wallet_address);
  free(user->wallet->wallet_public_key);
  free(user->wallet->wallet_private_key);
  free(user->wallet);

  free(user->user_name);
  free(user->user_public_key);
  free(user->user_private_key);
  free(user);
}

/*
struct Header *Header_create(int target, unsigned char *prev_hash,
                             struct Transaction **transactions[]) {

  assert(prev_hash != NULL && transactions != NULL);

  struct Header *header = calloc(1, sizeof(struct Header));
  assert(header != NULL);

  // ------------------------------- TIMESTAMP ---------------------------------
  time_t current_time = time(NULL);

  struct tm *time_info = gmtime(&current_time);

  char *gmt = asctime(time_info);

  header->timestamp = calloc(strlen(gmt) + 1, sizeof(char));
  assert(header->timestamp != NULL);

  strcpy(header->timestamp, gmt);

  // --------------------------------- NONCE -----------------------------------
  printf("\nLooking for exactly %d leading zeros...\n\n", target);

  header->nonce = rand() % (((int)pow(2, 32) - 1) + 1 - 0) + 0;

  int num_digits = floor((int)log10(fabs((double)header->nonce))) + 1;

  char *nonce = calloc(num_digits + 1, sizeof(char));
  assert(nonce != NULL);

  sprintf(nonce, "%d", header->nonce);
  printf("\tnonce:\t\t%s\n", nonce);

  // ------------------------------- PREV_HASH ---------------------------------
  header->prev_hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(header->prev_hash != NULL);
  memcpy(header->prev_hash, prev_hash, SHA256_BLOCK_SIZE);

  // ------------------------------- ROOT_HASH ---------------------------------
  block->transactions = calloc(strlen(transactions) + 1, sizeof(char));
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  block->hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block->hash != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'a'};

  char *text =
      calloc(strlen(transactions) + 1 + strlen(nonce) + 1, sizeof(char));
  assert(text != NULL);

  memcpy(text, transactions, strlen(transactions) + 1);
  strcat(text, nonce);

  printf("\ttext:\t\t%s", text);

  Hash(buffer, transactions);

  memcpy(block->hash, buffer, SHA256_BLOCK_SIZE);

  free(text);
  free(nonce);

  // ------------------------------- ZERO TEST ---------------------------------
  int i = 0;
  int j = 0;
  int k = 0;

  int zero_test[256] = {2};

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    for (j = 7; j >= 0; --j) {
      zero_test[k] = ((block->hash[i] & (1 << j)) ? 1 : 0);
      k++;
    }
  }
  printf("\n");

  printf("\tzero_test:\t");

  if (target > 0) {
    for (i = 0; i < target; i++) {
      printf("%d", zero_test[i]);
    }
  }

  printf("\n\n");

  if (target == 0 && zero_test[0] == 1) {
    printf(
        "\t\t************ Found exactly %d leading zeros!!! ************\n\n",
        target);
    Block_print(block);
    return block;
  }

  for (i = 0; i < target; i++) {

    if (zero_test[i] != 0) {
      printf("Found fewer than %d leading zeros; try again!\n\n", target);
      break;
    }

    if (i == target - 1) {
      if (zero_test[target] != 1) {
        printf("Found more than %d leading zeros; try again!\n\n", target);
        break;
      } else {
        printf("\t\t************ Found exactly %d leading zeros!!! "
               "************\n\n",
               target);
        Block_print(block);
        return block;
      }
    }
  }
}

struct Block *Block_create(int target, unsigned char *prev_hash,
                           struct Transaction **transactions[]) {

  assert(prev_hash != NULL && transactions != NULL);

  struct Block *block = calloc(1, sizeof(struct Block));
  assert(block != NULL);

  block->header = Header_create(target, *prev_hash, **transactions[]);
  // ----------------------------- TRANSACTIONS --------------------------------
  block->transactions = calloc(strlen(transactions) + 1, sizeof(char));
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  block->hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block->hash != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'a'};

  char *text =
      calloc(strlen(transactions) + 1 + strlen(nonce) + 1, sizeof(char));
  assert(text != NULL);

  memcpy(text, transactions, strlen(transactions) + 1);
  strcat(text, nonce);

  printf("\ttext:\t\t%s", text);

  Hash(buffer, transactions);

  memcpy(block->hash, buffer, SHA256_BLOCK_SIZE);

  // ----------------------------- TRANSACTIONS --------------------------------
  block->transactions = calloc(strlen(transactions) + 1, sizeof(char));
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  block->hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block->hash != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'a'};

  char *text =
      calloc(strlen(transactions) + 1 + strlen(nonce) + 1, sizeof(char));
  assert(text != NULL);

  memcpy(text, transactions, strlen(transactions) + 1);
  strcat(text, nonce);

  printf("\ttext:\t\t%s", text);

  Hash(buffer, transactions);

  memcpy(block->hash, buffer, SHA256_BLOCK_SIZE);

  return NULL;
}

void Block_print(struct Block *block) {

  assert(block != NULL);

  printf("\ttimestamp:\t%s", block->header->timestamp);

  int i = 0;
  int j = 0;

  printf("\tprev_hash:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", block->header->prev_hash[i]);
  }
  printf("\n");

  printf("\ttransactions:\t%s\n", block->transactions);

  printf("\ttx_hash:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", block->hash[i]);
  }
  printf("\n");

  printf("\ttx_hash binary:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    for (j = 7; j >= 0; --j) {
      putchar((block->hash[i] & (1 << j)) ? '1' : '0');
    }
  }
  printf("\n");
}

void Block_destroy(struct Block *block) {

  assert(block != NULL);

  free(block->header->timestamp);
  // free(block->transactions);
  // free(block->prev_hash);
  // free(block->hash);

  free(block->header);

  free(block);
}
*/
