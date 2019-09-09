#include <cmath>
#include <cstdio>
#include <cstring>
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
const int Max_n = 2e5 + 5, mod = 998244353, G = 3;
int n, m, K, ans;
int f[Max_n << 2], g[Max_n << 2], A[Max_n << 2];
int lim, bit, rev[Max_n << 2];
char S[Max_n], T[Max_n];
inline void Convert(char &c) {
  if (c == 'A') c = 'a';
  if (c == 'C') c = 'b';
  if (c == 'G') c = 'c';
  if (c == 'T') c = 'd';
}
inline int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
namespace NTT {
inline void dft(int *f, bool t) {
  for (int i = 0; i < lim; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int len = 1; len < lim; len <<= 1) {
    int Wn = ksm(G, (mod - 1) / (len << 1));
    if (t) Wn = ksm(Wn, mod - 2);
    for (int i = 0; i < lim; i += len << 1) {
      int Wnk = 1;
      for (int k = i; k < i + len; k++, Wnk = 1ll * Wnk * Wn % mod) {
        int x = f[k], y = 1ll * f[k + len] * Wnk % mod;
        f[k] = (x + y) % mod, f[k + len] = (x - y + mod) % mod;
      }
    }
  }
}
}  // namespace NTT
inline void ntt(int *f, int *g) {
  NTT::dft(f, 0), NTT::dft(g, 0);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * g[i] % mod;
  NTT::dft(f, 1);
  int Inv = ksm(lim, mod - 2);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * Inv % mod;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  n = read(), m = read(), K = read();
  scanf(" %s", S + 1), scanf("%s", T + 1);
  for (int i = 1; i <= n; i++) Convert(S[i]);
  for (int i = 1; i <= m; i++) Convert(T[i]);
  for (int i = 1; i <= m / 2; i++) swap(T[i], T[m - i + 1]);
  bit = log2(n + m) + 1, lim = 1 << bit;
  for (int i = 0; i < lim; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
  for (int k = 'a'; k <= 'd'; k++) {
    memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
    for (int i = 1, cnt = 0; i <= n; i++) {
      if (S[i] == k)
        cnt = K, f[i] = 1;
      else if (cnt)
        cnt--, f[i] = 1;
    }
    for (int i = n, cnt = 0; i >= 1; i--) {
      if (S[i] == k)
        cnt = K, f[i] = 1;
      else if (cnt)
        cnt--, f[i] = 1;
    }
    for (int i = 1; i <= m; i++) g[i] = T[i] == k;
    ntt(f, g);
    for (int i = 0; i < lim; i++) A[i] += f[i];
  }
  for (int i = 0; i < lim; i++)
    ans += A[i] == m;
  cout << ans;
}
