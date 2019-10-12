#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, sum, top, cnt, Que[250001], t[250001], stack[250001], head[250001],
    nx[500001], to[500001];
int dfn[250001], deep[250001], fa[250001][19];
long long minn[250001], w[500001];
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void check(int x) {
  if (t[x] != m)
    head[x] = 0, t[x] = m;
}
void addroad(int u, int v, long long W, int d) {
  check(u), check(v);
  nx[d] = head[u], to[d] = v, w[d] = W;
  head[u] = d;
}
void build(int x, int pa) {
  t[x] = -1, dfn[x] = ++dfn[0], fa[x][0] = pa, deep[x] = deep[pa] + 1;
  for (int i = 1; i <= 18; i++)
    fa[x][i] = fa[fa[x][i - 1]][i - 1];
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != pa)
      minn[to[i]] = min(w[i], minn[x]), build(to[i], x);
}
int getlca(int a, int b) {
  if (deep[a] < deep[b])
    swap(a, b);
  for (int i = 18; i >= 0; i--)
    if (deep[fa[a][i]] >= deep[b])
      a = fa[a][i];
  for (int i = 18; i >= 0; i--)
    if (fa[a][i] != fa[b][i])
      a = fa[a][i], b = fa[b][i];
  return a == b ? a : fa[a][0];
}
void link(int a, int b) {
  int W;
  addroad(a, b, W, ++cnt);
}
void Insert(int x) {
  if (top == 1) {
    stack[++top] = x;
    return;
  }
  int lca = getlca(x, stack[top]);
  if (lca == stack[top])
    return;
  while (top > 1 && dfn[stack[top - 1]] >= dfn[lca])
    link(stack[--top], stack[top]);
  if (stack[top] != lca)
    link(lca, stack[top]), stack[top] = lca;
  stack[++top] = x;
}
long long DP(int x) {
  long long now = !head[x] ? 1e18 : 0;
  for (int i = head[x]; i; i = nx[i])
    now += DP(to[i]);
  return min(now, minn[x]);
}
int main() {
  freopen("2495.in", "r", stdin);
  freopen("2495.out", "w", stdout);
  cin >> n;
  int u, v;
  long long W;
  for (int i = 1; i < n; i++) {
    scanf("%d%d%lld", &u, &v, &W);
    addroad(u, v, W, i), addroad(v, u, W, i + n);
  }
  minn[1] = 1e18;
  build(1, 0);
  cin >> m;
  while (m--) {
    cnt = 0;
    scanf("%d", &sum);
    for (int i = 1; i <= sum; i++)
      scanf("%d", &Que[i]);
    sort(Que + 1, Que + sum + 1, cmp);
    stack[top = 1] = 1;
    for (int i = 1; i <= sum; i++)
      Insert(Que[i]);
    while (top > 1)
      link(stack[--top], stack[top]);
    printf("%lld\n", DP(1));
  }
}
