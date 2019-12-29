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

struct node {
  int fa, t1, t2, c, c1, c2, sum, s[2];
} k[Max_n];
namespace LCT {
void upd(int x) {
  k[x].c1 = k[ls(x)].c2, k[x].c2 = k[rs(x)].c1;
  k[x].sum = k[ls(x)].sum + k[rs(x)].sum + 1;
  k[x].sum -= k[x].c == k[x].c1 + k[x].c == k[x].c2;
}
}

namespace Input {
void main() {}
}  // namespace Input

namespace Init {
void main() {}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2486.in", "r", stdin);
  freopen("2486.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
