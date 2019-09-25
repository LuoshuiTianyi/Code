#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, bei[101][101][101], bek[101][101][101];
double f[101][101][101], g[101][101], k1, k2;
int main() {
  freopen("4274.in", "r", stdin);
  freopen("4274.out", "w", stdout);
  cin >> k1 >> k2 >> n >> m;
  for (int i = 0; i <= 100; i++)
    for (int j = 0; j <= 100; j++)
      g[i][j] = 1000000;
  for (int i = 0; i <= 100; i++)
    for (int j = 0; j <= 100; j++)
      for (int k = 0; k <= 100; k++)
        f[i][j][k] = 1000000;
  g[0][0] = 0, f[0][0][0] = 0;
  for (int i = 1; i <= 100; i++)
    for (int j = 1; j <= i; j++)
      for (int k = j - 1; k < i; k++)
        g[i][j] = min(g[i][j], g[k][j - 1] + k2 * (i - k) * (i - k));
  for (int i = 1; i <= 100; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= m; k++) {
        for (int I = bei[i][j - 1][k]; I < i; I++)
          for (int K = bek[i][j - 1][k]; K < k; K++) {
            double X =
                f[I][j - 1][K] + k1 * (i - I) * (i - I) + g[i - I][k - K];
            if (X < f[i][j][k])
              f[i][j][k] = X, bei[i][j][k] = I, bek[i][j][k] = K;
          }
      }
  printf("%.1lf", f[100][n][m]);
}
