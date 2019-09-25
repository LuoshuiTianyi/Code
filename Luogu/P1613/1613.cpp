#include <cstdio>
#include <iostream>
using namespace std;
int n, m, dis[51][51];
bool G[51][51][70];
int main() {
  freopen("1613.in", "r", stdin);
  freopen("1613.out", "w", stdout);
  cin >> n >> m;
  int u, v;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      dis[i][j] = 1e9;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    dis[u][v] = 1;
    G[u][v][0] = true;
  }
  for (int l = 1; l <= 64; l++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        for (int k = 1; k <= n; k++) {
          G[i][j][l] |= (G[i][k][l - 1] & G[k][j][l - 1]);
          if (G[i][j][l])
            dis[i][j] = 1;
        }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= n; k++)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  cout << dis[1][n];
}
