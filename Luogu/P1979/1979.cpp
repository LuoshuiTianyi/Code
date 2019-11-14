#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}

const int Max_n = 35 * 35 * 4;
int n, m, Q;
int cnt, id[35][35][5];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 3], to[Max_n << 3], w[Max_n << 3];
  void addr(int u, int v, int W) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G;
struct maze {
  int a[35][35], dis[35][35], vis[35][35];
  int h, t, dx[5] = {0, 1, -1, 0, 0}, dy[5] = {0, 0, 0, 1, -1};
  pair<int, int> q[Max_n];
  void Get_dis(int sx, int sy) {
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) dis[i][j] = 1e9, vis[i][j] = 0;
    dis[sx][sy] = 0, vis[sx][sy] = 1;
    h = 0, q[t = 1] = make_pair(sx, sy);
    while (h < t) {
      pair<int, int> now = q[++h];
      int x = now.first, y = now.second;
      for (int i = 1; i <= 4; i++) {
        int xx = x + dx[i], yy = x + dy[i];
        if (vis[xx][yy] || xx < 1 || xx > n || yy < 1 || yy > m || a[xx][yy])
          continue;
        dis[xx][yy] = dis[x][y] + 1, vis[xx][yy] = 1;
        q[++t] = make_pair(xx, yy);
      }
    }
  }
} map;

namespace Input {
void main() {
  n = read(), m = read(), Q = read();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) map.a[i][j] = read();
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (map.a[i][j])
        for (int k = 1; k <= 4; k++) {
          int xx = i + dx[k], yy = j + dy[k];
          if (xx < 1 || xx > n || yy < 1 || yy > m || map.a[xx][yy]) continue;
          id[i][j][k] = ++cnt;
        }
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("1979.in", "r", stdin);
  freopen("1979.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
