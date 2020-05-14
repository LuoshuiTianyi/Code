#pragma GCC optimize(3)

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

const int Max_n = 3e4 + 5;
int T, mod, n;
int f[Max_n], g[Max_n], h[Max_n];

namespace Init {
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL) res * a % mod;
  return res;
}
void main() {
  n = 23333;
  for (int i = 1; i <= n; i++) {
    __int128 t = 0;
    for (int j = 1; j < i; j++) t += (LL)f[j] * h[i - j];
    f[i] = t % mod;
    f[i] = 2ll * (t % mod) * ksm(i) % mod;
    g[i] = (LL)ksm(2) * f[i] % mod + (i == 1), f[i] += (i == 1);
    for (int j = i; j <= n; j += i) {
      (h[j] += (LL)i * g[i] % mod) %= mod;
      if (j > i) (f[j] += (LL)i * g[i] % mod) %= mod;
    }
  }
}
}  // namespace Init

int main() {
#ifndef ONLINE_JUDGE
  freopen("6389.in", "r", stdin);
  freopen("6389.out", "w", stdout);
#endif
  T = read(), mod = read();
  Init::main();
  while(T--) {
    n = read();
    printf("%d\n", f[n]);
  }
}
