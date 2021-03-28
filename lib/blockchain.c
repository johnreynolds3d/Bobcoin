#include "headers/blockchain.h"
#include "headers/sha256.h"
#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char *GetHash(unsigned char *buffer, unsigned char *text) {

  assert(buffer != NULL && text != NULL);

  BYTE hash[SHA256_BLOCK_SIZE] = {
      0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 0x41, 0x41, 0x40,
      0xde, 0x5d, 0xae, 0x22, 0x23, 0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17,
      0x7a, 0x9c, 0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};

  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, text, strlen(text));
  sha256_final(&ctx, buffer);

  if (!memcmp(hash, buffer, SHA256_BLOCK_SIZE)) {
    printf("Hashing of '%s' failed\n", text);
    exit(1);
  }

  return buffer;
}

struct User *User_create(unsigned char *user_name) {

  assert(user_name != NULL);

  struct User *user = calloc(1, sizeof(struct User));
  assert(user != NULL);

  user->user_name = calloc(strlen(user_name) + 1, sizeof(char));
  assert(user->user_name != NULL);

  user->user_public_key = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(user->user_public_key != NULL);

  user->user_private_key = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(user->user_private_key != NULL);

  strcpy(user->user_name, user_name);

  user->user_public_key[0] = 'b';
  user->user_public_key[1] = 'c';
  user->user_public_key[2] = '1';

  unsigned char alphanum[] = "0123456789abcdefghijklmnopqrstuvwxyz";

  unsigned int i = 0;

  for (i = 3; i < SHA256_BLOCK_SIZE; i++) {
    user->user_public_key[i] =
        alphanum[rand() % ((strlen(alphanum) - 1) - 0 + 1) + 0];
  }
  user->user_public_key[SHA256_BLOCK_SIZE] = '\0';

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    user->user_private_key[i] =
        alphanum[rand() % ((strlen(alphanum) - 1) - 0 + 1) + 0];
  }
  user->user_private_key[SHA256_BLOCK_SIZE] = '\0';

  user->user_wallet = Wallet_create(user);

  return user;
}

struct Wallet *Wallet_create(struct User *user) {

  assert(user != NULL);

  struct Wallet *wallet = calloc(1, sizeof(struct Wallet));
  assert(wallet != NULL);

  wallet->wallet_address = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(wallet->wallet_address != NULL);

  wallet->wallet_public_key = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(wallet->wallet_public_key != NULL);

  wallet->wallet_private_key = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(wallet->wallet_private_key != NULL);

  wallet->wallet_transactions = calloc(1, sizeof(struct Transaction));
  assert(wallet->wallet_transactions != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'0'};

  GetHash(buffer, user->user_public_key);
  memcpy(wallet->wallet_address, buffer, SHA256_BLOCK_SIZE);

  GetHash(buffer, user->user_private_key);
  memcpy(wallet->wallet_public_key, buffer, SHA256_BLOCK_SIZE);

  GetHash(buffer, wallet->wallet_address);
  memcpy(wallet->wallet_private_key, buffer, SHA256_BLOCK_SIZE);

  wallet->wallet_balance = 0;

  return wallet;
}

struct Transaction *Transaction_create(unsigned char *payee_public_key,
                                       unsigned char *hash_prev_trans,
                                       unsigned char *signature) {

  assert(payee_public_key != NULL && hash_prev_trans != NULL &&
         signature != NULL);

  struct Transaction *transaction = calloc(1, sizeof(struct Transaction));
  assert(transaction != NULL);

  transaction->payee_public_key = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(transaction->payee_public_key != NULL);

  transaction->hash_prev_trans = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(transaction->hash_prev_trans != NULL);

  transaction->signature = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(transaction->signature != NULL);

  strcpy(transaction->payee_public_key, payee_public_key);
  strcpy(transaction->hash_prev_trans, hash_prev_trans);
  strcpy(transaction->signature, signature);

  return transaction;
}

/*
struct BlockHeader *BlockHeader_create(unsigned char *hash_prev_block,
                                       unsigned long bits) {

  assert(hash_prev_block != NULL);

  struct BlockHeader *block_header = calloc(1, sizeof(struct BlockHeader));
  assert(block_header != NULL);

  block_header->hash_prev_block = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block_header->hash_prev_block != NULL);

  block_header->hash_merkle_root = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block_header->hash_merkle_root != NULL);

  block_header->time = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block_header->time != NULL);

  block_header->version = 1.0f;

  time_t current_time = time(NULL);

  struct tm *time_info = gmtime(&current_time);

  unsigned char *gmt = asctime(time_info);

  block_header->time = calloc(strlen(gmt) + 1, sizeof(char));
  assert(block_header->time != NULL);

  strcpy(block_header->time, gmt);

  block_header->bits = bits;
  printf("\tbits:\t\t%lu\n", block_header->bits);

  block_header->nonce = 0;
  printf("\tnonce:\t\t%lu\n", block_header->nonce);

  block_header->hash_prev_block = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block_header->hash_prev_block != NULL);
  memcpy(block_header->hash_prev_block, hash_prev_block, SHA256_BLOCK_SIZE);

  // ---------------------------- HASH_MERKLE_ROOT -----------------------------

  block->transactions = calloc(strlen(transactions) + 1, sizeof(char));
  assert(block->transactions != NULL);
  strcpy(block->transactions, transactions);

  block->hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block->hash != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'a'};

  unsigned char *text =
      calloc(strlen(transactions) + 1 + strlen(nonce) + 1, sizeof(char));
  assert(text != NULL);

  memcpy(text, transactions, strlen(transactions) + 1);
  strcat(text, nonce);

  printf("\ttext:\t\t%s", text);

  Hash(buffer, transactions);

  memcpy(block_header->hash_prev_block, buffer, SHA256_BLOCK_SIZE);

  free(text);
  free(nonce);

  return block_header;
}
*/

