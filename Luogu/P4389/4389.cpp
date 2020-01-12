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

const int Max_n = 6e5 + 5, mod = 998244353, G = 3;

int bit, len, rev[Max_n];
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
}
struct poly {
  int f[Max_n];
  inline int& operator[](int x) {
    return f[x];
  }
  void Init() {
    for (int i = 0; i < Max_n; i++) f[i] = 0;
  }
  void dft(int t) {
    for (int i = 0; i < len; i++)
      if (rev[i] > i) swap(f[i], f[rev[i]]);
    for (int l = 1; l < len; l <<= 1) {
      int Wn = ksm(G, (mod - 1) / (l << 1));
      if (t == -1) Wn = ksm(Wn);
      for (int i = 0; i < len; i += l << 1) {
        int Wnk = 1;
        for (int k = i; k < i + l; k++, Wnk = 1ll * Wnk * Wn % mod) {
          int x = f[k], y = 1ll * f[k + l] * Wnk % mod;
          f[k] = (x + y) % mod, f[k + l] = (x - y + 1) % mod;
        }
      }
    }
    if (t == -1)
      for (int i = 0, Inv = ksm(len); i < len; i++) 
        f[i] = 1ll * f[i] * Inv % mod;
  }
  void inv(int n, poly &G) {
    static poly F, g;
    F.Init(), g.Init();
    g[0] = ksm(f[0]);
    for (int deg = 2; deg < (n << 1); deg <<= 1) {
      init(deg * 3);
      for (int i = 0; i < deg; i++) F[i] = f[i];
      for (int i = deg; i < len; i++) F[i] = 0;
      g.dft(1), F.dft(1);
      for (int i = 0; i < len; i++)
        g[i] = 1ll * g[i] * (2 - 1ll * g[i] * F[i] % mod + mod) % mod;
      g.dft(-1);
      for (int i = deg; i < len; i++) g[i] = 0;
    }
    G = g;
  }
  void der(int n, poly &G) {
    static poly g;
    g.Init();
    for (int i = 0; i < n - 1; i++) g[i] = 1ll * f[i + 1] * (i + 1) % mod;
    G = g;
  }
  void itg(int n, poly &G) {
    static poly g;
    g.Init();
    for (int i = 1; i < n; i++) g[i] = 1ll * f[i - 1] * i % mod;
    G = g;
  }
  void ln(int n, poly &G) {
    static poly df, Inv, g;
    der(n, df),inv(n, Inv), init(n * 2);
    df.dft(1), Inv.dft(1);
    for (int i = 0; i < len; i++) g[i] = 1ll * df[i] * Inv[i] % mod;
    g.dft(-1), g.itg(n, G);
  }
  void exp(int n, poly &G) {
    static poly Ln, F, g;
    g.Init(), F.Init();
    g[0] = 1;
    for (int deg = 2; deg < (n << 1); deg <<= 1) {
      Ln = g.ln(deg), init(deg * 2);
      for (int i = 0; i < deg; i++) F[i] = f[i];
      for (int i = deg; i < len; i++) F[i] = 0;
      g.dft(1), F.dft(1), Ln.dft(1);
      for (int i = 0; i < len; i++) 
        g[i] = 1ll * g[i] * (1 - Ln[i] + F[i] + mod) % mod;
      g.dft(-1);
      for (int i = deg; i < len; i++) g[i] = 0;
    }
    G = g;
  }
};

int n, m, exi[Max_n];
poly a, ans;

namespace Input {
void main() {
  n = read();//, m = read();
  for (int i = 0; i < n; i++) a[i] = read();// exi[read()] = 1;
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++)
    if (exi[i])
      for (int j = 1; j * i <= m; j++)
        (a[j * i] += ksm(j)) %= mod;
}
}  // namespace Init

namespace Solve {
void main() {
  a.exp(n, ans);
  for (int i = 0; i < n; i++)
    printf("%d\n", ans[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4389.in", "r", stdin);
  freopen("4389.out", "w", stdout);
#endif
  Input::main();
  //Init::main();
  Solve::main();
}
