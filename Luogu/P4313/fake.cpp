#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define LL long long

inline int read();

const int M = 5e4 + 2;
int n, m, cnt, c, S, T, sum;
int he[M << 1], ne[M << 3], to[M << 3], w[M << 3];

void Link(int x, int y, int z) {
  if (z != 1e9) sum += z;
  ne[++c] = he[x];
  he[x] = c;
  to[c] = y;
  w[c] = z;
  ne[++c] = he[y];
  he[y] = c;
  to[c] = x;
  w[c] = 0;
}

namespace FLOW {
queue<int> Q;
int dep[M << 1], cur[M << 1];

bool Bfs() {
  memcpy(cur, he, sizeof(he));
  memset(dep, 0, sizeof(dep));
  while (!Q.empty()) Q.pop();
  dep[S] = 1;
  Q.push(S);
  while (!Q.empty()) {
    int p = Q.front();
    Q.pop();
    for (int i = he[p]; i; i = ne[i]) {
      if (dep[to[i]] || !w[i]) continue;
      dep[to[i]] = dep[p] + 1;
      Q.push(to[i]);
      if (to[i] == T) return 1;
    }
  }
  return 0;
}

int Dinic(int p, int v) {
  if (p == T) return v;
  int las = v;
  for (int i = he[p]; i && las; i = ne[i]) {
    if (dep[to[i]] != dep[p] + 1 || !w[i]) continue;
    int k = Dinic(to[i], min(w[i], las));
    if (!k) {
      dep[to[i]] = -1;
      continue;
    }
    w[i] -= k, w[i ^ 1] += k;
    las -= k;
  }
  if (las != 0) dep[p] = -1;
  return v - las;
}

int Solve() {
  int ans = 0, now;
  while (Bfs()) {
    while ((now = Dinic(S, 2e9))) ans += now;
  }
  return ans;
}
}  // namespace FLOW

#define ID(a, b) ((a - 1) * m + b)
void Init() {
  S = n * m + 1, T = n * m + 2;
  cnt = n * m + 3;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) Link(S, ID(i, j), read());
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) Link(ID(i, j), T, read());
  int tmp = cnt;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      int now = ++cnt;
      Link(S, now, read());
      Link(now, ID(i, j), 1e9);
      if (i - 1) Link(now, ID(i - 1, j), 1e9);
      if (i < n) Link(now, ID(i + 1, j), 1e9);
      if (j - 1) Link(now, ID(i, j - 1), 1e9);
      if (j < m) Link(now, ID(i, j + 1), 1e9);
    }
  cnt=tmp;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      int now = ++cnt;
      Link(now, T, read());
      Link(ID(i, j), now, 1e9);
      if (i - 1) Link(ID(i - 1, j), now, 1e9);
      if (i < n) Link(ID(i + 1, j), now, 1e9);
      if (j - 1) Link(ID(i, j - 1), now, 1e9);
      if (j < m) Link(ID(i, j + 1), now, 1e9);
    }
}

void Work() {
  n = read(), m = read();
  c = 1;

  Init();
  printf("%d %d", sum, FLOW::Solve());

}

int main() {
  freopen("4313.in", "r", stdin);
  freopen("4313.out", "w", stdout);
  Work();

  return 0;
}

inline int read() {
  char c;
  bool type = 1;
  while ((c = getchar()) < '0' || c > '9')
    if (c == '-') type = 0;
  int ans = c ^ 48;
  while ((c = getchar()) >= '0' && c <= '9')
    ans = (ans << 3) + (ans << 1) + (c ^ 48);
  return type ? ans : -ans;
}
