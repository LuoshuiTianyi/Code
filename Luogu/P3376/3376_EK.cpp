#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int n, m, S, T, head[10002], nx[200004], to[200004], w[200004];
int pre[10002], flow[10002], ans, cnt;
void add(int u, int v, int W, int d) {
  nx[d] = head[u], to[d] = v, w[d] = W;
  head[u] = d;
}
queue<int> q;
void increase() {
  q.push(S);
  for (int i = 1; i <= n; i++)
    if (i != S)
      pre[i] = -1;
  flow[S] = 1e9;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = head[x]; i; i = nx[i]) {
      int p = to[i];
      if (pre[p] == -1 && w[i] > 0) {
        pre[p] = i;
        flow[p] = min(flow[x], w[i]);
        q.push(to[i]);
      }
    }
  }
}
int main() {
  freopen("3376.in", "r", stdin);
  freopen("3376.out", "w", stdout);
  cin >> n >> m >> S >> T;
  int u, v, W;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &W);
    add(u, v, W, (i << 1) ^ 1);
    add(v, u, 0, (i << 1));
  }
  while (1) {
    increase();
    if (pre[T] != -1) {
      ans += flow[T];
      int p = pre[T];
      while (p) {
        w[p ^ 1] += flow[T];
        w[p] -= flow[T];
        p = pre[to[p ^ 1]];
      }
    } else
      break;
  }
  cout << ans;
}
