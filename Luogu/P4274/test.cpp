#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 110
#define INF 1e200

using namespace std;

double f[MAXN][MAXN][MAXN], g[MAXN][MAXN];
double K1, K2;
int m, n;
int lastk[MAXN][MAXN][MAXN],
    lastj
        [MAXN][MAXN]
        [MAXN]; // lastk[k][i][j]=k',lastj[k][i][j]=j'表示f[k][i][j]是从f[k'][i-1][j']转移来的

int main() {
  freopen("4274.in", "r", stdin);
  freopen("test.out", "w", stdout);
  scanf("%lf%lf%d%d", &K1, &K2, &m, &n);
  for (int i = 0; i < MAXN; i++)
    for (int j = 0; j < MAXN; j++)
      g[i][j] = INF;
  for (int i = 0; i < MAXN; i++)
    for (int j = 0; j < MAXN; j++)
      for (int k = 0; k < MAXN; k++)
        f[i][j][k] = INF;
  g[0][0] = 0;
  for (int i = 1; i <= 100; i++)
    for (int j = 1; j <= i; j++)
      for (int k = j - 1; k < i; k++)
        g[i][j] = min(g[i][j], g[k][j - 1] + (i - k) * (i - k) * K2);
  f[0][0][0] = 0;
  for (int k = 1; k <= 100; k++)
    for (int i = 1; i <= m; i++)
      for (int j = 1; j <= n; j++) {
        for (int lk = lastk[k][i - 1][j]; lk < k; lk++)
          for (int lj = lastj[k][i - 1][j]; lj < j; lj++) {
            if (f[lk][i - 1][lj] + (k - lk) * (k - lk) * K1 +
                    g[k - lk][j - lj] <
                f[k][i][j]) {
              f[k][i][j] = f[lk][i - 1][lj] + (k - lk) * (k - lk) * K1 +
                           g[k - lk][j - lj];
              lastk[k][i][j] = lk;
              lastj[k][i][j] = lj;
            }
          }
      }
  printf("%.1lf\n", f[100][m][n]);
  return 0;
}
