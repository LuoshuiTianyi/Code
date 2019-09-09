#include <cstdio>
#include <iostream>
using namespace std;
int n, m, top, fa[1001], w[1001], v[1001], head[1001], nx[1001], to[1001],
    stack[101], f[1001][501], belong[1001];
bool vis[101];
void dfs(int x) {
  if (vis[x]) {
    fa[x] = 0;
    int nn = top;
    while (stack[nn] != x) {
      int now = stack[nn];
      w[x] += w[now], v[x] += v[now], belong[now] = x;
      nn--;
    }
    return;
  }
  stack[++top] = x, vis[x] = true;
  if (fa[x])
    dfs(fa[x]);
  top--, vis[x] = false;
}
void add(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void dp(int x) {
  for (int i = w[x]; i <= m; i++)
    f[x][i] = v[x];
  for (int i = head[x]; i; i = nx[i]) {
    dp(to[i]);
    for (int k = m; k >= w[x]; k--)
      for (int j = 0; j <= k - w[x]; j++)
        f[x][k] = max(f[x][k], f[x][k - j] + f[to[i]][j]);
  }
}
int main() {
  freopen("2515.in", "r", stdin);
  freopen("2515.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    scanf("%d", &w[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &v[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &fa[i]);
  for (int i = 1; i <= n; i++)
    belong[i] = i;
  for (int i = 1; i <= n; i++)
    if (belong[i] == i)
      dfs(i);
  for (int i = 1; i <= n; i++) {
    if (belong[i] != i)
      continue;
    if (!fa[i])
      add(0, i, i);
    else
      add(belong[fa[i]], i, i);
  }
  dp(0);
  cout << f[0][m];
}
