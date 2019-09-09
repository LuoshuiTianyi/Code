#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
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
const int Max_n = 1505, Max_l = 5e6 + 5, mod = 998244353, G = 3;
int n, m, K, ans, dx[5] = {0, -1, 1, 0, 0}, dy[5] = {0, 0, 0, -1, 1};
int lim, bit, rev[Max_l], f[Max_l], g[Max_l];
int s[Max_l], a[Max_n][Max_n];
char S[Max_l];
int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
namespace NTT {
void dft(int *f, bool t) {
  for (int i = 0; i < lim; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int len = 1; len < lim; len <<= 1) {
    int Wn = ksm(G, (mod - 1) / (len << 1));
    if (!t) Wn = ksm(Wn, mod - 2);
    for (int i = 0; i < lim; i += len << 1) {
      int Wnk = 1;
      for (int k = i; k < i + len; k++, Wnk = 1ll * Wnk * Wn % mod) {
        int x = f[k], y = 1ll * Wnk * f[k + len] % mod;
        f[k] = (x + y) % mod, f[k + len] = (x - y + mod) % mod;
      }
    }
  }
}
}  // namespace NTT
void ntt(int *f, int *g) {
  NTT::dft(f, 0), NTT::dft(g, 0);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * g[i] % mod;
  NTT::dft(f, 1);
  int Inv = ksm(lim, mod - 2);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * Inv % mod;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("5447.in", "r", stdin);
  freopen("5447.out", "w", stdout);
#endif
  n = read(), m = read(), K = read();
  for (int i = 0; i < n; i++) {
    scanf("%s", S);
    for (int j = 0; j < m; j++) f[i * m + j] = S[j] == '1';
  }
  scanf("%s", S + 1);
  for (int i = 1; i <= K; i++) {
    if (S[i] == 'w') s[i] = 1;
    if (S[i] == 's') s[i] = 2;
    if (S[i] == 'a') s[i] = 3;
    if (S[i] == 'd') s[i] = 4;
  }
  int sx = 0, sy = 0, l = 0, r = 0, u = 0, d = 0;
  for (int i = 1; i <= K; i++) {
    sx += dx[s[i]], sy += dy[s[i]];
    l = min(l, sy), r = max(r, sy), u = min(u, sx), d = max(d, sx);
  }
  r -= l, sy = -l, l = 0, d -= u, sx = -u, u = 0;
  a[sx][sy] = 1;
  for (int i = 1; i <= K; i++) a[sx += dx[s[i]]][sy += dy[s[i]]] = 1;
  for (int i = 0; i <= d; i++)
    for (int j = 0; j < m; j++) g[i * m + j] = a[i][j] == 1;
  for (int i = 0; i < (d + 1) * m / 2; i++) swap(g[i], g[(d + 1) * m - i - 1]);
  bit = log2(n * m + (d + 1) * m) + 1, lim = 1 << bit;
  for (int i = 0; i < lim; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
  ntt(f, g);
  for (int i = 0; i < n - d; i++)
    for (int j = 0; j < m - r; j++) ans += !f[(d + i + 1) * m + j - 1];
  cout << ans;
}
