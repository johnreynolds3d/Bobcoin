#include "headers/blockchain.h"
#include "headers/sha256.h"
#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct User *User_create(char *public_key, char *private_key, char *name) {

  assert(public_key != NULL && private_key != NULL && name != NULL);

  struct User *user = calloc(1, sizeof(struct User));
  assert(user != NULL);

  user->public_key = calloc(strlen(public_key) + 1, sizeof(char));
  assert(user->public_key != NULL);
  strcpy(user->public_key, public_key);

  user->private_key = calloc(strlen(private_key) + 1, sizeof(char));
  assert(user->private_key != NULL);
  strcpy(user->private_key, private_key);

  user->public_key = calloc(strlen(name) + 1, sizeof(char));
  assert(user->name != NULL);
  strcpy(user->name, name);

  return user;
}

void User_print(struct User *user) {

  assert(user != NULL);

  printf("\tname:\t%s\n", user->name);
  printf("\tpublic_key:\t%s\n", user->public_key);
  printf("\tprivate_key:\t%s\n", user->private_key);
}

void User_destroy(struct User *user) {

  assert(user != NULL);

  free(user->public_key);
  free(user->private_key);
  free(user->name);

  free(user);
}

unsigned char *Hash(unsigned char *buf, char *text) {

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

struct Block *Block_create(int num_leading_zeros, unsigned char *previous_hash,
                           char *transactions) {

  assert(previous_hash != NULL && transactions != NULL);

  struct Block *block = calloc(1, sizeof(struct Block));
  assert(block != NULL);

  printf("\nLooking for exactly %d leading zeros...\n\n", num_leading_zeros);

  // --------------------------------- NONCE -----------------------------------
  block->nonce = rand() % (((int)pow(2, 32) - 1) + 1 - 0) + 0;

  int num_digits = floor((int)log10(fabs((double)block->nonce))) + 1;

  char *nonce = calloc(num_digits + 1, sizeof(char));
  assert(nonce != NULL);

  sprintf(nonce, "%d", block->nonce);
  printf("\tnonce:\t\t%s\n", nonce);

  // ------------------------------ TRANSACTIONS -------------------------------
  block->transactions = calloc(strlen(transactions) + 1, sizeof(char));
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  // ------------------------------- PREV_HASH ---------------------------------
  block->previous_hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block->previous_hash != NULL);
  memcpy(block->previous_hash, previous_hash, SHA256_BLOCK_SIZE);

  // -------------------------------- TX_HASH ----------------------------------
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

  // ------------------------------- TIMESTAMP ---------------------------------
  time_t current_time = time(NULL);

  struct tm *time_info = gmtime(&current_time);

  char *gmt = asctime(time_info);

  block->timestamp = calloc(strlen(gmt) + 1, sizeof(char));
  assert(block->timestamp != NULL);
  strcpy(block->timestamp, gmt);

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

  if (num_leading_zeros > 0) {
    for (i = 0; i < num_leading_zeros; i++) {
      printf("%d", zero_test[i]);
    }
  }

  printf("\n\n");

  if (num_leading_zeros == 0 && zero_test[0] == 1) {
    printf(
        "\t\t************ Found exactly %d leading zeros!!! ************\n\n",
        num_leading_zeros);
    Block_print(block);
    return block;
  }

  for (i = 0; i < num_leading_zeros; i++) {

    if (zero_test[i] != 0) {
      printf("Found fewer than %d leading zeros; try again!\n\n",
             num_leading_zeros);
      break;
    }

    if (i == num_leading_zeros - 1) {
      if (zero_test[num_leading_zeros] != 1) {
        printf("Found more than %d leading zeros; try again!\n\n",
               num_leading_zeros);
        break;
      } else {
        printf("\t\t************ Found exactly %d leading zeros!!! "
               "************\n\n",
               num_leading_zeros);
        Block_print(block);
        return block;
      }
    }
  }

  Block_destroy(block);

  return NULL;
}

void Block_print(struct Block *block) {

  assert(block != NULL);

  printf("\ttimestamp:\t%s", block->timestamp);

  int i = 0;
  int j = 0;

  printf("\tprev_hash:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", block->previous_hash[i]);
  }
  printf("\n");

  printf("\ttransactions:\t%s\n", block->transactions);

  printf("\ttx_hash:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", block->hash[i]);
  }
  printf("\n");

  /*
  printf("\ttx_hash binary:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    for (j = 7; j >= 0; --j) {
      putchar((block->hash[i] & (1 << j)) ? '1' : '0');
    }
  }
  printf("\n");
  */
}

void Block_destroy(struct Block *block) {

  assert(block != NULL);

  free(block->timestamp);
  free(block->transactions);
  free(block->previous_hash);
  free(block->hash);

  free(block);
}
