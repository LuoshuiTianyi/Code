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

const int Max_n = 1e4 + 5;
int n, m;

struct node {
  int fa, tag, s[2];
} k[Max_n];
namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
bool kd(int x) { return rs(k[x].fa) == x; }
bool nrt(int x) { return kd(x) || ls(k[x].fa) == x; }
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
  k[y].fa = x, k[x].fa = z;
}
void Push(int x) {
  if (nrt(x)) Push(k[x].fa);
  pushdown(x);
}
void splay(int x) {
  Push(x);
  for (int fa = k[x].fa; nrt(x); rotate(x), fa = k[x].fa)
    if (nrt(fa)) rotate(kd(fa) ^ kd(x) ? x : fa);
}
void access(int x) {
  for (int y = 0; x; x = k[y = x].fa) splay(x), rs(x) = y;
}
void makert(int x) { access(x), splay(x), roll(x); }
int findrt(int x) {
  access(x), splay(x);
  while (ls(x)) x = ls(x);
  return x;
}
void link(int x, int y) { makert(x), k[x].fa = y; }
void cut(int x, int y) {
  makert(x), access(y), splay(y);
  ls(y) = k[x].fa = 0;
}
bool query(int x, int y) {
  makert(x);
  return findrt(y) == x;
}
}  // namespace LCT

namespace Input {
void main() { n = read(), m = read(); }
}  // namespace Input

namespace Solve {
void main() {
  char s[10];
  int u, v;
  while (m--) {
    scanf(" %s", s);
    u = read(), v = read();
    if (s[0] == 'Q') printf("%s\n", LCT::query(u, v) ? "Yes" : "No");
    if (s[0] == 'C') LCT::link(u, v);
    if (s[0] == 'D') LCT::cut(u, v);
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2147.in", "r", stdin);
  freopen("2147.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
