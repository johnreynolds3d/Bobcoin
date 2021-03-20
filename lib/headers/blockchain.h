#ifndef blockchain_h
#define blockchain_h

struct Block {
  unsigned char *previous_hash;
  unsigned char *hash;
  char *transactions;
};

extern struct Block *Block_create(unsigned char *previous_hash,
                                  char *transactions);

extern void Block_destroy(struct Block *block);

extern void Block_print(struct Block *block);

#endif
