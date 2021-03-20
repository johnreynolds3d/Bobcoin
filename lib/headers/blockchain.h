#ifndef blockchain_h
#define blockchain_h

struct Block {
  unsigned char *previous_hash;
  unsigned char *hash;
  char *transactions;
  unsigned long nonce;
  char *timestamp;
};

struct Block *Block_create(unsigned char *previous_hash, char *transactions);

void Block_print(struct Block *block);

void Block_destroy(struct Block *block);

#endif
