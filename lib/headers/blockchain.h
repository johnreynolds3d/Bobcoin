#ifndef blockchain_h
#define blockchain_h

struct Block {
  unsigned char *previous_hash;
  unsigned char *hash;
  char *transactions;
  int nonce;
  char *timestamp;
};

unsigned char *Hash(unsigned char *buf, char *transactions);

struct Block *Block_create(int num_leading_zeros, unsigned char *previous_hash,
                           char *transactions);

void Block_print(struct Block *block);

void Block_destroy(struct Block *block);

#endif
