#ifndef blockchain_h
#define blockchain_h

struct Block {
  unsigned char *previous_hash;
  unsigned char *hash;
  char *transactions;
  unsigned int nonce;
  char *timestamp;
};

struct User {
  char *public_key;
  char *private_key;
  char *name;
};

unsigned char *Hash(unsigned char *buf, char *transactions);

struct Block *Block_create(int num_leading_zeros, unsigned char *previous_hash,
                           char *transactions);

void Block_print(struct Block *block);

void Block_destroy(struct Block *block);

struct User *User_create(char *public_key, char *private_key, char *name);

void User_print(struct User *user);

void User_destroy(struct User *user);

#endif
