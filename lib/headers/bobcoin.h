#ifndef blockchain_h
#define blockchain_h

typedef struct Transaction {
  unsigned char *payee_address;
  unsigned int amount;
  unsigned char *payer_public_key;
  unsigned char *payer_signature;
} Transaction;

typedef struct Wallet {
  unsigned char *address;
  unsigned char *public_key;
  unsigned char *private_key;
  unsigned int balance;
  Transaction **transactions;
} Wallet;

typedef struct BlockHeader {
  unsigned char *version;
  unsigned char *hash_prev_block;
  unsigned char *hash_merkle_root;
  unsigned long time;
  unsigned long bits;
  unsigned long nonce;
} BlockHeader;

typedef struct Block {
  const unsigned long magic_number;
  unsigned int block_size;
  unsigned int transaction_counter;
  BlockHeader *block_header;
  Transaction **transactions;
} Block;

typedef struct User {
  char *name;
  unsigned char *public_key;
  unsigned char *private_key;
  Wallet *wallet;
} User;

void GetSignature(long f, unsigned long *signature_buffer);

unsigned char *GetHash(unsigned char *buffer, unsigned char *text);

User *User_create(char *name);

Wallet *Wallet_create(User *user);

Transaction *Transaction_create(User *payer, User *payee, unsigned int amount);

BlockHeader *BlockHeader_create(unsigned char *hash_prev_block,
                                unsigned long bits);

Block *Block_create(Transaction **transactions, int transaction_counter);

void User_print(User *user);

void Wallet_print(User *user);

void Transaction_print(Transaction *transaction);

void Block_print(Block *block);

void User_destroy(User *user);

void Block_destroy(Block *block);

#endif
