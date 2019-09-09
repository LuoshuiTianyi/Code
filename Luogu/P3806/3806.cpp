#include <cstdio>
#include <iostream>
using namespace std;
int n, m;
int head[10001], nx[20001], to[20001], w[20001];
int rt, sum, size[10001], maxs[10001];
int dis[10001], num[10001], book[10001], top, cnt;
int que[101];
bool Ans[101], judge[10000001], vis[10001];
void addroad(int u, int v, int W, int d) {
  to[d] = v, nx[d] = head[u], w[d] = W;
  head[u] = d;
}
void getrt(int x, int fa) {
  size[x] = 1, maxs[x] = 0;
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
  num[++top] = dis[x];
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]]) {
      dis[to[i]] = dis[x] + w[i];
      getdis(to[i], x);
    }
}
void Work(int x) {
  cnt = 0;
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]]) {
      top = 0;
      dis[to[i]] = w[i];
      getdis(to[i], x);
      for (int j = 1; j <= top; j++)
        for (int k = 1; k <= m; k++)
          if (que[k] >= num[j])
            Ans[k] |= judge[que[k] - num[j]];
      for (int j = 1; j <= top; j++)
        if (!judge[num[j]])
          judge[num[j]] = true, book[++cnt] = num[j];
    }
  for (int i = 1; i <= cnt; i++)
    judge[book[i]] = false;
}
void solve(int x) {
  vis[x] = judge[0] = 1;
  Work(x);
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]]) {
      sum = size[to[i]], rt = 0;
      getrt(to[i], 0);
      solve(rt);
    }
}
int main() {
  freopen("3806.in", "r", stdin);
  freopen("3806.out", "w", stdout);
  cin >> n >> m;
  int u, v, W;
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &u, &v, &W);
    addroad(u, v, W, i), addroad(v, u, W, i + n);
  }
  for (int i = 1; i <= m; i++)
    scanf("%d", &que[i]);
  maxs[rt] = sum = n;
  getrt(1, 0);
  solve(rt);
  for (int i = 1; i <= m; i++)
    printf(Ans[i] ? "AYE\n" : "NAY\n");
}
