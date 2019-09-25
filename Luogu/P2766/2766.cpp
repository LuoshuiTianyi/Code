#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, a[501], f[501], inf = 1e9;
int cnt, S, T, maxx, head[503], nx[250001], to[250001], w[250001], book[503],
    ans;
int deep[503];
void add(int u, int v, int W, int d) {
  to[d] = v, nx[d] = head[u], w[d] = W;
  head[u] = d;
}
queue<int> q;
bool init() {
  memset(deep, -1, sizeof(deep));
  for (int i = 1; i <= 502; i++)
    book[i] = head[i];
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
  freopen("2766.in", "r", stdin);
  freopen("2766.out", "w", stdout);
  cin >> n;
  S = 501, T = 502, cnt = 1;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++) {
    f[i] = 1;
    for (int j = 1; j < i; j++)
      if (a[j] <= a[i])
        f[i] = max(f[i], f[j] + 1);
    maxx = max(maxx, f[i]);
  }
  cout << maxx << endl;
  for (int i = 1; i <= n; i++) {
    if (f[i] == 1) {
      add(S, i, 1, ++cnt);
      add(i, S, 0, ++cnt);
    }
    if (f[i] == maxx) {
      add(i, T, 1, ++cnt);
      add(T, i, 0, ++cnt);
    }
    for (int j = i + 1; j <= n; j++)
      if (f[j] == f[i] + 1 && a[j] >= a[i]) {
        add(i, j, 1, ++cnt);
        add(j, i, 0, ++cnt);
      }
  }
  while (init())
    ans += dfs(S, inf);
  cout << ans << endl;
  add(S, 1, inf, ++cnt);
  add(1, S, 0, ++cnt);
  if (f[n] == maxx) {
    add(n, T, inf, ++cnt);
    add(T, n, 0, ++cnt);
  }
  while (init())
    ans += dfs(S, inf);
  cout << ans << endl;
}
