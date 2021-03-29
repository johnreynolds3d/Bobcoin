#ifndef blockchain_h
#define blockchain_h

struct User {
  unsigned char *name;
  unsigned char *public_key;
  unsigned char *private_key;
  struct Wallet *wallet;
};

struct Wallet {
  unsigned char *address;
  unsigned char *public_key;
  unsigned char *private_key;
  struct Transaction *transactions;
  unsigned long balance;
};

struct Transaction {
  unsigned char *payee_address;
  unsigned long amount;
  unsigned char *payer_public_key;
  unsigned char *payer_signature;
};

struct BlockHeader {
  unsigned long version;
  unsigned char *hash_prev_block;
  unsigned char *hash_merkle_root;
  unsigned char *time;
  unsigned long bits;
  unsigned long nonce;
};

struct Block {
  struct BlockHeader *blockheader;
  unsigned long transaction_counter;
  struct Transaction *transactions;
};

void GetSignature(long f);

unsigned char *GetHash(unsigned char *buffer, unsigned char *text);

struct User *User_create(unsigned char *name);

struct Wallet *Wallet_create(struct User *user);

struct Transaction *Transaction_create(struct User *payer, struct User *payee,
                                       unsigned long amount);

struct BlockHeader *BlockHeader_create(unsigned char *hash_prev_block,
                                       unsigned long bits);

struct Block *Block_create(unsigned char *hash_prev_block, unsigned long bits,
                           struct Transaction **transactions);

void User_print(struct User *user);

void Wallet_print(struct User *user);

void Transaction_print(struct Transaction *transaction);

void Block_print(struct Block *block);

void User_destroy(struct User *user);

void Block_destroy(struct Block *block);

#endif
