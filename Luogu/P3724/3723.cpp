#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define f(i) STA[i].first
#define d(i) STA[i].second
const int mod = 9e5 + 1;
int n, m, limit, maxx, cnt, C, a[101], w[101], c[21];
int f[101][101], D;
inline void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
pair<int, int> STA[1000001];
struct node {
  int L, F, t;
};
struct Check {
  int x[mod], y[mod], nx[mod], head[mod], cnt;
  int get_key(int X, int Y) { return (998244ll * X + Y) % mod; }
  inline void add(int X, int Y) {
    int now = get_key(X, Y);
    cnt++;
    nx[cnt] = head[now], x[cnt] = X, y[cnt] = Y;
    head[now] = cnt;
  }
  inline bool query(int X, int Y) {
    int now = get_key(X, Y);
    for (register int i = head[now]; i; i = nx[i])
      if (X == x[i] && Y == y[i])
        return true;
    return false;
  }
} Map, M;
inline void Max(int &a, int b) { a = a < b ? b : a; }
queue<node> q;
inline void bfs() {
  q.push((node){0, 1, 1});
  while (!q.empty()) {
    node now = q.front();
    q.pop();
    if (now.t == D)
      continue;
    q.push((node){now.L + 1, now.F, now.t + 1});
    if (now.L > 1 && 1ll * now.L * now.F <= maxx &&
        !Map.query(now.L * now.F, now.L)) {
      int A = now.L * now.F, B = now.t + 1;
      q.push((node){now.L, A, B});
      if (!M.query(A, 9181283))
        STA[++cnt] = make_pair(A, B), M.add(A, 9181283);
      Map.add(A, now.L);
    }
  }
}
int main() {
  freopen("3723.in", "r", stdin);
  freopen("3723.out", "w", stdout);
  read(n), read(m), read(limit);
  for (register int i = 1; i <= n; i++)
    read(a[i]);
  for (register int i = 1; i <= n; i++)
    read(w[i]);
  for (register int i = 1; i <= m; i++)
    read(c[i]), Max(maxx, c[i]);
  for (register int i = 1; i <= n; i++)
    for (register int j = a[i]; j <= limit; j++)
      Max(f[i][j - a[i]], f[i - 1][j] + 1),
          Max(f[i][min(limit, j - a[i] + w[i])], f[i - 1][j]);
  for (register int i = 1; i <= n; i++)
    for (register int j = 1; j <= limit; j++)
      Max(D, f[i][j]);
  bfs();
  sort(STA + 1, STA + cnt + 1);
  for (register int i = 1; i <= m; i++) {
    if (c[i] <= D) {
      printf("1\n");
      continue;
    }
    int mmax = -1e9, Ans = 0;
    for (register int l = 1, r = cnt; r; r--) {
      while (f(l) + f(r) <= c[i] && l < cnt)
        Max(mmax, f(l) - d(l)), l++;
      if (f(r) + D - d(r) + mmax >= c[i])
        Ans = 1;
      if (f(r) <= c[i] && f(r) + D - d(r) >= c[i])
        Ans = 1;
    }
    printf("%d\n", Ans);
  }
}
