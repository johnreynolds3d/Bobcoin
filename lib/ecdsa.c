#include "headers/ecdsa.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// return mod(v^-1, u)
long exgcd(long v, long u) {

  register long q, t;

  long r = 0;
  long s = 1;

  if (v < 0) {
    v += u;
  }

  while (v) {
    q = u / v;
    t = u - q * v;
    u = v;
    v = t;
    t = r - q * s;
    r = s;
    s = t;
  }

  if (u != 1) {
    printf("\timpossible inverse mod N, gcd = %ld\n", u);
    inverr = 1;
  }

  return r;
}

// return mod(a, N)
static inline dlong modn(dlong a) {
  a %= e.N;
  if (a < 0) {
    a += e.N;
  }
  return a;
}

// return mod(a, r)
dlong modr(dlong a) {
  a %= e.r;
  if (a < 0) {
    a += e.r;
  }
  return a;
}

// return the discriminant of E
long disc(void) {

  dlong c;
  dlong a = e.a;
  dlong b = e.b;

  c = 4 * modn(a * modn(a * a));

  return modn(-16 * (c + 27 * modn(b * b)));
}

// return 1 if P = zerO
int isO(epnt p) { return (p.x == inf) && (p.y == 0); }

// return 1 if P is on curve E
int ison(epnt p) {

  long r;
  long s;

  if (!isO(p)) {
    r = modn(e.b + p.x * modn(e.a + p.x * p.x));
    s = modn(p.y * p.y);
  }

  return (r == s);
}

// full ec point addition
void padd(epnt *r, epnt p, epnt q) {

  dlong la;
  dlong t;

  if (isO(p)) {
    *r = q;
    return;
  }

  if (isO(q)) {
    *r = p;
    return;
  }

  if (p.x != q.x) { // R:= P + Q
    t = p.y - q.y;
    la = modn(t * exgcd(p.x - q.x, e.N));
  } else // P = Q, R := 2P
      if (p.y == q.y && p.y != 0) {
    t = modn(3 * modn(p.x * p.x) + e.a);
    la = modn(t * exgcd(2 * p.y, e.N));
  } else {
    *r = zerO;
    return;
  } // P = -Q, R := O

  t = modn(la * la - p.x - q.x);
  r->y = modn(la * (p.x - t) - p.y);
  r->x = t;

  if (inverr) {
    *r = zerO;
  }
}

// R:= multiple kP
void pmul(epnt *r, epnt p, long k) {

  epnt s = zerO;
  epnt q = p;

  for (; k; k >>= 1) {

    if (k & 1) {
      padd(&s, s, q);
    }

    if (inverr) {
      s = zerO;
      break;
    }

    padd(&q, q, q);
  }

  *r = s;
}

// print point P with prefix f
void pprint(char *f, epnt p) {

  dlong y = p.y;

  if (isO(p)) {
    printf("%s (0)\n", f);
  } else {
    if (y > e.N - y) {
      y -= e.N;
    }
    printf("%s (%lld, %lld)\n", f, p.x, y);
  }
}

// initialize elliptic curve
int ellinit(long i[]) {

  long a = i[0];
  long b = i[1];

  e.N = i[2];

  inverr = 0;

  if (e.N < 5 || e.N > mxN) {
    return 0;
  }

  e.a = modn(a);
  e.b = modn(b);

  e.G.x = modn(i[3]);
  e.G.y = modn(i[4]);

  e.r = i[5];

  if (e.r < 5 || e.r > mxr) {
    return 0;
  }
  printf("\n\telliptic curve init:");
  printf("\tE: y^2 = x^3 + %ldx + %ld", a, b);
  printf(" (mod %lld)\n", e.N);
  pprint("\t\t\t\tbase point G", e.G);
  printf("\t\t\t\torder(G, E) = %lld\n", e.r);

  return 1;
}

// pseudorandom number [0..1)
double rnd(void) { return rand() / ((double)RAND_MAX + 1); }

// signature primitive
pair signature(dlong s, long f) {

  long c;
  long d;
  long u;
  long u1;

  pair sg;
  epnt V;

  printf("\n\tsignature computation:");

  do {
    do {
      u = 1 + (long)(rnd() * (e.r - 1));
      pmul(&V, e.G, u);
      c = modr(V.x);
    } while (c == 0);

    u1 = exgcd(u, e.r);
    d = modr(u1 * (f + modr(s * c)));

  } while (d == 0);

  printf("\tone-time u = %ld\n", u);
  pprint("\t\t\t\tV = uG", V);

  sg.a = c;
  sg.b = d;

  return sg;
}

