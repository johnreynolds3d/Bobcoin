#ifndef blockchain_h
#define blockchain_h

struct User {
  unsigned char *user_name;
  unsigned char *user_public_key;
  unsigned char *user_private_key; // randomly generated
  struct Wallet *wallet;
};

struct Wallet {
  unsigned char *wallet_address;     // hash of user's public_key
  unsigned char *wallet_public_key;  // hash of user's private_key
  unsigned char *wallet_private_key; // hash of wallet address
  int balance;
  // struct Transaction *transactions[];
};
/*
struct Transaction {
  unsigned char *payee_public_key;
  unsigned char *hash_prev_trans;
  unsigned char *signature;
};
*/
struct Block {
  unsigned long magic_number;
  unsigned long block_size;
  struct BlockHeader *block_header;
  unsigned int transaction_counter;
  // struct Transaction *transactions[];
};

struct BlockHeader {
  float version;
  unsigned char *hash_prev_block;
  unsigned char *hash_merkle_root;
  unsigned char *time;
  unsigned long bits;
  unsigned long nonce;
};

unsigned char *Hash_create(unsigned char *buffer, unsigned char *text);

struct User *User_create(unsigned char *user_name);

void User_print(struct User *user);

void User_destroy(struct User *user);

struct Wallet *Wallet_create(unsigned char *user_public_key,
                             unsigned char *user_private_key);

void Wallet_print(struct Wallet *wallet);

/*
struct Transaction *Transaction_create(unsigned char *payee_public_key,
                                       unsigned char *hash_prev_trans,
                                       unsigned char *signature);

void Transaction_print(struct Transaction *transaction);
*/

struct BlockHeader *BlockHeader_create(unsigned char *hash_prev_block,
                                       unsigned long bits);

struct Block *Block_create(unsigned char *hash_prev_block, unsigned long bits);
// struct Transaction **transactions[]);

void Block_print(struct Block *block);

void Block_destroy(struct Block *block);

#endif
