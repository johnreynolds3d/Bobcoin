#ifndef blockchain_h
#define blockchain_h

struct Block {
  unsigned long previous_hash;
  unsigned long hash;
  char *transactions;
};

extern unsigned long Hash(unsigned char *str);

extern struct Block *Block_create(unsigned long previous_hash,
                                  char *transactions);

extern void Block_destroy(struct Block *block);

extern void Block_print(struct Block *block);

#endif