// verification primitive
int verify(epnt W, long f, pair sg) {

  long c = sg.a;
  long d = sg.b;
  long t;
  long c1;
  long h1;
  long h2;

  dlong h;
  epnt V, V2;

  // domain check
  t = (c > 0) && (c < e.r);
  t &= (d > 0) && (d < e.r);

  if (!t) {
    return 0;
  }

  printf("\n\tsignature verification:");

  h = exgcd(d, e.r);
  h1 = modr(f * h);
  h2 = modr(c * h);

  printf("\th1, h2 = %ld, %ld\n", h1, h2);

  pmul(&V, e.G, h1);
  pmul(&V2, W, h2);

  pprint("\t\t\t\th1G", V);
  pprint("\t\t\t\th2W", V2);

  padd(&V, V, V2);
  pprint("\t\t\t\t+ =", V);

  if (isO(V)) {
    return 0;
  }

  c1 = modr(V.x);

  printf("\t\t\t\tc' = %ld\n", c1);

  return (c1 == c);
}

// digital signature on message hash f, error bit d
void ec_dsa(long f, long d, unsigned long *signature_buffer) {

  long i;
  long s;
  long t;

  pair sg;
  epnt W;

  // parameter check
  t = (disc() == 0);
  t |= isO(e.G);

  pmul(&W, e.G, e.r);

  t |= !isO(W);
  t |= !ison(e.G);

  if (t) {
    goto errmsg;
  }

  printf("\n\tkey generation:");

  s = 1 + (long)(rnd() * (e.r - 1));

  pmul(&W, e.G, s);

  printf("\t\tprivate key s = %ld\n", s);
  pprint("\t\t\t\tpublic key W = sG", W);

  // next highest power of 2 - 1
  t = e.r;

  for (i = 1; i < 32; i <<= 1) {
    t |= t >> i;
  }

  while (f > t) {
    f >>= 1;
  }

  printf("\t\t\t\taligned hash: %ld\n", f);

  sg = signature(s, f);

  if (inverr) {
    goto errmsg;
  }

  printf("\t\t\t\tsignature c, d = %ld, %ld\n", sg.a, sg.b);

  if (d > 0) {
    while (d > t) {
      d >>= 1;
    }
    f ^= d;

    printf("\n\tcorrupted hash: %ld\n", f);
  }

  t = verify(W, f, sg);

  if (inverr) {
    goto errmsg;
  }

  if (t) {
    printf("\n\n\t\t\t\t\t  -----------\n\t\t\t\t\t     "
           "VALID\n\t\t\t\t\t  -------"
           "----\n");
    signature_buffer[0] = sg.a;
    signature_buffer[1] = sg.b;
  }

  else {
    printf("\n\n\t\t\t\t\t  -----------\n\t\t\t\t\t     "
           "INVALID\n\t\t\t\t\t  -----"
           "------\n");
  }

  return;

errmsg:
  printf("\n\t\t\t\t  ---------------------------");
  printf("\n\t\t\t\t     INVALID PARAMETER SET");
  printf("\n\t\t\t\t  ---------------------------\n");
}

void GetSignature(long hash, unsigned long *signature_buffer) {

  assert(signature_buffer != NULL);

  typedef long eparm[6];

  zerO.x = inf;
  zerO.y = 0;

  // srand(time(NULL));

  /*
   * Test vectors:
   *    elliptic curve domain parameters
   *    short Weierstrass model y^2 * = x^3 + ax + b (mod N)
   */
  eparm *sp;

  eparm sets[1] = {

      // a, b, modulus N, base point G, order(G, E), cofactor
      {355, 671, 1073741789, 13693, 10088, 1073807281}};
  /*
  {0, 7, 67096021, 6580, 779, 16769911}, // 4
  {-3, 1, 877073, 0, 1, 878159},
  {0, 14, 22651, 63, 30, 151}, // 151
  {3, 2, 5, 2, 1, 5},

  // ecdsa may fail if:
  //   the base point is of composite order
  {0, 7, 67096021, 2402, 6067, 33539822}, // 2
  //   the given order is a multiple of the true order
  {0, 7, 67096021, 6580, 779, 67079644}, // 1
  //   the modulus is not prime (deceptive example)
  {0, 7, 877069, 3, 97123, 877069},
  //   fails if the modulus divides the discriminant
  {39, 387, 22651, 95, 27, 22651}};
  */

  // digital signature on message hash f
  // f = 0x789abcde;

  // set d > 0 to simulate corrupted data
  long d = 0;

  for (sp = sets;; sp++) {
    if (ellinit(*sp)) {
      ec_dsa(hash, d, signature_buffer);
    } else {
      break;
    }
  }
}
