#include <cstdio>
#include <iostream>
using namespace std;
int n, a[300001], head[300001], nx[600001], to[600001], change[300001];
int deep[300001], fa[300001][20], now, size[300001];
void add(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void build(int x) {
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x][0]) {
      fa[to[i]][0] = x;
      deep[to[i]] = deep[x] + 1;
      build(to[i]);
    }
}
void Swap(int &u, int &v) {
  if (deep[u] < deep[v])
    swap(u, v);
}
int LCA(int u, int v) {
  Swap(u, v);
  for (int i = 19; i >= 0; i--)
    if (deep[fa[u][i]] >= deep[v])
      u = fa[u][i];
  for (int i = 19; i >= 0; i--)
    if (fa[u][i] != fa[v][i]) {
      u = fa[u][i];
      v = fa[v][i];
    }
  return u == v ? u : fa[u][0];
}
void Count(int x) {
  size[x] = change[x];
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x][0]) {
      Count(to[i]);
      size[x] += size[to[i]];
    }
}
int main() {
  freopen("3258.in", "r", stdin);
  freopen("3258.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    add(u, v, i);
    add(v, u, i + n);
  }
  deep[1] = 1;
  build(1);
  for (int j = 1; j <= 19; j++)
    for (int i = 1; i <= n; i++)
      fa[i][j] = fa[fa[i][j - 1]][j - 1];
  now = a[1];
  for (int i = 2; i <= n; i++) {
    change[now]++;
    change[a[i]]++;
    int lca = LCA(now, a[i]);
    change[fa[lca][0]]--;
    change[lca]--;
    now = a[i];
  }
  Count(1);
  for (int i = 2; i <= n; i++)
    size[a[i]]--;
  for (int i = 1; i <= n; i++)
    printf("%d\n", size[i]);
}
