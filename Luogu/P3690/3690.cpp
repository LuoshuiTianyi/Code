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

const int Max_n = 1e5 + 5;
int n, m;

struct Splay {
  int fa, tag, v, sum, s[2];
} k[Max_n];
namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
bool kd(int x) { return ls(k[x].fa) == x; }
bool nrt(int x) { return ls(k[x].fa) == x || rs(k[x].fa) == x; }
void upd(int x) { k[x].sum = k[ls(x)].sum ^ k[rs(x)].sum ^ k[x].v; }
void pushdown(int x) {
  if (k[x].tag) {
    swap(ls(x), rs(x));
    k[ls(x)].tag ^= 1, k[rs(x)].tag ^= 1, k[x].tag = 0;
  }
}
void rotate(int x) {
  int y = k[x].fa, z = k[y].fa, s1 = kd(x), s2 = k[x].s[!s1];
  pushdown(x), pushdown(y);
  if (nrt(y)) k[z].s[kd(y)] = x;
  k[x].s[!s1] = y, k[y].s[s1] = s2;
  if (s2) k[s2].fa = y;
  k[x].fa = z, k[y].fa = x, upd(y);
}
void splay(int x) {
  for (int fa = k[x].fa; nrt(x); rotate(x), fa = k[x].fa)
    if (nrt(fa)) rotate(kd(x) ^ kd(fa) ? x : fa);
  upd(x);
}
void access(int x) {
  for (int y = 0; x; x = k[y = x].fa) splay(x), rs(x) = y, upd(x);
}
void makert(int x) { access(x), splay(x), k[x].tag ^= 1, pushdown(x); }
int findrt(int x) {
  access(x), splay(x);
  while (ls(x)) pushdown(x), x = ls(x);
  splay(x);
  return x;
}
int query(int x, int y) {
  makert(x), access(y), splay(y);
  return k[y].sum;
}
void link(int x, int y) {
  makert(x);
  if (findrt(y) != x) k[x].fa = y;
}
void cut(int x, int y) {
  makert(x);
  if (findrt(y) == x && k[y].fa == x && !ls(y)) k[y].fa = rs(x) = 0, upd(x);
}
}  // namespace LCT

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) k[i].v = read();
}
}  // namespace Input

namespace Solve {
void main() {
  int op, x, y;
  while (m--) {
    op = read(), x = read(), y = read();
    if (op == 0) printf("%d\n", LCT::query(x, y));
    if (op == 1) LCT::link(x, y);
    if (op == 2) LCT::cut(x, y);
    if (op == 3) LCT::splay(x), k[x].v = y;
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3690.in", "r", stdin);
  freopen("3690.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
