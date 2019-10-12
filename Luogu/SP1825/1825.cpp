#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, K, ans = 0;
int head[200001], nx[400001], to[400001], w[400001];
int sum, rt, maxs[200001], sizeb[200001], size[200001], dis[200001],
    maxf[200001], Son[200001], To[200001], top, limit;
bool black[200001], vis[200001];
void add(int u, int v, int W, int d) {
  to[d] = v, w[d] = W, nx[d] = head[u];
  head[u] = d;
}
void getrt(int x, int fa) {
  size[x] = 1, maxs[x] = 0, sizeb[x] = black[x];
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]] && to[i] != fa) {
      getrt(to[i], x);
      size[x] += size[to[i]];
      sizeb[x] += sizeb[to[i]];
      maxs[x] = max(maxs[x], size[to[i]]);
    }
  maxs[x] = max(maxs[x], sum - size[x]);
  if (maxs[x] < maxs[rt])
    rt = x;
}
bool cmp(int a, int b) { return sizeb[a] < sizeb[b]; }
void getdis(int x, int fa, int now, int tot) {
  now += black[x];
  if (now > K)
    return;
  dis[now] = max(dis[now], tot);
  limit = max(limit, now);
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]])
      getdis(to[i], x, now, tot + w[i]);
}
void work(int x) {
  top = 0;
  for (int i = 0; i <= limit; i++)
    maxf[i] = -1e9;
  getrt(x, 0);
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]])
      Son[++top] = to[i], To[to[i]] = w[i];
  sort(Son + 1, Son + top + 1, cmp);
  K -= black[x];
  for (int i = 1; i <= top; i++) {
    int tmp = limit;
    limit = 0;
    getdis(Son[i], x, 0, To[Son[i]]);
    for (int j = 0; j <= limit; j++)
      ans = max(ans, max(dis[j] + maxf[min(tmp, K - j)], dis[j]));
    for (int j = 0; j <= limit; j++) {
      maxf[j] = max(maxf[j], dis[j]);
      dis[j] = -1e9;
    }
    for (int j = 1; j <= limit; j++)
      maxf[j] = max(maxf[j], maxf[j - 1]);
  }
  K += black[x];
}
void solve(int x) {
  vis[x] = true;
  work(x);
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]]) {
      rt = 0, sum = size[to[i]];
      getrt(to[i], x);
      solve(rt);
    }
}
int main() {
  freopen("1825.in", "r", stdin);
  freopen("1825.out", "w", stdout);
  cin >> n >> K >> m;
  int x;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &x);
    black[x] = true;
  }
  int u, v, W;
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &u, &v, &W);
    add(u, v, W, i);
    add(v, u, W, i + n);
  }
  maxs[rt] = sum = n;
  getrt(1, 0);
  solve(rt);
  cout << ans;
}
