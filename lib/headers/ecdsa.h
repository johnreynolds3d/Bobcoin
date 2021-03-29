#ifndef ecdsa_h
#define ecdsa_h

// 64-bit integer type
typedef long long int dlong;

// rational ec point
typedef struct {
  dlong x, y;
} epnt;

// elliptic curve parameters
typedef struct {
  long a, b;
  dlong N;
  epnt G;
  dlong r;
} curve;

// signature pair
typedef struct {
  long a, b;
} pair;

// dlong for holding intermediate results,
// long variables in exgcd() for efficiency,
// maximum parameter size 2 * p.y (line 129)
// limits the modulus size to 30 bits.

/*
// maximum modulus
const long mxN = 1073741789;

// max order G = mxN + 65536
const long mxr = 1073807325;

// symbolic infinity
const long inf = -2147483647;

// single global curve
curve e;

// point at infinity zerO
epnt zerO;

// impossible inverse mod N
int inverr;
*/

// return mod(v^-1, u)
long exgcd(long v, long u);

// return mod(a, N)
static inline dlong modn(dlong a);

// return mod(a, r)
dlong modr(dlong a);

// return the discriminant of E
long disc(void);

// return 1 if P = zerO
int isO(epnt p);

// return 1 if P is on curve E
int ison(epnt p);

// full ec point addition
void padd(epnt *r, epnt p, epnt q);

// R:= multiple kP
void pmul(epnt *r, epnt p, long k);

// print point P with prefix f
void pprint(char *f, epnt p);

// initialize elliptic curve
int ellinit(long i[]);

// pseudorandom number [0..1)
double rnd(void);

// signature primitive
pair signature(dlong s, long f);

// verification primitive
int verify(epnt W, long f, pair sg);

// digital signature on message hash f, error bit d
void ec_dsa(long f, long d);

void GetSignature(long f);

#endif
