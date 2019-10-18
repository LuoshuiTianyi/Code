#include <algorithm>
#include <cmath>
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
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 405;
int n, mod, ans;
int C[Max_n][Max_n];
int to[Max_n][Max_n], f[Max_n][Max_n], g[Max_n][Max_n];
int ksm(int a, int b) {
  int base = 1;
  while (b) {
    if (b & 1) base = 1ll * base * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return base;
}
void Mod(int &x) { x %= mod; }
int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  n = read(), mod = read();
  for (int i = 0; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) Mod(C[i][j] = C[i - 1][j - 1] + C[i - 1][j]);
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; i + j <= n; j++)
      to[i][j] = 1ll * ksm(2, C[j][2]) * ksm(ksm(2, i) - 1 + mod, j) % mod;
  f[0][1] = 1, g[0][1] = n - 1;
  for (int i = 0; i <= n; i++)
    for (int j = 1; i + j <= n; j++)
      for (int k = 1; i + j + k <= n; k++) {
        int To = 1ll * to[j][k] * C[n - i - j][k] % mod;
        Mod(f[i + j][k] += 1ll * f[i][j] * To % mod);
        Mod(g[i + j][k] +=
            (1ll * g[i][j] * To + 1ll * (n - i - j - k) * To % mod * f[i][j]) %
            mod);
      }
  for (int i = 0; i <= n; i++) Mod(ans += g[i][n - i]);
  ans = 1ll * ans * ksm(n - 1, mod - 2) % mod;
  cout << ans;
}
