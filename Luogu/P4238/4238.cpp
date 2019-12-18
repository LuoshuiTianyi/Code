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

const int Max_n = 2e5 + 5, mod = 998244353, G = 3;
int n;
int a[Max_n];

namespace Input {
void main() {
  n = read();
  for (int i = 0; i <= n; i++) a[i] = read();
}
}  // namespace Input

namespace Solve {
int bit, len, F[Max_n], rev[Max_n];
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
void solve(int deg, int *f, int *g) {
  if (deg == 1) {
    g[0] = ksm(f[0]);
    return;
  }
  solve(deg + 1 >> 1, f, g);
  len = 1 << (bit = log2(deg) + 1);
  for (int i = 0; i < len; i++) rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
  for (int i = 0; i < deg; i++) F[i] = f[i];
  for (int i = deg; i < len; i++) F[i] = 0;
  dft(F, 1), dft(g, 1);
}
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4238.in", "r", stdin);
  freopen("4238.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
