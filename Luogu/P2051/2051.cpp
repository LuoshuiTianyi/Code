#include <cstdio>
#include <iostream>
using namespace std;
int mod = 9999973, n, m, ans;
int f[101][101][101];
void Mod(int &x) { x %= mod; }
int And(int x) { return x * (x - 1) / 2; }
int main() {
  freopen("2051.in", "r", stdin);
  freopen("2051.out", "w", stdout);
  cin >> n >> m;
  f[0][0][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= m; j++)
      for (int k = 0; k <= m - j; k++)
        if (f[i - 1][j][k]) {
          int x = f[i - 1][j][k], rest = m - j - k;
          Mod(f[i][j][k] += x);
          if (rest > 0)
            Mod(f[i][j + 1][k] += 1ll * rest * x % mod);
          if (rest > 1)
            Mod(f[i][j + 2][k] += 1ll * And(rest) * x % mod);
          if (j > 0)
            Mod(f[i][j - 1][k + 1] += 1ll * j * x % mod);
          if (rest > 0 && j > 0)
            Mod(f[i][j][k + 1] += 1ll * j * rest * x % mod);
          if (j > 1)
            Mod(f[i][j - 2][k + 2] += 1ll * And(j) * x % mod);
        }
  for (int i = 0; i <= m; i++)
    for (int j = 0; j <= m - i; j++)
      Mod(ans += f[n][i][j]);
  cout << ans;
}
