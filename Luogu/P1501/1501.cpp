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
  k[x].sum = (k[ls(x)].sum + k[rs(x).sum] + k[x].v) % mod;
  k[x].siz = k[ls(x)].siz + k[rs(x)].siz + 1;
}
void pushdown(int x) {
}
}

namespace Input {
void main() {}
}  // namespace Input

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("1501.in", "r", stdin);
  freopen("1501.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
