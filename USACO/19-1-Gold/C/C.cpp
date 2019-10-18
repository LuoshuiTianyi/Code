#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int n, m, t, num[10001], head[10001], nx[100001], to[100001], w[100001];
int pre[10001], up[10001];
long long size[10001], ans = -2e18;
bool vis[10001];
pair<int, int> dis[10001];
void addroad(int u, int v, int W, int d) {
  w[d] = W, to[d] = v, nx[d] = head[u];
  head[u] = d;
}
priority_queue<pair<int, int>> q;
void SPFA() {
  dis[1].first = 0, q.push(dis[1]);
  while (!q.empty()) {
    pair<int, int> no = q.top();
    int x = no.second;
    q.pop();
    vis[x] = false;
    for (int i = head[x]; i; i = nx[i]) {
      int now = no.first + w[i];
      if (dis[to[i]].first == now)
        pre[to[i]] = min(pre[to[i]], x);
      if (dis[to[i]].first > now) {
        dis[to[i]].first = now, pre[to[i]] = x;
        if (!vis[to[i]])
          vis[to[i]] = true, q.push(dis[to[i]]);
      }
    }
  }
}
void dfs(int x, long long tot) {
  size[x] = num[x];
  for (int i = head[x]; i; i = nx[i]) {
    if (pre[to[i]] == x)
      dfs(to[i], tot + w[i]), size[x] += size[to[i]];
  }
  ans = max(ans, 1ll * (tot - t) * size[x]);
}
int main() {
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
  cin >> n >> m >> t;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &num[i]);
    dis[i].second = i;
    dis[i].first = 1e9;
  }
  int u, v, W;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &W);
    addroad(u, v, W, i), addroad(v, u, W, i + n);
  }
  SPFA();
  dfs(1, 0);
  cout << ans;
}
