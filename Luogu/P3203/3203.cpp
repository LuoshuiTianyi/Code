#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
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

const int Max_n = 2e5 + 5;
int n, m;
int a[Max_n];

struct node {
  int fa, siz, tag, s[2];
} k[Max_n];
namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
bool kd(int x) { return rs(k[x].fa) == x; }
bool nrt(int x) { return kd(x) || ls(k[x].fa) == x; }
void upd(int x) {
  if (!x) return;
  k[x].siz = k[ls(x)].siz + k[rs(x)].siz + 1;
}
void roll(int x) {
  if (!x) return;
  swap(ls(x), rs(x)), k[x].tag ^= 1;
}
void pushdown(int x) {
  if (k[x].tag) roll(ls(x)), roll(rs(x)), k[x].tag = 0;
}
void rotate(int x) {
  int y = k[x].fa, z = k[y].fa, s1 = kd(x), s2 = k[x].s[!s1];
  if (nrt(y)) k[z].s[kd(y)] = x;
  k[x].s[!s1] = y, k[y].s[s1] = s2;
  if (s2) k[s2].fa = y;
  k[x].fa = z, k[y].fa = x, upd(y);
}
int stk[Max_n];
void splay(int x) {
  int top = 0, p = x;
  for (; nrt(p); p = k[p].fa) stk[++top] = p;
  stk[++top] = p;
  while (top) pushdown(stk[top--]);
  for (int fa = k[x].fa; nrt(x); rotate(x), fa = k[x].fa)
    if (nrt(fa)) rotate(kd(fa) ^ kd(x) ? x : fa);
  upd(x);
}
void access(int x) {
  for (int y = 0; x; x = k[y = x].fa) splay(x), rs(x) = y;
}
void makert(int x) { access(x), splay(x), roll(x); }
void link(int x, int y) { 
  y = min(y, n + 1);
  makert(x), k[x].fa = y; 
}
void cut(int x, int y) {
  y = min(y, n + 1);
  makert(x), access(y), splay(y);
  ls(y) = k[x].fa = 0, upd(y);
}
int query(int x) {
  makert(n + 1), access(x), splay(x);
  return k[x].siz - 1;
}
}  // namespace LCT

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) a[i] = read(), LCT::link(i, i + a[i]);
}
}  // namespace Input

namespace Solve {
void main() {
  m = read();
  while (m--) {
    int op = read(), x = read() + 1;
    if (op == 1)
      printf("%d\n", LCT::query(x));
    else {
      LCT::cut(x, x + a[x]), LCT::link(x, x + (a[x] = read()));
    }
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3203.in", "r", stdin);
  freopen("3203.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
