#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int T, n, m, mod, K, head[100001], head2[100001], f[100001][51], dis[100001],
    in[100001][51];
struct edge {
  int next, to, w;
} road[400001];
queue<int> q;
void SPFA() {
  dis[n] = 0;
  int u[100001] = {0};
  q.push(n);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = head2[x]; i; i = road[i].next) {
      int p = road[i].to;
      if (dis[p] > dis[x] + road[i].w) {
        dis[p] = dis[x] + road[i].w;
        if (!u[p]) {
          u[p] = 1;
          q.push(p);
        }
      }
    }
    u[x] = 0;
  }
}
int dfs(int u, int k) {
  if (in[u][k])
    return -1;
  if (f[u][k])
    return f[u][k];
  in[u][k] = 1;
  f[u][k] = u == n ? 1 : 0;
  for (int i = head[u], w, v, sc; i; i = road[i].next)
    if ((sc = dis[v = road[i].to] - dis[u] + road[i].w) <= k) {
      if ((w = dfs(v, k - sc)) == -1)
        return f[u][k] = -1;
      f[u][k] = (f[u][k] + w) % mod;
    }
  return in[u][k] = 0, f[u][k];
}
void add(int u, int v, int w, int d) {
  road[d].to = v;
  road[d].w = w;
  road[d].next = head[u];
  head[u] = d;
}
void add2(int u, int v, int w, int d) {
  road[d].to = v;
  road[d].w = w;
  road[d].next = head2[u];
  head2[u] = d;
}
int main() {
  freopen("3953.in", "r", stdin);
  freopen("3953.out", "w", stdout);
  cin >> T;
  for (int pl = 1; pl <= T; pl++) {
    memset(head, 0, sizeof(head));
    memset(head2, 0, sizeof(head2));
    memset(f, 0, sizeof(f));
    memset(dis, 9, sizeof(dis));
    memset(in, 0, sizeof(in));
    cin >> n >> m >> K >> mod;
    int u, v, w;
    for (int i = 1; i <= m; i++) {
      cin >> u >> v >> w;
      add(u, v, w, i);
      add2(v, u, w, i + m);
    }
    SPFA();
    cout << dfs(1, K) << endl;
  }
}
