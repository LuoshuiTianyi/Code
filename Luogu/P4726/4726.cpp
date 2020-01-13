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

const int Max_n = 6e5 + 5, mod = 998244353, G = 3, Len = 1 << 19;
int n;

int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}

namespace Poly {
int bit, len, rev[Max_n];
int gp[Max_n], invn[Max_n];
struct poly {
  int f[Max_n];
  inline int& operator[](int x) {
    return f[x];
  }
  void dft(int t) {
    for (int i = 0; i < len; i++)
      if (rev[i] > i) swap(f[i], f[rev[i]]);
    for (int l = 1; l < len; l <<= 1) {
      int Wn = Len / (l << 1);
      for (int i = 0; i < len; i += l << 1) {
        for (int k = i; k < i + l; k++) {
          int x = f[k], p = (k - i) * Wn;
          int y = 1ll * f[k + l] * (t == -1 ? gp[Len - p] : gp[p]) % mod;
          f[k] = (x + y) % mod, f[k + l] = (x - y + mod) % mod;
        }
      }
    }
    if (t == -1)
      for (int i = 0, Inv = invn[len]; i < len; i++) 
        f[i] = 1ll * f[i] * Inv % mod;
  }
};
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
}
void inv(int n, poly &f, poly &g) {
  static poly F;
  g[0] = ksm(f[0]);
  for (int deg = 2; deg < (n << 1); deg <<= 1) {
    init(deg * 3);
    for (int i = 0; i < deg; i++) F[i] = f[i];
    for (int i = deg; i < len; i++) F[i] = g[i] = 0;
    g.dft(1), F.dft(1);
    for (int i = 0; i < len; i++)
      g[i] = 1ll * g[i] * (2 - 1ll * g[i] * F[i] % mod + mod) % mod;
    g.dft(-1);
    for (int i = deg; i < len; i++) g[i] = 0;
  }
}
void ln(int n, poly &f, poly &g) {
  static poly df, Inv;
  for (int i = 0; i < n - 1; i++) df[i] = 1ll * f[i + 1] * (i + 1) % mod;
  df[n - 1] = 0, inv(n, f, Inv), init(n * 2);
  for (int i = n; i < len; i++) df[i] = 0;
  for (int i = 0; i < len; i++) g[i] = 0;
  df.dft(1), Inv.dft(1);
  for (int i = 0; i < len; i++) g[i] = 1ll * df[i] * Inv[i] % mod;
  g.dft(-1);
  for (int i = n - 1; i; i--) g[i] = 1ll * g[i - 1] * invn[i] % mod;
  g[0] = 0;
}
void exp(int n, poly &f, poly &g) {
  static poly Ln, F;
  g[0] = 1;
  for (int deg = 2; deg < (n << 1); deg <<= 1) {
    ln(deg, g, Ln), init(deg);
    for (int i = 0; i < deg; i++) F[i] = f[i];
    for (int i = deg; i < len; i++) F[i] = g[i] = 0;
    g.dft(1), F.dft(1), Ln.dft(1);
    for (int i = 0; i < len; i++) 
      g[i] = 1ll * g[i] * (1 - Ln[i] + F[i] + mod) % mod;
    g.dft(-1);
    for (int i = deg; i < len; i++) g[i] = 0;
  }
}
}
using namespace Poly;

poly a, ans;

namespace Input {
void main() {
  n = read();
  for (int i = 0; i < n; i++) a[i] = read();
}
}  // namespace Input

namespace Init {
void main() {
  invn[0] = invn[1] = gp[0] = 1;
  int g = ksm(G, (mod - 1) / Len);
  for (int i = 1; i <= Len; i++) gp[i] = 1ll * gp[i - 1] * g % mod;
  for (int i = 2; i <= Len; i++) invn[i] = 1ll * (mod - mod / i) * invn[mod % i] % mod;
}
}

namespace Solve {
void main() {
  exp(n, a, ans);
  for (int i = 0; i < n; i++) printf("%d ", ans[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4726.in", "r", stdin);
  freopen("4726.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
