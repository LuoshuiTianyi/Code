#include <cstdio>
#include <iostream>
#include <queue>
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

const int Max_n = 1e5 + 5, inf = 1e9;
int n, m, lim, mod;
int Dis, pdis[Max_n], rdis[Max_n];
int f[Max_n][51];
bool vis[Max_n];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1], w[Max_n << 1];
  void memset(int n) {
    cntr = 0;
    for (int i = 1; i <= n; i++) hd[i] = 0;
  }
  void addr(int u, int v, int W) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G, G2;

namespace Input {
void main() {
  n = read(), m = read(), lim = read(), mod = read();
  G.memset(n), G2.memset(n);
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    u = read(), v = read(), w = read();
    G.addr(u, v, w), G2.addr(v, u, w);
  }
}
}  // namespace Input

namespace Init {
struct node {
  int id, dis;
};
priority_queue<node> q;
void Push(int x, int dis) { q.push((node){x, dis}); }
void Dij(graph G, int s, int *dis) {
  for (int i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
  Push(s, dis[s] = 0);
  while (!q.empty()) {
    int x = q.top().id, tp;
    if (vis[x]) continue;
    vis[x] = 1, q.pop();
    go(G, x, i, v) if ((tp = dis[x] + G.w[i]) < dis[v]) Push(v, dis[v] = td);
  }
}
void main() {
  Dij(G, 1, pdis), Dij(G2, n, rdis); 
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= K; j++) f[i][j] = -1;
}
}  // namespace Init

namespace Solve {
int status[Max_n];
int DP(int x, int left) {
  if (left < 0) return 0;
  if (x == n) return 1;
  if (status[x] == left) return -1;
  int &res = f[x][left];
  if (res != -1) return res;
  res = 0;
  go(G, x, i, v) {
  }
}
void main() {
  printf("%d\n", DP(1, K));
}
}  // namespace Solve

int main() {
#ifdef Thyu
  freopen("3953.in", "r", stdin);
  freopen("3953.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Input::main();
    Init::main();
    Solve::main();
  }
}
