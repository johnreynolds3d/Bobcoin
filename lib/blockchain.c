#include "headers/blockchain.h"
#include "headers/ecdsa.h"
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

struct User *User_create(unsigned char *name) {

  assert(name != NULL);

  struct User *user = calloc(1, sizeof(struct User));
  assert(user != NULL);

  user->name = calloc(strlen((const char *)(name)) + 1, sizeof(char));
  assert(user->name != NULL);

  user->public_key = calloc((SHA256_BLOCK_SIZE * 2) + 1, sizeof(char));
  assert(user->public_key != NULL);

  user->private_key = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(user->private_key != NULL);

  memcpy(user->name, name, strlen((const char *)(name)) + 1);

  unsigned int i = 0;

  const char alphanum[] = "0123456789abcdefghijklmnopqrstuvwxyz";

  user->public_key[0] = 'b';
  user->public_key[1] = 'c';
  user->public_key[2] = '1';

  for (i = 3; i < SHA256_BLOCK_SIZE * 2; i++) {
    user->public_key[i] =
        alphanum[rand() % ((strlen((const char *)alphanum) - 1) - 0 + 1) + 0];
  }
  user->public_key[SHA256_BLOCK_SIZE * 2] = '\0';

  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    user->private_key[i] = rand() % (255 - 0 + 1) + 0;
  }
  user->private_key[SHA256_BLOCK_SIZE] = '\0';

  user->wallet = Wallet_create(user);

  return user;
}

struct Wallet *Wallet_create(struct User *user) {

  assert(user != NULL);

  struct Wallet *wallet = calloc(1, sizeof(struct Wallet));
  assert(wallet != NULL);

  wallet->address = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(wallet->address != NULL);

  wallet->public_key = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(wallet->public_key != NULL);

  wallet->private_key = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(wallet->private_key != NULL);

  wallet->transactions = calloc(1, sizeof(struct Transaction));
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

struct Transaction *Transaction_create(struct User *payer, struct User *payee,
                                       unsigned long amount) {

  assert(payer != NULL && payee != NULL);

  struct Transaction *transaction = calloc(1, sizeof(struct Transaction));
  assert(transaction != NULL);

  transaction->payee_address = calloc(SHA256_BLOCK_SIZE + 1, sizeof(char));
  assert(transaction->payee_address != NULL);

  transaction->payer_public_key =
      calloc((SHA256_BLOCK_SIZE * 2) + 1, sizeof(char));
  assert(transaction->payer_public_key != NULL);

  transaction->payer_signature = calloc(65, sizeof(char));
  assert(transaction->payer_signature != NULL);

  memcpy(transaction->payee_address, payee->wallet->address, SHA256_BLOCK_SIZE);
  memcpy(transaction->payer_public_key, payer->public_key,
         SHA256_BLOCK_SIZE * 2);

  printf("\nTransaction pending:\n\n");

  // ------------------------------ HASHING ------------------------------------

  // concatenate address, amount, and time into a string for hashing
  unsigned int size_amount = snprintf(NULL, 0, "%lu", amount);
  assert(size_amount > 0);

  unsigned char amount_buffer[size_amount + 1];
  snprintf((char *)amount_buffer, size_amount + 1, "%lu", amount);
  printf("\ttransaction amount:\t%s\n", amount_buffer);

  unsigned int size_time = snprintf(NULL, 0, "%lu", (unsigned long)time(NULL));
  assert(size_time > 0);

  unsigned char time_buffer[size_time];
  snprintf((char *)time_buffer, size_time, "%lu", (unsigned long)time(NULL));
  printf("\ttransaction time:\t%s (seconds since 1970-01-01T00:00:00Z)\n",
         time_buffer);

  unsigned char *text_buffer =
      calloc(SHA256_BLOCK_SIZE + size_time + size_amount, sizeof(char));
  assert(text_buffer != NULL);

  memcpy(text_buffer, transaction->payee_address, SHA256_BLOCK_SIZE);

  strncat((char *)text_buffer, time_buffer,
          sizeof(text_buffer) - strlen((const char *)text_buffer) - 1);

  strncat((char *)text_buffer, amount_buffer,
          sizeof(text_buffer) - strlen((const char *)text_buffer) - 1);

  unsigned int i = 0;

  /*
  printf("\ttransaction text:\t");
  for (i = 0; i < strlen((const char *)(text_buffer)); i++) {
    printf("%.2x", text_buffer[i]);
  }
  printf("\n");
  */

  unsigned char hash_buffer[SHA256_BLOCK_SIZE] = {'0'};

  GetHash(hash_buffer, text_buffer);

  printf("\ttransaction hash:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", hash_buffer[i]);
  }
  printf("\n");

  // ------------------------------ SIGNING ------------------------------------

