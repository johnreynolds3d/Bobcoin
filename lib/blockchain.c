#include "headers/blockchain.h"
#include "headers/sha256.h"
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Block *Block_create(unsigned char *previous_hash, char *transactions) {

  time_t rawtime;
  struct tm *time_info;

  time(&rawtime);
  time_info = localtime(&rawtime);

  struct Block *block = malloc(sizeof(struct Block));
  assert(block != NULL);

  block->timestamp = malloc(32 * sizeof(char));
  assert(block->timestamp != NULL);
  strcpy(block->timestamp, asctime(time_info));

  block->transactions = malloc(strlen(transactions) + 1);
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  BYTE text[strlen(transactions) + 1];
  strcpy(text, transactions);

  BYTE hash[SHA256_BLOCK_SIZE] = {
      0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 0x41, 0x41, 0x40,
      0xde, 0x5d, 0xae, 0x22, 0x23, 0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17,
      0x7a, 0x9c, 0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};

  BYTE buf[SHA256_BLOCK_SIZE];

  SHA256_CTX ctx;

  sha256_init(&ctx);

  for (int idx = 0; idx < 100000; ++idx) {
    sha256_update(&ctx, text, strlen(text));
  }

  sha256_final(&ctx, buf);

  // printf("Hashing of transactions %s\n",
  //       memcmp(hash, buf, SHA256_BLOCK_SIZE) ? "succeeded" : "failed");

  block->previous_hash = malloc(SHA256_BLOCK_SIZE);
  assert(block->previous_hash != NULL);
  strcpy(block->previous_hash, previous_hash);

  block->hash = malloc(SHA256_BLOCK_SIZE);
  assert(block->hash != NULL);
  strcpy(block->hash, buf);

  return block;
}

void Block_print(struct Block *block) {
  assert(block != NULL);
  printf("\tTimestamp:\t%s\tPrevious "
         "hash:\t%s\n\tTransactions:\t%s\n\tTX_hash:\t%s\n",
         block->timestamp, block->previous_hash, block->transactions,
         block->hash);

  printf("\tTX_H binary:\t");
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%d", !!((block->hash[0] << j) & 0x80));
    }
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
