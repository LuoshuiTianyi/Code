#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, ans, now, S, T;
int head[100001], nx[100001], to[100001], w[100001], cnt, diff = 50000;
int deep[100001], nxt[100001];
bool book[100001], r[100001];
int inf = 1e9;
void add(int u, int v, int W, int d) {
  to[d] = v, nx[d] = head[u], w[d] = W;
  head[u] = d;
}
void print(int x) {
  if (!x)
    return;
  printf("%d ", x);
  print(nxt[x]);
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
  for (int i = head[x]; i; i = nx[i])
    if (!book[i] && deep[to[i]] == deep[x] + 1 &&
        (fnow = dfs(to[i], min(limit, w[i])))) {
      book[i] = true;
      w[i] -= fnow, w[i ^ 1] += fnow;
      flow += fnow, limit -= fnow;
      if (!limit)
        break;
    }
  return flow;
}
int main() {
  freopen("2765.in", "r", stdin);
  freopen("2765.out", "w", stdout);
  cin >> n;
  S = 99999, T = 100000, cnt = 1;
  while (now - ans <= n) {
    memset(r, 0, sizeof(r));
    for (int i = 2; i <= cnt; i += 2)
      if (w[i ^ 1]) {
        int p1 = to[i], p2 = to[i ^ 1];
        if (p1 == S || p1 == T || p2 == S || p2 == T)
          continue;
        nxt[to[i ^ 1]] = to[i] - diff;
        r[to[i] - diff] = true;
      }
    now++;
    add(S, now, 1, ++cnt);
    add(now, S, 0, ++cnt);
    add(now + diff, T, 1, ++cnt);
    add(T, now + diff, 0, ++cnt);
    for (int i = 1; i * i - now < now; i++)
      if (i * i > now) {
        add(i * i - now, now + diff, inf, ++cnt);
        add(now + diff, i * i - now, 0, ++cnt);
      }
    while (init())
      ans += dfs(S, inf);
  }
  cout << now - 1 << endl;
  for (int i = 1; i <= now - 1; i++)
    if (!r[i]) {
      print(i);
      printf("\n");
    }
}
