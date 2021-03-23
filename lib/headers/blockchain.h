#ifndef blockchain_h
#define blockchain_h

struct Block {
  struct Header *header;
  int *trans_count;
  struct Transaction *transactions[];
};

struct Header {
  char *timestamp;
  unsigned char *prev_hash;
  unsigned char *root_hash;
  unsigned int nonce;
  int target;
};

struct User {
  char *name;
  char *public_key;
  unsigned char *private_key; // randomly generated
  struct Wallet *wallet;
};

struct Wallet {
  unsigned char *address;     // hash of User->public_key;
  unsigned char *public_key;  // hash of User->private_key
  unsigned char *private_key; // hash of Wallet->address;
  int balance;
  struct Transaction *transactions[];
};

struct Transaction {
  char *public_key_owner;
  unsigned char *hash_prev_trans;
  char *signature_prev_owner;
};

unsigned char *Hash_create(unsigned char *buf, char *text);

struct Block *Block_create(int target, unsigned char *prev_hash,
                           struct Transaction **transactions[]);

void Block_print(struct Block *block);

void Block_destroy(struct Block *block);

struct Header *Header_create(int target, unsigned char *prev_hash,
                             struct Transaction **transactions[]);

struct User *User_create(char *name);

void User_print(struct User *user);

void User_destroy(struct User *user);

struct Wallet *Wallet_create(char *public_key, unsigned char *private_key);

void Wallet_print(struct Wallet *wallet);

struct Transaction *Transaction_create(char *public_key_owner,
                                       unsigned char *hash_prev_trans,
                                       char *signature_prev_owner);

void Transaction_print(struct Transaction *transaction);

#endif
