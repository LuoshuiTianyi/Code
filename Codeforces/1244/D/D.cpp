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
const int Max_n = 1e5 + 5;
int n;
int c[Max_n][3], col[Max_n];
LL f[Max_n][3], s[Max_n][3];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} G;
void DP(int x, int fa) {
  for (int i = 0; i < 3; i++) {
    f[x][i] = c[x][i];
    go(G, x, i, v) if (v != fa) {
      int minn = (i + 1) % 3;
      for (int j = 1; j < 3; j++)
        if (j != i && f[v][minn] > f[v][j]) minn = j;
      f[x][i] += f[v][minn], s[v][i] = minn;
    }
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) c[i][0] = read();
  for (int i = 1; i <= n; i++) c[i][1] = read();
  for (int i = 1; i <= n; i++) c[i][2] = read();
  int u, v;
  for (int i = 1; i < n; i++) {
    u = read(), v = read();
    G.addr(u, v), G.addr(v, u);
  }
  DP(1, 0);
  int Min = 0;
  for (int i = 1; i < 3; i++) if (f[1][i] > f[1][Min]) Min = i;
  cout << f[1][Min] << endl;
}
