#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, m, S, T;
int head[1001], nx[20001], to[20001], w[20001], cnt;
int deep[1001], nt[1001];
bool book[20001], r[1001];
int inf = 1e9, ans;
void add(int u, int v, int W, int d) {
  to[d] = v, nx[d] = head[u], w[d] = W;
  head[u] = d;
}
queue<int> q;
bool init() {
  memset(book, 0, sizeof(book));
  memset(deep, -1, sizeof(deep));
  deep[S] = 1;
  q.push(S);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = head[x]; i; i = nx[i])
      if (deep[to[i]] == -1 && w[i] > 0) {
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
  for (int i = head[x]; i; i = nx[i])
    if (deep[to[i]] == deep[x] + 1 && !book[i] &&
        (fnow = dfs(to[i], min(limit, w[i])))) {
      book[i] = true;
      flow += fnow;
      limit -= fnow;
      w[i] -= fnow;
      w[i ^ 1] += fnow;
      if (!limit)
        break;
    }
  return flow;
}
void print(int x) {
  if (!x)
    return;
  printf("%d ", x);
  print(nt[x]);
}
int main() {
  freopen("2764.in", "r", stdin);
  freopen("2764.out", "w", stdout);
  cin >> n >> m;
  S = n * 2 + 1, T = n * 2 + 2, cnt = 1;
  for (int i = 1; i <= n; i++) {
    add(S, i, 1, ++cnt);
    add(i, S, 0, ++cnt);
    add(i + n, T, 1, ++cnt);
    add(T, i + n, 0, ++cnt);
  }
  int u, v;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    v += n;
    add(u, v, inf, ++cnt);
    add(v, u, 0, ++cnt);
  }
  while (init())
    dfs(S, inf);
  for (int i = 2; i <= cnt; i += 2) {
    int p1 = to[i], p2 = to[i ^ 1];
    if (p1 == S || p1 == T || p2 == S || p2 == T)
      continue;
    if (w[i ^ 1])
      nt[to[i ^ 1]] = to[i] - n, r[to[i] - n] = true;
  }
  for (int i = 1; i <= n; i++)
    if (!r[i]) {
      ans++;
      print(i);
      cout << endl;
    }
  cout << ans;
}
