#ifndef ecdsa_h
#define ecdsa_h

typedef long long int dlong;

typedef struct {
  dlong x;
  dlong y;
} epnt;

typedef struct {
  long a;
  long b;
  dlong N;
  epnt G;
  dlong r;
} curve;

typedef struct {
  long a;
  long b;
} pair;

long exgcd(long v, long u);

static inline dlong modn(dlong a);

dlong modr(dlong a);

long disc(void);

int isO(epnt p);

int ison(epnt p);

void padd(epnt *r, epnt p, epnt q);

void pmul(epnt *r, epnt p, long k);

void pprint(char *f, epnt p);

int ellinit(long i[]);

double rnd(void);

pair signature(dlong s, long f);

int verify(epnt W, long f, pair sg);

void ec_dsa(long f, long d, unsigned long *signature_buffer);

void GetSignature(long f, unsigned long *signature_buffer);

#endif
