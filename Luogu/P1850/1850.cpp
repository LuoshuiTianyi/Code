#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, v, e, c[2001], d[2001];
double odd[2001], f[2001][2001][2], dis[301][301], inf = 1e18;
int main() {
  freopen("1850.in", "r", stdin);
  freopen("1850.out", "w", stdout);
  cin >> n >> m >> v >> e;
  for (int i = 1; i <= n; i++)
    cin >> c[i];
  for (int i = 1; i <= n; i++)
    cin >> d[i];
  for (int i = 1; i <= n; i++)
    cin >> odd[i];
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      f[i][j][1] = f[i][j][0] = inf;
  for (int i = 1; i <= v; i++)
    for (int j = 1; j <= v; j++)
      if (i != j)
        dis[i][j] = inf;
  for (int i = 1; i <= e; i++) {
    int u, v;
    double w;
    cin >> u >> v >> w;
    dis[u][v] = dis[v][u] = min(dis[u][v], w);
  }
  for (int k = 1; k <= v; k++)
    for (int i = 1; i <= v; i++)
      for (int j = 1; j <= v; j++)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  f[1][0][0] = f[1][1][1] = 0;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j <= min(i, m); j++) {
      if (j)
        f[i][j][1] =
            min(f[i - 1][j - 1][0] + odd[i] * dis[c[i - 1]][d[i]] +
                    (1 - odd[i]) * dis[c[i - 1]][c[i]],
                f[i - 1][j - 1][1] + odd[i] * odd[i - 1] * dis[d[i - 1]][d[i]] +
                    (1 - odd[i]) * odd[i - 1] * dis[d[i - 1]][c[i]] +
                    odd[i] * (1 - odd[i - 1]) * dis[c[i - 1]][d[i]] +
                    (1 - odd[i]) * (1 - odd[i - 1]) * dis[c[i - 1]][c[i]]);
      f[i][j][0] = min(f[i - 1][j][0] + dis[c[i - 1]][c[i]],
                       f[i - 1][j][1] + odd[i - 1] * dis[d[i - 1]][c[i]] +
                           (1 - odd[i - 1]) * dis[c[i - 1]][c[i]]);
    }
  }
  double ans = inf;
  for (int i = 0; i <= m; i++)
    ans = min(ans, min(f[n][i][1], f[n][i][0]));
  printf("%.2lf", ans);
}
