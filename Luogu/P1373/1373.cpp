#include <cstdio>
#include <iostream>
using namespace std;
int n, m, K, a[801][801], f[801][801][17][2], mod = 1e9 + 7, ans;
void Mod(int &x) { x %= mod; }
int main() {
  freopen("1373.in", "r", stdin);
  freopen("1373.out", "w", stdout);
  cin >> n >> m >> K;
  K++;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      f[i][j][a[i][j] % K][0] = 1;
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      for (int k = 0; k <= K; k++) {
        Mod(f[i][j][k][0] += f[i][j - 1][(k - a[i][j] + K) % K][1]);
        Mod(f[i][j][k][0] += f[i - 1][j][(k - a[i][j] + K) % K][1]);
        Mod(f[i][j][k][1] += f[i][j - 1][(k + a[i][j]) % K][0]);
        Mod(f[i][j][k][1] += f[i - 1][j][(k + a[i][j]) % K][0]);
      }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      Mod(ans += f[i][j][0][1]);
  cout << ans;
}
