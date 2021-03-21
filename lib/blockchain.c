#include "headers/blockchain.h"
#include "headers/sha256.h"
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char *Hash(unsigned char *buf, char *transactions) {

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

  if (!memcmp(hash, buf, SHA256_BLOCK_SIZE)) {
    printf("Hashing of '%s' failed\n", transactions);
    exit(1);
  }

  return buf;
}

struct Block *Block_create(int num_leading_zeros, unsigned char *previous_hash,
                           char *transactions) {

  assert(previous_hash != NULL && transactions != NULL);

  struct Block *block = calloc((size_t)1, sizeof(struct Block));
  assert(block != NULL);

  time_t current_time = time(NULL);

  struct tm *time_info = gmtime(&current_time);

  char *gmt = asctime(time_info);

  block->timestamp = calloc((size_t)(strlen(gmt) + 1), sizeof(char));
  assert(block->timestamp != NULL);
  strcpy(block->timestamp, gmt);

  block->transactions =
      calloc((size_t)(strlen(transactions) + 1), sizeof(char));
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  block->previous_hash =
      calloc((size_t)(SHA256_BLOCK_SIZE + 1), sizeof(unsigned char));
  assert(block->previous_hash != NULL);
  strcpy(block->previous_hash, previous_hash);

  block->hash = calloc((size_t)(SHA256_BLOCK_SIZE + 1), sizeof(unsigned char));
  assert(block->hash != NULL);

  BYTE buf[SHA256_BLOCK_SIZE + 1] = {'a'};
  strcpy(block->hash, Hash(buf, transactions));

  return block;
}

void Block_print(struct Block *block) {

  assert(block != NULL);

  printf("\ttimestamp:\t%s", block->timestamp);

  int i = 0;
  int j = 0;

  /*
    printf("\tprev_hash bin:\t");
    for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
      for (j = 0; j < 8; j++) {
        printf("%d", !!((block->previous_hash[i] << j) & 0x80));
      }
    }
    printf("\n");
  */

  printf("\tprev_hash:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", block->previous_hash[i]);
  }
  printf("\n");

  printf("\ttransactions:\t%s\n", block->transactions);

  /*
    printf("\ttx_hash bin:\t");
    for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
      for (j = 0; j < 8; j++) {
        printf("%d", !!((block->hash[i] << j) & 0x80));
      }
    }
    printf("\n");
  */

  printf("\ttx_hash:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", block->hash[i]);
  }
  printf("\n");
}

void Block_destroy(struct Block *block) {

  assert(block != NULL);

  free(block->timestamp);
  free(block->transactions);
  free(block->previous_hash);
  free(block->hash);

  free(block);
}
