#include <cstdio>
#include <iostream>
using namespace std;
int dis[13], n, m, G[13][13], limit, f[8192], inf = 1e9 + 7, ans = 1e9;
void dfs(int x) {
  for (int i = 1; i <= n; i++)
    if ((1 << (i - 1)) & x)
      for (int j = 1; j <= n; j++)
        if (((1 << (j - 1)) & x) == 0 && G[i][j] != inf)
          if (dis[i] * G[i][j] + f[x] < f[(x | (1 << (j - 1)))]) {
            f[x | (1 << (j - 1))] = dis[i] * G[i][j] + f[x];
            int t = dis[j];
            dis[j] = dis[i] + 1;
            dfs(x | (1 << (j - 1)));
            dis[j] = t;
          }
}
int main() {
  freopen("3959.in", "r", stdin);
  freopen("3959.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      G[i][j] = inf;
  limit = (1 << n);
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    G[v][u] = G[u][v] = min(G[u][v], min(G[v][u], w));
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      dis[j] = inf;
    for (int j = 0; j < limit; j++)
      f[j] = inf;
    f[(1 << (i - 1))] = 0;
    dis[i] = 1;
    dfs(1 << (i - 1));
    ans = min(ans, f[limit - 1]);
  }
  cout << ans;
}
