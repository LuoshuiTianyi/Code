#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int mod = 998244353;
int n, m, ans, fa[100001][18], head[100001], nx[200001], to[200001];
int now, top, cnt, sum, sumk, num, key[23], U[23], V[23], tree[100001],
    stack[100001], dfn[100001], deep[100001];
int hd2[100001], nx2[100001], to2[100001], g[100001][2], f[100001][2],
    k0[100001][2], k1[100001][2];
bool vis[100001], book[100001];
int find(int x) { return fa[x][0] == x ? x : fa[x][0] = find(fa[x][0]); }
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void addroad(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void build(int x, int pa) {
  deep[x] = deep[pa] + 1, dfn[x] = ++cnt, fa[x][0] = pa;
  for (int i = 1; i <= 17; i++)
    fa[x][i] = fa[fa[x][i - 1]][i - 1];
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != pa)
      build(to[i], x);
}
int getlca(int a, int b) {
  if (deep[a] < deep[b])
    swap(a, b);
  for (int i = 17; i >= 0; i--)
    if (deep[fa[a][i]] >= deep[b])
      a = fa[a][i];
  for (int i = 17; i >= 0; i--)
    if (fa[a][i] != fa[b][i])
      a = fa[a][i], b = fa[b][i];
  return a == b ? a : fa[a][0];
}
void link(int a, int b) {
  if (!book[a])
    tree[++num] = a;
  if (!book[b])
    tree[++num] = b;
  book[a] = book[b] = true, cnt++;
  to2[cnt] = b, nx2[cnt] = hd2[a];
  hd2[a] = cnt;
}
void Insert(int x) {
  int lca = getlca(stack[top], x);
  while (top > 1 && dfn[stack[top - 1]] >= dfn[lca])
    link(stack[--top], stack[top]);
  if (lca != stack[top])
    link(lca, stack[top]), stack[top] = lca;
  stack[++top] = x;
}
void work(int x, int y) {
  f[x][0] = f[x][1] = vis[x] = 1;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x][0] && to[i] != y && !vis[to[i]]) {
      work(to[i], y);
      f[x][0] = 1ll * f[x][0] * (f[to[i]][0] + f[to[i]][1]) % mod;
      f[x][1] = 1ll * f[x][1] * f[to[i]][0] % mod;
    }
}
void getk(int x, int y) {
  vis[x] = k0[x][0] = k1[x][1] = 1;
  for (int i = x; fa[i][0] != y; i = fa[i][0]) {
    int Fa = fa[i][0];
    work(Fa, i);
    int t0 = k0[x][0], t1 = k1[x][0];
    k0[x][0] = 1ll * f[Fa][0] * (t0 + k0[x][1]) % mod;
    k1[x][0] = 1ll * f[Fa][0] * (t1 + k1[x][1]) % mod;
    k0[x][1] = 1ll * f[Fa][1] * t0 % mod;
    k1[x][1] = 1ll * f[Fa][1] * t1 % mod;
  }
}
void Count(int x) {
  for (int i = hd2[x]; i; i = nx2[i])
    Count(to2[i]), getk(to2[i], x);
  f[x][0] = f[x][1] = 1;
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]] && to[i] != fa[x][0]) {
      work(to[i], 0);
      f[x][0] = 1ll * f[x][0] * (f[to[i]][0] + f[to[i]][1]) % mod;
      f[x][1] = 1ll * f[x][1] * f[to[i]][0] % mod;
    }
}
void DP(int x) {
  for (int i = hd2[x]; i; i = nx2[i]) {
    int p = to2[i];
    DP(p);
    int f0 = (1ll * k0[p][0] * g[p][0] + 1ll * k1[p][0] * g[p][1] % mod) % mod;
    int f1 = (1ll * k0[p][1] * g[p][0] + 1ll * k1[p][1] * g[p][1] % mod) % mod;
    g[x][0] = 1ll * g[x][0] * (f0 + f1) % mod,
    g[x][1] = 1ll * g[x][1] * f0 % mod;
  }
}
int main() {
  freopen("4426.in", "r", stdin);
  freopen("4426.out", "w", stdout);
  cin >> n >> m;
  int u, v;
  for (int i = 1; i <= n; i++)
    fa[i][0] = i;
  vis[1] = true;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    if (find(u) == find(v)) {
      sum++;
      U[sum] = u;
      if (!vis[u])
        key[++sumk] = u;
      V[sum] = v;
      if (!vis[v])
        key[++sumk] = v;
      vis[u] = vis[v] = true;
    } else {
      addroad(u, v, ++cnt), addroad(v, u, ++cnt);
      fa[find(v)][0] = fa[u][0];
    }
  }
  build(1, 0);
  sort(key + 1, key + sumk + 1, cmp);
  cnt = 0, stack[top = 1] = 1;
  for (int i = 1; i <= n; i++)
    vis[i] = 0;
  for (int i = 1; i <= sumk; i++)
    Insert(key[i]);
  while (top > 0)
    link(stack[--top], stack[top]);
  Count(1);
  for (int S = 0; S < (1 << sum); S++) {
    for (int i = 1; i <= num; i++)
      g[tree[i]][0] = f[tree[i]][0], g[tree[i]][1] = f[tree[i]][1];
    for (int i = 1; i <= sum; i++)
      if (S & (1 << (i - 1)))
        g[U[i]][0] = 0, g[V[i]][1] = 0;
      else
        g[U[i]][1] = 0;
    DP(1);
    ans = (ans + (g[1][0] + g[1][1]) % mod) % mod;
  }
  cout << ans;
}
