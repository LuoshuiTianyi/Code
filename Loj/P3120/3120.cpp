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

int D, n, m;
int fac[Max_n], ifac[Max_n];
int f[Max_n], g[Max_n], G[Max_n];

int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}

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
  for (int l = 1; l < len; l <<= 1) {
    int Wn = ksm(3, (mod - 1) / (l << 1));
    if (t) Wn = ksm(Wn);
    for (int i = 0; i < len; i += l << 1) {
      int Wnk = 1;
      for (int j = i; j < i + l; j++, Wnk = (LL)Wnk * Wn % mod) {
        int x = f[j], y = (LL)f[j + l] * Wnk % mod;
        f[j] = (x + y) % mod, f[j + l] = (x - y + mod) % mod;
      }
    }
  }
  if (t)
    for (int i = 0, Inv = ksm(len); i < len; i++) f[i] = (LL)f[i] * Inv % mod;
}
void Mul(int *f, int *g, int N) {
  init(N);
  dft(f, 0), dft(g, 0);
  for (int i = 0; i < len; i++) f[i] = (LL)f[i] * g[i] % mod;
  dft(f, 1), dft(g, 1);
}
}  // namespace Poly

namespace Input {
void main() {
  D = read(), n = read(), m = read();
}
}  // namespace Input

namespace Init {
void main() {
  fac[0] = 1;
  for (int i = 1; i <= D; i++) fac[i] = (LL)fac[i - 1] * i % mod;
  ifac[D] = ksm(fac[D]);
  for (int i = D; i; i--) ifac[i - 1] = (LL)ifac[i] * i % mod;
}
}

namespace Solve {
int C(int n, int m) {
  if (n < m || m < 0) return 0;
  return (LL)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
void main() {
  for (int i = 0, t = 1; i <= D; i++, t *= -1) {
    G[i] = ifac[i];
    g[i] = (LL)(t + mod) * ksm((D - 2 * i + mod) % mod, n) % mod * ifac[i] % mod;
  }
  Mul(G, g, D + 1 << 1);
  for (int i = 0; i <= D; i++) G[i] = (LL)ksm(ksm(2, i)) * G[i] % mod;
  for (int i = 
}
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
