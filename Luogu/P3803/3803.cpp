#include <cmath>
#include <complex>
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

const int Max_n = 4e6 + 5, mod = 998244353, G = 3;
int n, m;

int len, bit, rev[Max_n];
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
void init(int deg) {
  len = 1 << (bit = log2(deg * 3) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
}
struct poly {
  int f[Max_n];
  poly() {
    for (int i = 0; i < Max_n; i++) f[i] = 0;
  }
  void dft(int t) {
    for (int i = 0; i < len; i++)
      if (rev[i] > i) swap(f[rev[i]], f[i]);
    for (int l = 1; l < len; l <<= 1) {
      int Wn = ksm(G, (mod - 1) / (l << 1));
      if (t == -1) Wn = ksm(Wn);
      for (int i = 0; i < len; i += l << 1) {
        int Wnk = 1;
        for (int k = i; k < i + l; k++, Wnk = 1ll * Wnk * Wn % mod) {
          int x = f[k], y = 1ll * f[k + l] * Wnk % mod;
          f[k] = (x + y) % mod, f[k + l] = (x - y + mod) % mod;
        }
      }
    }
    if (t == -1)
      for (int i = 0, Inv = ksm(len); i < len; i++) f[i] = 1ll * f[i] * Inv % mod;
  }
};

poly f, g;

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 0; i <= n; i++) f.f[i] = read();
  for (int i = 0; i <= m; i++) g.f[i] = read();
}
}  // namespace Input

namespace Solve {
void main() {
  init(n + m + 2);
  f.dft(1), g.dft(1);
  for (int i = 0; i < len; i++) f.f[i] = 1ll * f.f[i] * g.f[i] % mod;
  f.dft(-1);
  for (int i = 0; i <= n + m; i++)
    printf("%d ", f.f[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3803.in", "r", stdin);
  freopen("3803.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
