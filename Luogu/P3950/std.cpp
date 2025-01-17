#include <cstdio>
#include <cstdlib>
#define R register int
#define I inline void
#define lc c[x][0]
#define rc c[x][1]
#define G ch = getchar()
#define gc \
  G;       \
  while (ch < '-') G
#define in(z)  \
  gc;          \
  z = ch & 15; \
  G;           \
  while (ch > '-') z *= 10, z += ch & 15, G;
const int N = 300009;
int f[N], c[N][2], st[N], u[N], v[N];
bool r[N];
inline bool nroot(R x) { return c[f[x]][0] == x || c[f[x]][1] == x; }
I pushdown(R x) {
  if (r[x]) {
    R t = lc;
    lc = rc;
    rc = t;
    r[lc] ^= 1, r[rc] ^= 1, r[x] = 0;
  }
}
I rotate(R x) {
  R y = f[x], z = f[y], k = c[y][1] == x, w = c[x][!k];
  if (nroot(y)) c[z][c[z][1] == y] = x;
  c[x][!k] = y;
  c[y][k] = w;
  if (w) f[w] = y;
  f[y] = x;
  f[x] = z;
}
I splay(R x) {
  R y = x, z = 0;
  st[++z] = y;
  while (nroot(y)) st[++z] = y = f[y];
  while (z) pushdown(st[z--]);
  while (nroot(x)) {
    y = f[x];
    z = f[y];
    if (nroot(y)) rotate((c[y][0] == x) ^ (c[z][0] == y) ? x : y);
    rotate(x);
  }
}
I access(R x) {
  for (R y = 0; x; x = f[y = x]) splay(x), rc = y;
}
I makeroot(R x) {
  access(x);
  splay(x);
  r[x] ^= 1;
}
inline int findroot(R x) {
  access(x);
  splay(x);
  pushdown(x);
  while (lc) pushdown(x = lc);
  return x;
}
I split(R x, R y) {
  makeroot(x);
  access(y);
  splay(y);
}
I link(R x, R y) {
  makeroot(x);
  f[x] = y;
}
I cut(R x, R y) {
  split(x, y);
  f[x] = c[y][0] = 0;
}
int main() {
  freopen("3950.in", "r", stdin);
  freopen("3950.ans", "w", stdout);
  register char ch;
  R n, m, p = 0, a, b;
  in(n);
  in(m);
  for (R i = 1; i < n; ++i) {
    in(a);
    in(b);
    link(a, b);
  }
  while (m--) {
    gc;
    switch (ch) {
      case 'U':
        in(a);
        link(u[a], v[a]);
        break;
      case 'C':
        in(a);
        in(b);
        ++p;
        cut(u[p] = a, v[p] = b);
        break;
      case 'Q':
        in(a);
        in(b);
        puts(findroot(a) == findroot(b) ? "Yes" : "No");
    }
  }
  return 0;
}
