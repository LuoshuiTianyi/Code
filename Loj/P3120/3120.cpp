#include <cmath>
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

const int Max_n = 8e5 + 5, mod = 998244353;

namespace Poly {
int len, bit, rev[Max_n];
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << bit - 1);
}
void dft(int *f, bool t) {
  for (int i = 0; i < len; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int i = 
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
  freopen("3120.in", "r", stdin);
  freopen("3120.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
