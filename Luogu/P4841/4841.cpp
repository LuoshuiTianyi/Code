#include <cmath>
#include <cstdio>
#include <cstring>
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

const int Max_n = 130000 << 3, mod = 1004535809;
int n;
int fac[Max_n], ifac[Max_n];
int f[Max_n], g[Max_n], h[Max_n];

namespace Poly {
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}
int len, bit, rev[Max_n];
void Init(int *f) {
  memset(f, 0, sizeof f);
}
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
}
void dft(int *f, bool t) {
  for (int i = 0; i < len; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int l = 1; l < len; l <<= 1) {
    int Wn = ksm(3, (mod - 1) / (l << 1));
    if (t) Wn = ksm(Wn);
    for (int i = 0; i < len; i += l << 1) {
      int Wnk = 1;
      for (int k = i; k < i + l; k++, Wnk = (LL)Wnk * Wn % mod) {
        int x = f[k], y = (LL)f[k + l] * Wnk % mod;
        f[k] = (x + y) % mod, f[k + l] = (x + mod - y) % mod;
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
  dft(g, 1), dft(f, 1);
}
void Inv(int *f, int *g, int N) {
  static int F[Max_n];
  Init(g), g[0] = ksm(f[0]);
  for (int deg = 2; deg < (N << 1); deg <<= 1) {
    init(deg * 3);
    for (int i = 0; i < deg; i++) F[i] = f[i];
    for (int i = deg; i < len; i++) F[i] = 0;
    dft(g, 0), dft(F, 0);
    for (int i = 0; i < len; i++)
      g[i] = (LL)g[i] * (2ll - (LL)g[i] * F[i] % mod + mod) % mod;
    dft(g, 1);
    for (int i = deg; i < len; i++) g[i] = 0;
  }
}
}  // namespace Poly
using namespace Poly;

namespace Input {
void main() {
  n = read();
}
}  // namespace Input

namespace Init {
void main() {
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = (LL)fac[i - 1] * i % mod;
  ifac[n] = ksm(fac[n]);
  for (int i = n; i; i--) ifac[i - 1] = (LL)ifac[i] * i % mod;
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 1; i <= n; i++) h[i] = (LL)ifac[i - 1] * ksm(2, (LL)i * (i - 1) / 2 % (mod - 1)) % mod;
  for (int i = 0; i <= n; i++) g[i] = (LL)ifac[i] * ksm(2, (LL)i * (i - 1) / 2 % (mod - 1)) % mod;
  Inv(g, f, n);
  Mul(f, h, n * 2);
  cout << (LL)f[n] * fac[n - 1] % mod << endl;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4841.in", "r", stdin);
  freopen("4841.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
