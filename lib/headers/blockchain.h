#ifndef blockchain_h
#define blockchain_h

struct User {
  char *user_name;
  char *user_public_key;
  unsigned char *user_private_key; // randomly generated
  struct Wallet *wallet;
};

struct Wallet {
  unsigned char *wallet_address;     // hash of user's public_key
  unsigned char *wallet_public_key;  // hash of user's private_key
  unsigned char *wallet_private_key; // hash of wallet address
  int balance;
  struct Transaction *transactions[];
};

struct Transaction {
  char *public_key_owner;
  unsigned char *hash_prev_trans;
  char *signature_prev_owner;
};

struct Block {
  int *block_size;
  struct BlockHeader *block_header;
  int *transaction_counter;
  struct Transaction *transactions[];
};

struct BlockHeader {
  double *version;
  unsigned char *previous_block_hash;
  unsigned char *merkle_root;
  char *timestamp;
  int *difficulty_target;
  unsigned int *nonce;
};

unsigned char *Hash_create(unsigned char *buffer, char *text);

struct User *User_create(char *user_name);

struct Wallet *Wallet_create(char *user_public_key,
                             unsigned char *user_private_key);

struct Transaction *Transaction_create(char *owner_public_key,
                                       unsigned char *previous_transaction_hash,
                                       char *previous_owner_signature);

struct Block *Block_create(int difficulty_target,
                           unsigned char *previous_block_hash,
                           struct Transaction **transactions[]);

struct BlockHeader *BlockHeader_create(int difficulty_target,
                                       unsigned char *previous_block_hash,
                                       struct Transaction **transactions[]);

void User_print(struct User *user);

void Wallet_print(struct Wallet *wallet);

void Transaction_print(struct Transaction *transaction);

void Block_print(struct Block *block);

void User_destroy(struct User *user);

void Block_destroy(struct Block *block);

#endif
