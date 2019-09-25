#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 5e5 + 5, mod = 998244353;
int n, m, ans;
int fac[Max_n], ifac[Max_n];
int f[Max_n];
int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
int C(int n, int m) { return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int main() {
#ifndef ONLINE_JUDGE
  freopen("F.in", "r", stdin);
  freopen("F.out", "w", stdout);
#endif
  n = read(), m = read();
  if (n > m) swap(n, m);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= m; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
  ifac[m] = ksm(fac[m], mod - 2);
  for (int i = m - 1; i; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
  for (int i = 0; i <= n; i++) {
    f[i] = 1ll * C(n, i) * C(m, i) % mod * fac[i] % mod;
    f[i] = 1ll * f[i] * ksm(m + 1, n - i) % mod * ksm(n + 1, m - i) % mod;
  }
  for (int i = 0; i <= n; i++)
    ans = ((ans + ksm(-1, i & 1) * f[i]) % mod + mod) % mod;
  cout << ans;
}
