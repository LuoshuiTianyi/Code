#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
const int inf = 1e7;
int n, m, K, e, D, f[101];
int cntr, head[21], to[10001], nx[10001], w[10001], dis[21];
int Min[101][101];
bool vis[21], u[21];
struct Que {
  int x, l, r;
} k[10001];
bool cmp(Que a, Que b) { return a.l < b.l ? a.l < b.l : a.r < b.r; }
queue<int> q;
void addr(int u, int v, int W) {
  cntr++;
  to[cntr] = v, nx[cntr] = head[u], w[cntr] = W;
  head[u] = cntr;
}
void SPFA() {
  for (int i = 1; i <= m; i++)
    dis[i] = inf;
  dis[1] = 0;
  q.push(1);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    u[x] = 0;
    for (int i = head[x]; i; i = nx[i]) {
      int p = to[i];
      if (vis[p] && dis[p] > dis[x] + w[i]) {
        dis[p] = dis[x] + w[i];
        if (!u[i])
          q.push(p), u[p] = 1;
      }
    }
  }
}
int main() {
  freopen("1772.in", "r", stdin);
  freopen("1772.out", "w", stdout);
  read(n), read(m), read(K), read(e);
  int u, v, W;
  for (int i = 1; i <= e; i++) {
    read(u), read(v), read(W);
    addr(u, v, W), addr(v, u, W);
  }
  read(D);
  for (int i = 1; i <= D; i++)
    read(k[i].x), read(k[i].l), read(k[i].r);
  sort(k + 1, k + D + 1, cmp);
  for (int l = 0; l <= n; l++) {
    for (int i = 1; i <= m; i++)
      vis[i] = true;
    int pos = 1;
    while (k[pos].l < l && pos <= D)
      if (k[pos++].r >= l)
        vis[k[pos - 1].x] = false;
    for (int r = l; r <= n; r++) {
      while (k[pos].l <= r && pos <= D)
        vis[k[pos++].x] = false;
      SPFA();
      Min[l][r] = dis[m];
    }
  }
  for (int i = 1; i <= n; i++) {
    f[i] = Min[0][i] * i;
    for (int j = 1; j < i; j++)
      f[i] = min(f[i], f[j] + Min[j + 1][i] * (i - j) + K);
  }
  cout << f[n];
}
