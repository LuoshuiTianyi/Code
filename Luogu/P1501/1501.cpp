#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}

const int Max_n = 1e5 + 5, mod = 51061;
int n, Q;

struct node {
  int fa, t1, t2, t3, siz, v, sum, s[2];
} k[Max_n];
namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
bool kd(int x) { return rs(k[x].fa) == x; }
bool nrt(int x) { return kd(x) || ls(k[x].fa) == x; }
void upd(int x) {
  k[x].sum = (k[ls(x)].sum + k[rs(x)].sum + k[x].v) % mod;
  k[x].siz = k[ls(x)].siz + k[rs(x)].siz + 1;
}
void roll(int x) { 
  if (!x) return;
  swap(ls(x), rs(x)), k[x].t1 ^= 1; 
}
void mul(int x, int v) {
  if (!x) return;
  k[x].v = 1ll * k[x].v * v % mod;
  k[x].sum = 1ll * k[x].sum * v % mod;
  k[x].t2 = 1ll * k[x].t2 * v % mod;
  k[x].t3 = 1ll * k[x].t3 * v % mod;
}
void add(int x, int v) {
  if (!x) return;
  (k[x].v += v) %= mod;
  (k[x].sum += 1ll * v * k[x].siz % mod) %= mod;
  (k[x].t3 += v) %= mod;
}
void pushdown(int x) {
  if (k[x].t1) roll(ls(x)), roll(rs(x)), k[x].t1 = 0;
  if (k[x].t2 != 1) mul(ls(x), k[x].t2), mul(rs(x), k[x].t2), k[x].t2 = 1;
  if (k[x].t3) add(ls(x), k[x].t3), add(rs(x), k[x].t3), k[x].t3 = 0;
}
void rotate(int x) {
  int y = k[x].fa, z = k[y].fa, s1 = kd(x), s2 = k[x].s[!s1];
  if (nrt(y)) k[z].s[kd(y)] = x;
  k[x].s[!s1] = y, k[y].s[s1] = s2;
  if (s2) k[s2].fa = y;
  k[y].fa = x, k[x].fa = z, upd(y);
}
void Push(int x) {
  if (nrt(x)) Push(k[x].fa);
  pushdown(x);
}
void splay(int x) {
  Push(x);
  for (int fa = k[x].fa; nrt(x); rotate(x), fa = k[x].fa)
    if (nrt(fa)) rotate(kd(fa) ^ kd(x) ? fa : x);
  upd(x);
}
void access(int x) {
  for (int y = 0; x; x = k[y = x].fa) splay(x), rs(x) = y, upd(y);
}
void makert(int x) { access(x), splay(x), roll(x); }
void link(int x, int y) { makert(x), k[x].fa = y; }
void cut(int x, int y) {
  makert(x), access(y), splay(y);
  ls(y) = k[x].fa = 0, upd(y);
}
void modify(int x, int y, char op, int v) {
  makert(x), access(y), splay(y);
  if (op == '*')
    mul(y, v);
  else
    add(y, v);
}
int query(int x, int y) {
  makert(x), access(y), splay(y);
  return k[y].sum;
}
}  // namespace LCT

namespace Input {
void main() {
  n = read(), Q = read();
  for (int i = 1; i <= n; i++) k[i].v = k[i].t2 = 1;
  for (int i = 1; i < n; i++) {
    int u = read(), v = read();
    LCT::link(u, v);
  }
}
}  // namespace Input

namespace Solve {
void main() {
  char op;
  int u, v, a, b, x;
  while (Q--) {
    scanf(" %c", &op);
    u = read(), v = read();
    if (op == '-') {
      a = read(), b = read();
      LCT::cut(u, v);
      LCT::link(a, b);
    } else if (op == '/') {
      printf("%d\n", LCT::query(u, v));
    } else {
      x = read();
      LCT::modify(u, v, op, x);
    }
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("1501.in", "r", stdin);
  freopen("1501.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
