#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;
const int MAXN = 505;
int n, m, cnt, w[MAXN], a[MAXN], d[MAXN];
int dfn[MAXN], low[MAXN], bel[MAXN], tot, scc, ins[MAXN], sta[MAXN], top;
int W[MAXN], V[MAXN], indeg[MAXN], dp[MAXN][MAXN];
struct edge {
  int v;
  edge *next;
} pool[MAXN * 2], *head[MAXN];
inline void addedge(int u, int v) {
  edge *p = &pool[++cnt];
  p->v = v, p->next = head[u], head[u] = p;
}
void tarjan(int u) {
  dfn[u] = low[u] = ++tot;
  sta[++top] = u;
  ins[u] = 1;
  for (edge *p = head[u]; p; p = p->next) {
    int v = p->v;
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (ins[v])
      low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    ++scc;
    while (sta[top + 1] != u) {
      bel[sta[top]] = scc;
      W[scc] += w[sta[top]];
      V[scc] += a[sta[top]];
      ins[sta[top--]] = 0;
    }
  }
}
void solve(int u) {
  for (int i = W[u]; i <= m; i++)
    dp[u][i] = V[u];
  for (edge *p = head[u]; p; p = p->next) {
    int v = p->v;
    solve(v);
    int k = m - W[u];
    for (int i = k; i >= 0; i--)
      for (int j = 0; j <= i; j++)
        dp[u][i + W[u]] = max(dp[u][i + W[u]], dp[v][j] + dp[u][i + W[u] - j]);
  }
}
int main() {
  freopen("2515.in", "r", stdin);
  freopen("test.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &w[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &d[i]);
    if (d[i])
      addedge(d[i], i);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i])
      tarjan(i);
  for (int i = 0; i <= n; i++)
    head[i] = NULL;
  cnt = 0;
  for (int i = 1; i <= n; i++)
    if (bel[d[i]] != bel[i]) {
      addedge(bel[d[i]], bel[i]);
      indeg[bel[i]]++;
    }
  for (int i = 1; i <= scc; i++)
    if (!indeg[i])
      addedge(0, i);
  solve(0);
  // printf("%d\n", dp[0][m]);
  return 0;
}
