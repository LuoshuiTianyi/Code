#include <cmath>
#include <cstdio>
#include <cstring>
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

const int Max_n = 6e5 + 5, mod = 998244353;
int n;
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}

namespace Poly {
int len, bit, rev[Max_n];
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
}
struct poly {
  int f[Max_n];
  int& operator[](int x) { return f[x]; }
  void init() {
    memset(f, 0, sizeof f);
  }
  void dft(int t) {
    for (int i = 0; i < len; i++)
      if (rev[i] > i) swap(f[rev[i]], f[i]);
    for (int l = 1; l < len; l <<= 1) {
      int Wn = ksm(3, (mod - 1) / (l << 1));
      if (t) Wn = ksm(Wn);
      for (int i = 0; i < len; i += l << 1) {
        int Wnk = 1;
        for (int k = i; k < i + l; k++, Wnk = 1ll * Wnk * Wn % mod) {
          int x = f[k], y = 1ll * f[k + l] * Wnk % mod;
          f[k] = (x + y) % mod, f[k + l] = (x - y + mod) % mod;
        }
      }
    }
    if (t)
      for (int i = 0, Inv = ksm(len); i < len; i++)
        f[i] = 1ll * f[i] * Inv % mod;
  }
};
void Mul(poly &f, poly &g, int N) {
  init(N);
  f.dft(0), g.dft(0);
  for (int i = 0; i < len; i++) f[i] = (LL)f[i] * g[i] % mod;
  f.dft(1), g.dft(1);
}
void Inv(poly &f, poly &g, int N) {
  static poly F;
  g.init(), g[0] = ksm(f[0]);
  for (int deg = 2; deg < (N << 1); deg <<= 1) {
    init(deg * 3);
    for (int i = 0; i < deg; i++) F[i] = f[i];
    for (int i = deg; i < len; i++) F[i] = 0;
    F.dft(0), g.dft(0);
    for (int i = 0; i < len; i++) 
      g[i] = (2ll * g[i] % mod + mod - (LL)g[i] * g[i] % mod * F[i] % mod) % mod;
    g.dft(-1);
    for (int i = deg; i < len; i++) g[i] = 0;
  }
}
void Sqrt(poly &f, poly &g, int N) {
  static poly inv, F;
  g.init(), inv.init(), g[0] = 1;
  for (int deg = 2; deg < (N << 1); deg <<= 1) {
    Inv(g, inv, deg), init(deg * 3);
    for (int i = 0; i < deg; i++) F[i] = f[i];
    for (int i = deg; i < len; i++) F[i] = 0;
    g.dft(0), inv.dft(0), F.dft(0);
    for (int i = 0; i < len; i++)
      g[i] = (LL)inv[i] * ((LL)g[i] * g[i] % mod + F[i]) % mod;
    g.dft(1);
    for (int i = 0, iv = ksm(2); i < deg; i++) g[i] = (LL)iv * g[i] % mod;
    for (int i = deg; i < len; i++) g[i] = 0;
  }
}
}  // namespace Poly
using namespace Poly;

poly f, ans;

namespace Input {
void main() { 
  n = read(); 
  for (int i = 0; i < n; i++) f[i] = read();
}
}  // namespace Input

namespace Solve {
void main() {
  Sqrt(f, ans, n);
  for (int i = 0; i < n; i++) printf("%d ", ans[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("5205.in", "r", stdin);
  freopen("5205.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}

