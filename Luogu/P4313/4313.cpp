#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 105, Max_m = 1e6 + 5, inf = 1e7;
int n, m, ans;
int cntr = 1, hd[Max_m], nx[Max_m], to[Max_m], w[Max_m];
int S, T, cur[Max_m], dep[Max_m], flow[Max_m], fnow[Max_m];
int id(int x, int y) { return (x - 1) * m + y; }
void addr(int u, int v, int W) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
  hd[u] = cntr;
}
queue<int> q;
bool build() {
  for (int i = 0; i <= T; i++) cur[i] = hd[i], dep[i] = -1, fnow[i] = 0;
  q.push(S), dep[S] = 0, fnow[S] = inf;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    go(x, i, v) if (dep[v] == -1 && w[i]) dep[v] = dep[x] + 1, q.push(v);
  }
  return dep[T] != -1;
}
void dfs(int x) {
  if (x == T) {
    flow[x] = fnow[x], ans -= flow[x];
    return;
  }
  for (int i = cur[x], v = to[i]; i; v = to[i = nx[i]]) {
    cur[x] = i;
    if (dep[v] == dep[x] + 1 && w[i]) {
      fnow[v] = min(fnow[x], w[i]), dfs(v);
      w[i] -= flow[v], fnow[x] -= flow[v];
      w[i ^ 1] += flow[v], flow[x] += flow[v];
      flow[v] = 0;
    }
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("4313.in", "r", stdin);
  freopen("4313.out", "w", stdout);
#endif
  n = read(), m = read();
  int x;
  S = 0, T = n * m * 3 + 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      ans += (x = read()), addr(S, id(i, j), x), addr(id(i, j), S, 0);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      ans += (x = read()), addr(id(i, j), T, x), addr(T, id(i, j), 0);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      int t = id(i, j) + n * m;
      ans += (x = read()), addr(S, t, x), addr(t, S, 0);
      addr(t, id(i, j), inf), addr(id(i, j), t, 0);
      if (i > 1) addr(t, id(i - 1, j), inf), addr(id(i - 1, j), t, 0);
      if (i < n) addr(t, id(i + 1, j), inf), addr(id(i + 1, j), t, 0);
      if (j < m) addr(t, id(i, j + 1), inf), addr(id(i, j + 1), t, 0);
      if (j > 1) addr(t, id(i, j - 1), inf), addr(id(i, j - 1), t, 0);
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      int t = id(i, j) + 2 * n * m;
      ans += (x = read()), addr(t, T, x), addr(T, t, 0);
      addr(t, id(i, j), 0), addr(id(i, j), t, inf);
      if (i > 1) addr(t, id(i - 1, j), 0), addr(id(i - 1, j), t, inf);
      if (i < n) addr(t, id(i + 1, j), 0), addr(id(i + 1, j), t, inf);
      if (j < m) addr(t, id(i, j + 1), 0), addr(id(i, j + 1), t, inf);
      if (j > 1) addr(t, id(i, j - 1), 0), addr(id(i, j - 1), t, inf);
    }
  while (build()) dfs(S);
  cout << ans;
}
