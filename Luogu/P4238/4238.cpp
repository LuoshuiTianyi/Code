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

const int Max_n = 2e5 + 5, mod = 998244353, G = 3;
int n;
int a[Max_n], ans[Max_n];

namespace Input {
void main() {
  n = read();
  for (int i = 0; i < n; i++) a[i] = read();
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
void dft(int *f, int t) {
  for (int i = 0; i < len; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int l = 1; l < len; l <<= 1) {
    int Wn = ksm(G, (mod - 1) / (l << 1));
    if (t == -1) Wn = ksm(Wn);
    for (int i = 0, Wnk = 1; i < len; i += l << 1)
      for (int k = i; k < i + l; k++, Wnk = 1ll * Wnk * Wn % mod) {
        int x = f[k], y = 1ll * f[k + l] * Wnk % mod;
        f[k] = (x + y) % mod, f[k + l] = (x + mod - y) % mod;
      }
  }
  if (t == -1) {
    int Inv = ksm(len);
    for (int i = 0; i < len; i++) f[i] = 1ll * f[i] * Inv % mod;
  }
}
void solve(int deg, int *f, int *g) {
  if (deg == 1) {
    g[0] = ksm(f[0]);
    return;
  }
  solve(deg + 1 >> 1, f, g);
  len = 1 << (bit = log2(deg) + 1), rev[0] = 0;
  for (int i = 0; i < len; i++) rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
  //for (int i = 0; i < deg; i++) F[i] = f[i];
  for (int i = deg; i < len; i++) F[i] = 0;
  dft(F, 1), dft(g, 1);
  for (int i = 0; i < len; i++)
    g[i] = 1ll * (2ll - 1ll * F[i] * g[i] % mod + mod) * g[i] % mod;
  dft(g, -1), dft(F, -1);
  for (int i = deg; i < len; i++) g[i] = 0;
}
void main() {
  solve(n, a, ans);
  for (int i = 0; i < n; i++) printf("%d ", ans[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4238.in", "r", stdin);
  freopen("4238.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
