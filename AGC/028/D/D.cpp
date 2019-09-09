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
const int Max_n = 605, mod = 1e9 + 7;
int n, K, m, ans;
int to[Max_n], s[Max_n];
int f[Max_n][Max_n], g[Max_n];
int F(int l, int r) {
  if (l > r) return 0;
  return r - l + 1 - s[r] + s[l - 1];
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  n = read() << 1, m = read() << 1, g[0] = 1;
  int u, v;
  for (int i = 1; i <= (m >> 1); i++) {
    u = read(), v = read();
    to[u] = v, to[v] = u, s[u] = s[v] = 1;
  }
  for (int i = 1; i <= n; i++) s[i] += s[i - 1];
  for (int i = 2; i <= n; i += 2) g[i] = 1ll * (i - 1) * g[i - 2] % mod;
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      if ((j - i) & 1) {
        bool fl = 0;
        for (int k = i; k <= j; k++)
          if (to[k] && (to[k] < i || to[k] > j)) fl = 1;
        if (fl) continue;
        f[i][j] = g[F(i, j)];
        for (int k = i + 1; k < j; k++)
          f[i][j] =
              (f[i][j] - 1ll * f[i][k] * g[F(k + 1, j)] % mod + mod) % mod;
        ans = (ans + 1ll * f[i][j] * g[F(1, i - 1) + F(j + 1, n)] % mod) % mod;
      }
  cout << ans;
}
