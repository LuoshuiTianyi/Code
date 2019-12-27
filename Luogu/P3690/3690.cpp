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

struct node {
  int fa, v, sum, tag, s[2];
} k[Max_n];
namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
bool nrt(int x) { return ls(k[x].fa) == x || rs(k[x].fa) == x; }
bool kd(int x) { return rs(k[x].fa) == x; }
void upd(int x) { k[x].sum = k[ls(x)].sum ^ k[rs(x)].sum ^ k[x].v; }
void roll(int x) { 
  if (!x) return;
  swap(ls(x), rs(x)), k[x].tag ^= 1; 
}
void pushdown(x) {
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
}
}  // namespace LCT

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) k[i].v = read();
}
}  // namespace Input

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3690.in", "r", stdin);
  freopen("3690.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
