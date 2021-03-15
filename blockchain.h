#ifndef blockchain_h__
#define blockchain_h__

extern unsigned long Hash(unsigned char *str);
extern struct Block *Block_create(unsigned long previous_hash,
                                  char *transactions);
extern void Block_destroy(struct Block *block);
extern void Block_print(struct Block *block);

#endif // blockchain_h__
