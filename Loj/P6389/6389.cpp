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

namespace FastMod {
typedef unsigned long long ull;
typedef __uint128_t L;
ull b, m;
void init(ull x) {
  b = x;
  m = ull((L(1) << 64) / b);
}
ull Mod(ull x) {
  ull q = L(m) * x >> 64;
  ull res = x - q * b;
  return res >= b ? res - b : res;
}
}
using namespace FastMod;

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
    for (int j = 1; j < i; j++) f[i] = Mod((ull)f[j] * h[i - j] + f[i]);
    f[i] = Mod(2ull * f[i] * ksm(i));
    g[i] = Mod((ull)ksm(2) * f[i]) + (i == 1), f[i] += (i == 1);
    for (int j = i; j <= n; j += i) {
      h[j] = Mod((ull)i * g[i] + h[j]);
      if (j > i) f[j] = Mod((ull)i * g[i] + f[j]);
    }
  }
}
}  // namespace Init

int main() {
#ifndef ONLINE_JUDGE
  freopen("6389.in", "r", stdin);
  freopen("6389.out", "w", stdout);
#endif
  T = read(), init(mod = read());
  Init::main();
  while(T--) {
    n = read();
    printf("%d\n", f[n]);
  }
}