/*
struct Block *Block_create(unsigned char *hash_prev_block, unsigned long bits,
                           struct Transaction **transactions) {

  assert(hash_prev_block != NULL && transactions != NULL);

  struct Block *block = calloc(1, sizeof(struct Block));
  assert(block != NULL);

  block->block_header = BlockHeader_create(hash_prev_block, bits);
  assert(block->block_header != NULL);

  block->transactions = calloc(1, sizeof(struct Transaction));
  assert(block->transactions != NULL);
  memcpy(block->transactions, transactions, sizeof(char));

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

  // --------------------------- PROOF OF WORK ---------------------------------

  printf("\nLooking for exactly %lu leading zeros...\n\n", bits);

  int i = 0;
  int j = 0;
  int k = 0;

  unsigned int buffer[256] = {0};

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    for (j = 7; j >= 0; --j) {
      buffer[k] =
          ((block->block_header->hash_prev_block[i] & (1 << j)) ? 1 : 0);
      k++;
    }
  }
  printf("\n");

  printf("\tbuffer:\t");

  if (bits > 0) {
    for (i = 0; i < bits; i++) {
      printf("%d", buffer[i]);
    }
  }

  printf("\n\n");

  if (bits == 0 && buffer[0] == 1) {
    printf(
        "\t\t************ Found exactly %lu leading zeros!!! ************\n\n",
        bits);
    Block_print(block);
    return block;
  }

  for (i = 0; i < bits; i++) {

    if (buffer[i] != 0) {
      printf("Found fewer than %lu leading zeros; try again!\n\n", bits);
      break;
    }

    if (i == bits - 1) {
      if (buffer[bits] != 1) {
        printf("Found more than %lu leading zeros; try again!\n\n", bits);
        break;
      } else {
        printf("\t\t************ Found exactly %lu leading zeros!!! "
               "************\n\n",
               bits);
        Block_print(block);
        return block;
      }
    }
  }
}
*/

void User_print(struct User *user) {

  assert(user != NULL);

  printf("\n\tuser name:\t\t%s\n", user->user_name);

  unsigned int i = 0;

  printf("\tuser public key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->user_public_key[i]);
  }
  printf("\n");

  printf("\tuser private key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->user_private_key[i]);
  }
  printf("\n");
}

void Wallet_print(struct Wallet *wallet) {

  assert(wallet != NULL);

  unsigned int i = 0;

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

  printf("\twallet balance:\t\t%d\n", wallet->wallet_balance);
}

void User_destroy(struct User *user) {

  assert(user != NULL);

  free(user->user_wallet->wallet_transactions);
  free(user->user_wallet->wallet_private_key);
  free(user->user_wallet->wallet_public_key);
  free(user->user_wallet->wallet_address);
  free(user->user_wallet);

  free(user->user_private_key);
  free(user->user_public_key);
  free(user->user_name);
  free(user);
}

void Transaction_print(struct Transaction *transaction) {

  assert(transaction != NULL);

  unsigned int i = 0;

  printf("Transaction:\n");

  printf("\tpayee public key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", transaction->payee_public_key[i]);
  }
  printf("\n");

  printf("\thash prev trans:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", transaction->hash_prev_trans[i]);
  }
  printf("\n");

  printf("\tsignature:\t\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", transaction->signature[i]);
  }
  printf("\n");
}

/*
void Block_print(struct Block *block) {

  assert(block != NULL);

  printf("\ttime:\t%s", block->block_header->time);

  int i = 0;
  int j = 0;

  printf("\thash prev block:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", block->block_header->hash_prev_block[i]);
  }
  printf("\n");

  printf("\thash merkle root:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", block->block_header->hash_merkle_root[i]);
  }
  printf("\n");

  Transaction_print(block->transactions);

  printf("\thmr binary:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    for (j = 7; j >= 0; --j) {
      putchar((block->block_header->hash_merkle_root[i] & (1 << j)) ? '1'
                                                                    : '0');
    }
  }
  printf("\n");
}
*/

/*
void Block_destroy(struct Block *block) {

  assert(block != NULL && block->block_header != NULL &&
         block->transactions != NULL);

  free(block->block_header->time);
  free(block->block_header->hash_merkle_root);
  free(block->block_header->hash_prev_block);
  free(block->block_header);

  free(block->transactions);

  free(block);
}
*/
