#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, m, S, T, tot, a[101][101], id[101][101], sum,
    dx[5] = {0, 1, -1, 0, 0}, dy[5] = {0, 0, 0, 1, -1}, inf = 1e9, ans;
int head[10003], book[10003], nx[60001], to[60001], w[60001], cnt;
int deep[10003];
queue<int> q;
void add(int u, int v, int W, int d) {
  to[d] = v, w[d] = W, nx[d] = head[u];
  head[u] = d;
}
bool init() {
  for (int i = 1; i <= 10002; i++)
    book[i] = head[i];
  memset(deep, -1, sizeof(deep));
  deep[S] = 1;
  q.push(S);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = head[x]; i; i = nx[i])
      if (w[i] > 0 && deep[to[i]] == -1) {
        deep[to[i]] = deep[x] + 1;
        q.push(to[i]);
      }
  }
  return deep[T] != -1;
}
int dfs(int x, int limit) {
  if (x == T || !limit)
    return limit;
  int flow = 0, fnow;
  for (int i = book[x]; i; i = nx[i]) {
    book[x] = i;
    int p = to[i];
    if (deep[p] == deep[x] + 1 && (fnow = dfs(p, min(limit, w[i])))) {
      flow += fnow, w[i ^ 1] += fnow;
      limit -= fnow, w[i] -= fnow;
      if (!limit)
        break;
    }
  }
  return flow;
}
int main() {
  freopen("2774.in", "r", stdin);
  freopen("2774.out", "w", stdout);
  cin >> n >> m;
  S = 10001, T = 10002, cnt = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      id[i][j] = ++sum;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      tot += a[i][j];
      if ((i + j) & 1) {
        add(S, id[i][j], a[i][j], ++cnt), add(id[i][j], S, 0, ++cnt);
        for (int k = 1; k <= 4; k++) {
          int xx = i + dx[k], yy = j + dy[k];
          int To = id[xx][yy];
          if (xx < 1 || xx > n || yy < 1 || yy > m)
            continue;
          add(id[i][j], To, inf, ++cnt);
          add(To, id[i][j], 0, ++cnt);
        }
      } else
        add(id[i][j], T, a[i][j], ++cnt), add(T, id[i][j], 0, ++cnt);
    }
  while (init())
    ans += dfs(S, inf);
  cout << tot - ans;
}
