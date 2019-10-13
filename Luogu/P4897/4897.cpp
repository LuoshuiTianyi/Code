#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
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
const int Max_n = 505, Max_m = 1e4 + 5;
int n, m;
int node[Max_n], tp1[Max_n], tp2[Max_n];
int f[10][Max_n], Min[10][Max_n];
bool vis[Max_n];
struct graph {
  int hd[Max_n];
  int cntr = 1, nx[Max_m], to[Max_m], w[Max_m];
  void addr(int u, int v, int W) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G, Gf, G2;
namespace FLOW {
int S, T;
int cur[Max_n], dep[Max_n], fnow[Max_n], flow[Max_n], ans;
void init(graph &G) {
  for (int i = 0; i <= n; i++) cur[i] = G.hd[i], dep[i] = -1, fnow[i] = 0;
}
queue<int> q;
bool build(graph &G) {
  init(G);
  q.push(S), dep[S] = 0, fnow[S] = 1e9;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    go(G, x, i, v) {
      if (dep[v] == -1 && G.w[i] && vis[v]) {
        dep[v] = dep[x] + 1, q.push(v);
      }
    }
  }
  return dep[T] != -1;
}
void dfs(graph &G, int x) {
  if (x == T) {
    flow[x] = fnow[x], ans += flow[x];
    return;
  }
  for (int i = cur[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
    if (dep[v] == dep[x] + 1 && G.w[i] && vis[v]) {
      fnow[v] = min(fnow[x], G.w[i]), dfs(G, v);
      fnow[x] -= flow[v], G.w[i] -= flow[v];
      flow[x] += flow[v], G.w[i ^ 1] += flow[v];
      flow[v] = 0;
    }
}
int Dinic(graph &G, int s, int t) {
  S = s, T = t, ans = 0;
  while (build(G)) dfs(G, S);
  return ans;
}
}  // namespace FLOW
void Solve(int l, int r) {
  if (l == r) return;
  cout << node[l] << " " << node[r] << endl;
  Gf = G;
  for (int i = l; i <= r; i++) vis[node[i]] = 1;
  int W = FLOW::Dinic(Gf, node[l], node[r]);
  G2.addr(node[l], node[r], W), G2.addr(node[r], node[l], W);
  for (int i = l; i <= r; i++) vis[node[i]] = 0;
  int top1 = 0, top2 = 0;
  for (int i = l; i <= r; i++)
    if (FLOW::dep[node[i]] != -1)
      tp1[++top1] = node[i];
    else
      tp2[++top2] = node[i];
  for (int i = 1; i <= top1; i++) node[l + i - 1] = tp1[i];
  for (int i = 1; i <= top2; i++) node[l + top1 + i - 1] = tp2[i];
  Solve(l, l + top1 - 1), Solve(l + top1, r);
}
void build(int x, int fa) {
  go(G2, x, i, v) if (v != fa) {
    cout << x << " " << v << " " << G.w[i] << endl;
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("4897.in", "r", stdin);
  freopen("4897.out", "w", stdout);
#endif
  n = read(), m = read();
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    u = read(), v = read(), w = read();
    G.addr(u, v, w), G.addr(v, u, w);
  }
  for (int i = 0; i <= n; i++) node[i] = i;
  Solve(0, n);
  build(0, -1);
}
