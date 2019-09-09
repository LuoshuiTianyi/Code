#include <cstdio>
#include <iostream>
using namespace std;
int n, start, a[51], f[51][51][2], q[51], Inf = 2e9, s[51][51], s2[51][51],
                                          sum[51][51], total;
int main() {
  freopen("1220.in", "r", stdin);
  freopen("1220.out", "w", stdout);
  cin >> n >> start;
  for (int i = 1; i <= n; i++) {
    cin >> q[i] >> a[i];
    total += a[i];
  }
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      s[i][j] = s[i][j - 1] + (q[j] - q[i]) * a[j];
  for (int i = n; i >= 1; i--)
    for (int j = i; j >= 1; j--)
      s2[j][i] = s2[j + 1][i] + (q[i] - q[j]) * a[j];
  for (int i = 1; i <= n; i++)
    sum[i][i] = total - a[i];
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
      sum[i][j] = sum[i][j - 1] - a[j];
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      f[i][j][0] = f[i][j][1] = Inf;
  f[start][start][0] = f[start][start][1] = 0;
  for (int l = 1; l <= n; l++)
    for (int i = start; i >= 1; i--)
      for (int j = start; j <= n; j++) {
        for (int k = i - 1; k >= 1; k--) {
          f[k][j][0] = min(f[k][j][0],
                           f[i][j][0] + s2[k][i] + (q[i] - q[k]) * sum[k][j]);
          f[k][j][0] =
              min(f[k][j][0], f[i][j][1] + (q[j] - q[i]) * (sum[i][j]) +
                                  s2[k][i] + (q[i] - q[k]) * sum[k][j]);
        }
        for (int k = j + 1; k <= n; k++) {
          f[i][k][1] =
              min(f[i][k][1], f[i][j][1] + (q[k] - q[j]) * sum[i][k] + s[j][k]);
          f[i][k][1] =
              min(f[i][k][1], f[i][j][0] + (q[j] - q[i]) * (sum[i][j]) +
                                  s[j][k] + (q[k] - q[j]) * sum[j][k]);
        }
        for (int k = 1; k < start; k++) {
          f[k][j][0] = min(f[k][j][0], f[k][j][1] + (q[j] - q[k]) * sum[k][j]);
          f[k][j][1] = min(f[k][j][1], f[k][j][0] + (q[j] - q[k]) * sum[k][j]);
        }
        for (int k = start + 1; k <= n; k++) {
          f[i][k][1] = min(f[i][k][1], f[i][k][0] + (q[k] - q[i]) * sum[i][k]);
          f[i][k][0] = min(f[i][k][0], f[i][k][1] + (q[k] - q[i]) * sum[i][k]);
        }
      }
  cout << min(f[1][n][1], f[1][n][0]);
}
