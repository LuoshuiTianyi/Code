#include <cstdio>
#include <cstdlib>
#define R register unsigned int
#define I inline
#define YL 51061
#define lc c[x][0]
#define rc c[x][1]
#define mul(x) \
  x *= c;      \
  x %= YL
#define add(x, c) \
  x += c;         \
  x %= YL
#define G ch = getchar()
#define gc \
  G;       \
  while (ch < '*') G
#define in(z)  \
  gc;          \
  z = ch & 15; \
  G;           \
  while (ch > '*') z *= 10, z += ch & 15, G;
const int N = 100009;
unsigned int n, f[N], c[N][2], v[N], s[N], sz[N], lm[N], la[N], st[N];
bool r[N];
I bool nroot(R x) {  //好像Dalao都写的是isroot
  return c[f[x]][0] == x || c[f[x]][1] == x;
}
I void pushup(R x) {
  s[x] = (s[lc] + s[rc] + v[x]) % YL;
  sz[x] = sz[lc] + sz[rc] + 1;
}
I void pushr(R x) {  //翻转
  R t = lc;
  lc = rc;
  rc = t;
  r[x] ^= 1;
}
I void pushm(R x, R c) {  //乘
  mul(s[x]);
  mul(v[x]);
  mul(lm[x]);
  mul(la[x]);
}
I void pusha(R x, R c) {  //加
  add(s[x], c * sz[x]);
  add(v[x], c);
  add(la[x], c);
}
I void pushdown(R x) {
  if (lm[x] != 1) pushm(lc, lm[x]), pushm(rc, lm[x]), lm[x] = 1;
  if (la[x]) pusha(lc, la[x]), pusha(rc, la[x]), la[x] = 0;
  if (r[x]) {
    if (lc) pushr(lc);
    if (rc) pushr(rc);
    r[x] = 0;
  }
}
I void rotate(R x) {
  R y = f[x], z = f[y], k = c[y][1] == x, w = c[x][!k];
  if (nroot(y)) c[z][c[z][1] == y] = x;
  c[x][!k] = y;
  c[y][k] = w;  //注意if(nroot(y))，本蒟蒻经常忘写
  if (w) f[w] = y;
  f[y] = x;
  f[x] = z;
  pushup(y);
}
I void splay(R x) {
  R y = x, z = 0;
  st[++z] = y;  //手动放个栈
  while (nroot(y)) st[++z] = y = f[y];
  while (z) pushdown(st[z--]);
  while (nroot(x)) {
    y = f[x];
    z = f[y];
    if (nroot(y)) rotate((c[y][0] == x) ^ (c[z][0] == y) ? x : y);
    rotate(x);
  }
  pushup(x);
}
I void access(R x) {
  for (R y = 0; x; x = f[y = x]) splay(x), rc = y, pushup(x);
}
I void makeroot(R x) {
  access(x);
  splay(x);
  pushr(x);
}
I void split(R x, R y) {
  makeroot(x);
  access(y);
  splay(y);
}
I void link(R x, R y) {
  makeroot(x);
  f[x] = y;
}
I void cut(R x, R y) {
  split(x, y);
  f[x] = c[y][0] = 0;
}
int main() {
  freopen("1501.in", "r", stdin);
  freopen("1501.out", "w", stdout);
  register char ch;
  R q, i, a, b, k;
  in(n);
  in(q);
  for (i = 1; i <= n; ++i) v[i] = sz[i] = lm[i] = 1;  //注意乘法标记的初值为1
  for (i = 1; i < n; ++i) {
    in(a);
    in(b);
    link(a, b);
  }
  while (q--) {
    gc;
    switch (ch) {
      case '+':
        in(a);
        in(b);
        in(k);
        split(a, b);
        pusha(b, k);
        break;
      case '-':
        in(a);
        in(b);
        cut(a, b);
        in(a);
        in(b);
        link(a, b);
        break;
      case '*':
        in(a);
        in(b);
        in(k);
        split(a, b);
        pushm(b, k);
        break;
      case '/':
        in(a);
        in(b);
        split(a, b);
        printf("%d\n", s[b]);
    }
  }
  return 0;
}
