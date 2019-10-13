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
const int Max_n = 505, Max_m = 1e4 + 5;
int n, m;
int node[Max_n], tp[Max_n];
struct graph {
  int hd[Max_n];
  int cntr = 1, nx[Max_m], to[Max_m], w[Max_m];
  void addr(int u, int v, int W) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G, G2;
namespace FLOW {
int Dinic(int &G, int S, int T) {}
}  // namespace FLOW
void Solve(int l, int r) {
  
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("4897.in", "r", stdin);
  freopen("4897.out", "w", stdout);
#endif
  n = read(), m = read();
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    u = read(), v = read(), w = read();
    G.addr(u, v, w), G.addr(v, u, 0);
    G.addr(u, v, 0), G.addr(v, u, w);
  }
  for (int i = 1; i <= n; i++) node[i] = i;
  Solve(1, n);
}
