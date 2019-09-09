#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, m, head[203], nx[50001], to[50001], w[50001], S, T, cnt, tot, inf = 1e9;
int deep[203], ans, book[50001];
void addroad(int u, int v, int W) {
  cnt++;
  to[cnt] = v, nx[cnt] = head[u], w[cnt] = W;
  head[u] = cnt;
}
queue<int> q;
bool init() {
  memset(deep, 0x7f, sizeof(deep));
  memset(book, false, sizeof(book));
  deep[S] = 1;
  q.push(S);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = head[x]; i; i = nx[i])
      if (deep[to[i]] > inf && w[i] > 0) {
        deep[to[i]] = deep[x] + 1;
        q.push(to[i]);
      }
  }
  return deep[T] < inf;
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
int main() {
  freopen("2756.in", "r", stdin);
  freopen("2756.out", "w", stdout);
  cin >> m >> n;
  S = m + n + 1, T = m + n + 2, tot = m + n + 2, cnt = 1;
  for (int i = 1; i <= m; i++) {
    addroad(S, i, 1);
    addroad(i, S, 0);
  }
  for (int i = m + 1; i <= m + n; i++) {
    addroad(i, T, 1);
    addroad(T, i, 0);
  }
  int u, v;
  while (1) {
    scanf("%d%d", &u, &v);
    if (u == v && u == -1)
      break;
    addroad(u, v, inf);
    addroad(v, u, 0);
  }
  while (init())
    ans += dfs(S, inf);
  if (!ans) {
    cout << "No Solution!";
    return 0;
  }
  cout << ans << endl;
  for (int i = 2; i <= cnt; i += 2) {
    int p1 = to[i], p2 = to[i ^ 1];
    if (p1 == S || p2 == S || p1 == T || p2 == T)
      continue;
    if (w[i ^ 1])
      printf("%d %d\n", to[i ^ 1], to[i]);
  }
}
