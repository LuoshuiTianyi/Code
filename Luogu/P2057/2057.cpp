#include <cstdio>
#include <cstring>
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
const int Max_n = 305, Max_m = Max_n * Max_n << 1, inf = 1e9;
int n, m, S, T, ans;
int cntr = 1, hd[Max_n], cur[Max_n], nx[Max_m], to[Max_m], w[Max_m];
int dep[Max_n], fnow[Max_n], flow[Max_n];
void addr(int u, int v, int W) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
  hd[u] = cntr;
}
queue<int> q;
bool build() {
  for (int i = 1; i <= n + 2; i++) cur[i] = hd[i], dep[i] = -1, fnow[i] = 0;
  q.push(S), dep[S] = 0, fnow[S] = 1e9;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    go(x, i, v) if (dep[v] == -1 && w[i]) dep[v] = dep[x] + 1, q.push(v);
  }
  return dep[T] != -1;
}
void dfs(int x) {
  if (x == T) {
    flow[x] = fnow[x], ans += flow[x];
    return;
  }
  for (int i = cur[x], v = to[i]; i; v = to[i = nx[i]])
    if (dep[v] == dep[x] + 1 && w[i]) {
      cur[x] = i, fnow[v] = min(fnow[x], w[i]), dfs(v);
      w[i] -= flow[v], fnow[x] -= flow[v];
      w[i ^ 1] += flow[v], flow[x] += flow[v];
      flow[v] = 0;
    }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("2057.in", "r", stdin);
  freopen("2057.out", "w", stdout);
#endif
  n = read(), m = read(), S = n + 1, T = n + 2;
  for (int i = 1; i <= n; i++)
    if (!read())
      addr(S, i, 1), addr(i, S, 0);
    else
      addr(i, T, 1), addr(T, i, 0);
  int u, v;
  while (m--) {
    u = read(), v = read();
    addr(u, v, 1), addr(v, u, 0);
    addr(u, v, 0), addr(v, u, 1);
  }
  while (build()) dfs(S);
  cout << ans;
}
