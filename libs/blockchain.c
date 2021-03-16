#include "headers/blockchain.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// djb2 hashing algorithm by Dan Bernstein
unsigned long Hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }

  return hash;
}

struct Block *Block_create(unsigned long previous_hash, char *transactions) {
  struct Block *block = malloc(sizeof(struct Block));
  assert(block != NULL);

  block->transactions = malloc(strlen(transactions) + 1);
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  size_t st = sizeof(block->transactions) / sizeof(unsigned char);
  size_t sb = sizeof(unsigned long) + st;

  char buffer[sb];

  snprintf(buffer, sb, "%lu%s\n", previous_hash, block->transactions);

  block->previous_hash = previous_hash;
  block->hash = Hash((unsigned char *)buffer);

  return block;
}

void Block_destroy(struct Block *block) {
  assert(block != NULL);

  free(block->transactions);
  free(block);
}

void Block_print(struct Block *block) {
  assert(block != NULL);

  printf("\tPrevious hash:\t%lu\n\tTransactions:\t%s\n\tHash:\t\t%lu",
         block->previous_hash, block->transactions, block->hash);
}
