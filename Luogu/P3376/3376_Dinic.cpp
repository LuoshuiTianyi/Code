#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, m, S, T;
int head[10001], nx[200005], to[200005], w[200005];
int flow[10001], fnow[10001], deep[10001], ans;
bool book[200005];
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
void addroad(int u, int v, int W, int d) {
  to[d] = v, nx[d] = head[u], w[d] = W;
  head[u] = d;
}
queue<int> q;
bool init() {
  memset(book, 0, sizeof(book));
  memset(fnow, 0, sizeof(fnow));
  fnow[S] = 1e9;
  for (int i = 1; i <= n; i++)
    deep[i] = -1;
  deep[S] = 1;
  q.push(S);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = head[x]; i; i = nx[i]) {
      int p = to[i];
      if (deep[p] == -1 && w[i] > 0)
        deep[p] = deep[x] + 1, q.push(p);
    }
  }
  return deep[T] != -1;
}
void dfs(int x) {
  if (x == T) {
    flow[x] = fnow[x];
    ans += fnow[x];
    return;
  }
  for (int i = head[x]; i; i = nx[i]) {
    int p = to[i];
    if (w[i] > 0 && !book[i] && deep[p] == deep[x] + 1) {
      book[i] = true;
      fnow[p] = min(fnow[x], w[i]);
      dfs(p);
      if (flow[p]) {
        w[i] -= flow[p];
        w[i ^ 1] += flow[p];
        flow[x] += flow[p];
        fnow[x] -= flow[p];
        flow[p] = 0;
      }
    }
  }
}
int main() {
  freopen("3376.in", "r", stdin);
  freopen("3376.out", "w", stdout);
  read(n), read(m), read(S), read(T);
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    read(u), read(v), read(w);
    addroad(u, v, w, (i << 1));
    addroad(v, u, 0, (i << 1) ^ 1);
  }
  while (init())
    dfs(S);
  cout << ans;
}