  // printf("\trunning ECDSA on hash:\t%ld\n", (long)hash_buffer);

  unsigned long *signature_buffer = calloc(2, sizeof(long));
  assert(signature_buffer != 0);

  GetSignature((long)hash_buffer, signature_buffer);

  /*
  printf("\n\tsignature (c, d):\t(%ld, %ld)\n", signature_buffer[0],
         signature_buffer[1]);
         */

  transaction->amount = amount;

  payee->wallet->balance += amount;
  payer->wallet->balance -= amount;

  if (payee->wallet->transactions == NULL) {
    payee->wallet->transactions[0] = transaction;
  } else {
    payee->wallet->transactions[1] = transaction;
  }

  for (i = 0; i < 2 && payee->wallet->transactions[i] != NULL; i++) {
    printf("\nsizeof(payee->wallet->transactions[%d]): %ld\n", i,
           sizeof(payee->wallet->transactions[i]));
    Transaction_print(payee->wallet->transactions[i]);
  }

  free(text_buffer);
  free(signature_buffer);

  return transaction;
}

/*
struct BlockHeader *BlockHeader_create(unsigned char *hash_prev_block,
                                       unsigned long bits) {


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

  block_header->time = calloc(strlen(const char *)(gmt) + 1, sizeof(char));
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

  block->transactions = calloc(strlen(const char *)(transactions) + 1,
sizeof(char)); assert(block->transactions != NULL); strcpy(block->transactions,
transactions);

  block->hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block->hash != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'a'};

  unsigned char *text =
      calloc(strlen(const char *)(transactions) + 1 + strlen(const char
*)(nonce) + 1, sizeof(char)); assert(text != NULL);

  memcpy(text, transactions, strlen(const char *)(transactions) + 1);
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
*/

struct Block *Block_create(struct Transaction **transactions,
                           unsigned long transaction_counter) {

  assert(transactions != NULL);

  struct Block *block = calloc(1, sizeof(struct Block));
  assert(block != NULL);

  *(unsigned long *)&block->magic_number = 0xD9B4BEF9UL;

  block->transaction_counter = transaction_counter;

  block->transactions = calloc(1, sizeof(struct Transaction));
  assert(block->transactions != NULL);

  unsigned int i = 0;

  for (i = 0; i < transaction_counter; i++) {
    block->transactions[i] = transactions[i];
  }

  // unsigned long bits = rand() % (((int)pow(2, 32) - 1) - 0 + 1) + 0;

  /*
  block->block_header = BlockHeader_create(hash_prev_block, bits);
  assert(block->block_header != NULL);


  block->hash = calloc(SHA256_BLOCK_SIZE, sizeof(char));
  assert(block->hash != NULL);

  BYTE buffer[SHA256_BLOCK_SIZE] = {'a'};

  char *text =
      calloc(strlen(const char *)(transactions) + 1 + strlen(const char
*)(nonce) + 1, sizeof(char)); assert(text != NULL);

  memcpy(text, transactions, strlen(const char *)(transactions) + 1);
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
*/

  return block;
}

void User_print(struct User *user) {

  assert(user != NULL);

  printf("\n\tuser name:\t\t%s\n", user->name);

  unsigned int i = 0;

  printf("\tuser public key:\t%s\n", user->public_key);

  printf("\tuser private key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", user->private_key[i]);
  }
  printf("\n");

  Wallet_print(user);
}

void Wallet_print(struct User *user) {

  assert(user != NULL);

  unsigned int i = 0;

  printf("\twallet address:\t\t");
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

  printf("\twallet balance:\t\t%lu\n", user->wallet->balance);
}

void User_destroy(struct User *user) {

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

void Transaction_print(struct Transaction *transaction) {

  assert(transaction != NULL);

  unsigned int i = 0;

  printf("\nTransaction verified:\n");

  printf("\tpayee wallet address:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", transaction->payee_address[i]);
  }
  printf("\n");

  printf("\ttransaction amount:\t%lu\n", transaction->amount);

  printf("\tpayer public key:\t%s\n", transaction->payer_public_key);

  /*
  printf("\tpayer public key:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", transaction->payer_public_key[i]);
  }
  printf("\n");

  printf("\tpayer signature:\t");
  for (i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", transaction->payer_signature[i]);
  }
  printf("\n");
  */
}

void Block_print(struct Block *block) {

  assert(block != NULL);

  printf("\nBlock:\n");
  printf("\ttransaction counter:\t%ld\n", block->transaction_counter);

  unsigned int i = 0;

  for (i = 0; i < block->transaction_counter; i++) {
    Transaction_print(block->transactions[i]);
  }

  /*
  printf("\ttime:\t%s", block->block_header->time);

  unsigned int i = 0;
  unsigned int j = 0;

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
*/
}

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
