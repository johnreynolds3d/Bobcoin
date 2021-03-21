#include "headers/blockchain.h"
#include "headers/sha256.h"
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct User *User_create(unsigned char *public_key, unsigned char *private_key,
                         unsigned char *name) {

  assert(public_key != NULL && private_key != NULL && name != NULL);

  struct User *user = calloc((size_t)1, sizeof(struct User));
  assert(user != NULL);

  user->public_key = calloc((size_t)(strlen(public_key) + 1), sizeof(char));
  assert(user->public_key != NULL);
  strcpy(user->public_key, public_key);

  user->private_key = calloc((size_t)(strlen(private_key) + 1), sizeof(char));
  assert(user->private_key != NULL);
  strcpy(user->private_key, private_key);

  user->public_key = calloc((size_t)(strlen(name) + 1), sizeof(char));
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

unsigned char *Hash(unsigned char *buf, unsigned char *transactions) {

  assert(buf != NULL && transactions != NULL);

  BYTE text[strlen(transactions) + 1];
  strcpy(text, transactions);

  BYTE hash[SHA256_BLOCK_SIZE] = {
      0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 0x41, 0x41, 0x40,
      0xde, 0x5d, 0xae, 0x22, 0x23, 0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17,
      0x7a, 0x9c, 0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};

  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, text, strlen(text));
  sha256_final(&ctx, buf);

  if (!memcmp(hash, buf, SHA256_BLOCK_SIZE + 1)) {
    printf("Hashing of '%s' failed\n", transactions);
    exit(1);
  }

  return buf;
}

struct Block *Block_create(int num_leading_zeros, unsigned char *previous_hash,
                           unsigned char *transactions) {

  assert(previous_hash != NULL && transactions != NULL);

  struct Block *block = calloc((size_t)1, sizeof(struct Block));
  assert(block != NULL);

  time_t current_time = time(NULL);

  struct tm *time_info = gmtime(&current_time);

  unsigned char *gmt = asctime(time_info);

  block->timestamp = calloc((size_t)(strlen(gmt) + 1), sizeof(char));
  assert(block->timestamp != NULL);
  strcpy(block->timestamp, gmt);

  block->transactions =
      calloc((size_t)(strlen(transactions) + 1), sizeof(char));
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  block->previous_hash = calloc((size_t)(SHA256_BLOCK_SIZE + 1), sizeof(char));
  assert(block->previous_hash != NULL);
  strcpy(block->previous_hash, previous_hash);

  block->hash = calloc((size_t)(SHA256_BLOCK_SIZE + 1), sizeof(char));
  assert(block->hash != NULL);

  BYTE buf[SHA256_BLOCK_SIZE + 1] = {'a'};

  Hash(buf, transactions);

  /*
  int i = 0;
  int j = 0;

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    for (j = 7; j >= 0; --j) {
      putchar((buf[i] & (1 << j)) ? '1' : '0');
    }
  }
  printf("\n\n");
  */

  strcpy(block->hash, buf);

  return block;
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
