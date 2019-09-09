#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int a, b, c, head[100001], to[200001], nx[200001], w[200001], u[100001];
long long ans, H, dis[100001];
void add(int u, int v, int W, int d) {
  w[d] = W, nx[d] = head[u], to[d] = v;
  head[u] = d;
}
queue<int> q;
void SPFA() {
  q.push(1);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    u[x] = 0;
    for (int i = head[x]; i; i = nx[i])
      if (dis[to[i]] > dis[x] + w[i]) {
        dis[to[i]] = dis[x] + w[i];
        if (!u[to[i]]) {
          q.push(to[i]);
          u[to[i]] = 1;
        }
      }
  }
}
int main() {
  freopen("3403.in", "r", stdin);
  freopen("3403.out", "w", stdout);
  cin >> H >> a >> b >> c;
  for (int i = 0; i < c; i++) {
    dis[i] = 2e18;
    add(i, (i + a) % c, a, i + 1);
    add(i, (i + b) % c, b, i + c + 1);
  }
  dis[1] = 1;
  SPFA();
  for (int i = 0; i < c; i++)
    if (dis[i] <= H)
      ans += (H - dis[i]) / (long long)c + 1;
  cout << ans;
}
