#include <cstdio>
#include <iostream>
using namespace std;
int n, ans;
int head[20001], nx[40001], to[40001], w[40001];
int rt, sum, maxs[20001], size[20001], dis[20001], tag[3];
bool vis[20001];
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
void addroad(int u, int v, int W, int d) {
  nx[d] = head[u], to[d] = v, w[d] = W;
  head[u] = d;
}
void getrt(int x, int fa) {
  maxs[x] = 0, size[x] = 1;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]]) {
      getrt(to[i], x);
      size[x] += size[to[i]];
      maxs[x] = max(maxs[x], size[to[i]]);
    }
  maxs[x] = max(maxs[x], sum - size[x]);
  if (maxs[x] < maxs[rt])
    rt = x;
}
void getdis(int x, int fa) {
  tag[dis[x]]++;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]]) {
      dis[to[i]] = (dis[x] + w[i]) % 3;
      getdis(to[i], x);
    }
}
int work(int x) {
  tag[0] = tag[1] = tag[2] = 0;
  getdis(x, 0);
  return tag[1] * tag[2] * 2 + tag[0] * tag[0];
}
void solve(int x) {
  vis[x] = true;
  dis[x] = 0, ans += work(x);
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]]) {
      dis[to[i]] = w[i] % 3;
      ans -= work(to[i]);
      rt = 0, sum = size[to[i]];
      getrt(to[i], x);
      solve(rt);
    }
}
int main() {
  freopen("2634.in", "r", stdin);
  freopen("2634.out", "w", stdout);
  cin >> n;
  int u, v, W;
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &u, &v, &W);
    addroad(u, v, W, i), addroad(v, u, W, i + n);
  }
  maxs[rt = 0] = sum = n;
  getrt(1, 0);
  solve(rt);
  cout << ans / gcd(ans, n * n) << "/" << n * n / gcd(ans, n * n);
}
