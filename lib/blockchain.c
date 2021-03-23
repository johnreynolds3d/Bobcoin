#include "headers/blockchain.h"
#include "headers/sha256.h"
#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct User *User_create(char *name) {

  assert(name != NULL);

  struct User *user = calloc(1, sizeof(struct User));
  assert(user != NULL);

  user->name = calloc(strlen(name) + 1, sizeof(char));
  assert(user->name != NULL);
  strcpy(user->name, name);

  user->public_key = calloc(33, sizeof(char));
  assert(user->public_key != NULL);

  char public_key[33] = {'a'};

  public_key[0] = 'b';
  public_key[1] = 'c';
  public_key[2] = '1';

  char alphanum[] =
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  int i = 0;

  for (i = 3; i < 32; i++) {
    public_key[i] = alphanum[rand() % ((strlen(alphanum) - 1) - 0 + 1) + 0];
  }
  public_key[32] = '\0';

  strcpy(user->public_key, public_key);

  user->private_key = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(user->private_key != NULL);

  BYTE buf[SHA256_BLOCK_SIZE] = {'a'};

  for (i = 0; i < SHA256_BLOCK_SIZE - 1; i++) {
    buf[i] = (unsigned char)rand() % (255 - 0 + 1) + 0;
  }
  buf[SHA256_BLOCK_SIZE] = '\0';

  memcpy(user->private_key, buf, SHA256_BLOCK_SIZE);

  user->wallet = Wallet_create(user->public_key, user->private_key);

  return user;
}

void User_print(struct User *user) {

  assert(user != NULL);

  printf("\nUser:\n");
  printf("\tname:\t\t%s\n", user->name);
  printf("\tpublic key:\t%s\n", user->public_key);

  printf("\tprivate key:\t");
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->private_key[i]);
  }
  printf("\n");
}

void User_destroy(struct User *user) {

  assert(user != NULL);

  free(user->wallet->address);
  free(user->wallet->public_key);
  free(user->wallet->private_key);

  free(user->name);
  free(user->public_key);
  free(user->private_key);

  free(user->wallet);
  free(user);
}

unsigned char *Hash_create(unsigned char *buf, char *text) {

  assert(buf != NULL && text != NULL);

  BYTE hash[SHA256_BLOCK_SIZE] = {
      0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 0x41, 0x41, 0x40,
      0xde, 0x5d, 0xae, 0x22, 0x23, 0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17,
      0x7a, 0x9c, 0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};

  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, (unsigned char *)text, strlen(text));
  sha256_final(&ctx, buf);

  if (!memcmp(hash, buf, SHA256_BLOCK_SIZE)) {
    printf("Hashing of '%s' failed\n", text);
    exit(1);
  }

  return buf;
}

struct Wallet *Wallet_create(char *public_key, unsigned char *private_key) {

  struct Wallet *wallet = calloc(1, sizeof(struct Wallet));
  assert(wallet != NULL);

  wallet->address = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(wallet->address != NULL);

  wallet->public_key = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(wallet->public_key != NULL);

  wallet->private_key = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(wallet->private_key != NULL);

  BYTE buf[SHA256_BLOCK_SIZE] = {'a'};

  Hash_create(buf, public_key);
  memcpy(wallet->address, buf, SHA256_BLOCK_SIZE);

  char *text = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));

  int i = 0;

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    text[i] = private_key[i];
  }
  text[SHA256_BLOCK_SIZE] = '\0';

  Hash_create(buf, text);
  memcpy(wallet->public_key, buf, SHA256_BLOCK_SIZE);

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    text[i] = wallet->address[i];
  }
  text[SHA256_BLOCK_SIZE] = '\0';

  Hash_create(buf, text);
  memcpy(wallet->private_key, buf, SHA256_BLOCK_SIZE);

  free(text);

  wallet->balance = 0;

  // wallet->transactions = calloc(4, sizeof(struct Transaction));
  // assert(wallet->transactions != NULL);
}

void Wallet_print(struct Wallet *wallet) {

  assert(wallet != NULL);

  printf("\nWallet:\n");

  int i = 0;

  printf("\taddress:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", wallet->address[i]);
  }
  printf("\n");

  printf("\tpublic key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", wallet->public_key[i]);
  }
  printf("\n");

  printf("\tprivate key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", wallet->private_key[i]);
  }
  printf("\n");

  printf("\tbalance:\t%d\n", wallet->balance);
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

  BYTE buf[SHA256_BLOCK_SIZE] = {'a'};

  char *text =
      calloc(strlen(transactions) + 1 + strlen(nonce) + 1, sizeof(char));
  assert(text != NULL);

  memcpy(text, transactions, strlen(transactions) + 1);
  strcat(text, nonce);

  printf("\ttext:\t\t%s", text);

  Hash(buf, transactions);

  memcpy(block->hash, buf, SHA256_BLOCK_SIZE);

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

  BYTE buf[SHA256_BLOCK_SIZE] = {'a'};

  char *text =
      calloc(strlen(transactions) + 1 + strlen(nonce) + 1, sizeof(char));
  assert(text != NULL);

  memcpy(text, transactions, strlen(transactions) + 1);
  strcat(text, nonce);

  printf("\ttext:\t\t%s", text);

  Hash(buf, transactions);

  memcpy(block->hash, buf, SHA256_BLOCK_SIZE);

  // ----------------------------- TRANSACTIONS --------------------------------
  block->transactions = calloc(strlen(transactions) + 1, sizeof(char));
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  block->hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block->hash != NULL);

  BYTE buf[SHA256_BLOCK_SIZE] = {'a'};

  char *text =
      calloc(strlen(transactions) + 1 + strlen(nonce) + 1, sizeof(char));
  assert(text != NULL);

  memcpy(text, transactions, strlen(transactions) + 1);
  strcat(text, nonce);

  printf("\ttext:\t\t%s", text);

  Hash(buf, transactions);

  memcpy(block->hash, buf, SHA256_BLOCK_SIZE);

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
