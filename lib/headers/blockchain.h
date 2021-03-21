#ifndef blockchain_h
#define blockchain_h

struct Block {
  unsigned char *previous_hash;
  unsigned char *hash;
  unsigned char *transactions;
  unsigned int nonce;
  unsigned char *timestamp;
};

struct User {
  unsigned char *public_key;
  unsigned char *private_key;
  unsigned char *name;
};

unsigned char *Hash(unsigned char *buf, unsigned char *transactions);

struct Block *Block_create(int num_leading_zeros, unsigned char *previous_hash,
                           unsigned char *transactions);

void Block_print(struct Block *block);

void Block_destroy(struct Block *block);

struct User *User_create(unsigned char *public_key, unsigned char *private_key,
                         unsigned char *name);

void User_print(struct User *user);

void User_destroy(struct User *user);

#endif
