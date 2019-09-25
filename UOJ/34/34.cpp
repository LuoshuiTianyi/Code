#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 3e6 + 5, mod = 998244353, G = 3;
int n, m;
int lim = 1, bit, rev[Max_n];
int f[Max_n], g[Max_n];
int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
namespace NTT {
void dft(int *f, int t) {
  for (int i = 0; i < lim; i++)
    if (rev[i] > i) swap(f[rev[i]], f[i]);
  for (int len = 1; len < lim; len <<= 1) {
    int Wn = ksm(G, (mod - 1) / (len << 1));
    if (t == -1) Wn = ksm(Wn, mod - 2);
    for (int i = 0; i < lim; i += len << 1) {
      int Wnk = 1;
      for (int k = i; k < i + len; k++, Wnk = 1ll * Wnk * Wn % mod) {
        int x = f[k], y = 1ll * Wnk * f[k + len] % mod;
        f[k] = (x + y) % mod, f[k + len] = (x + mod - y) % mod;
      }
    }
  }
}
}  // namespace NTT
void ntt(int *f, int *g) {
  NTT::dft(f, 1), NTT::dft(g, 1);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * g[i] % mod;
  NTT::dft(f, -1);
  int Inv = ksm(lim, mod - 2);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * Inv % mod;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("34.in", "r", stdin);
  freopen("34.out", "w", stdout);
#endif
  n = read(), m = read();
  bit = log2(n + m) + 1, lim = 1 << bit;
  for (int i = 0; i <= n; i++) f[i] = read();
  for (int i = 0; i <= m; i++) g[i] = read();
  for (int i = 0; i < lim; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
  ntt(f, g);
  for (int i = 0; i <= n + m; i++) printf("%d ", f[i]);
}
