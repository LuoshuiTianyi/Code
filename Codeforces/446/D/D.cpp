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
const int Max_n = 505, Max_m = 2e5 + 5;
int n, m, K;
double f[Max_n][Max_n], g[Max_n][Max_n];
bool vis[Max_n];
struct graph {
  int hd[Max_n], deg[Max_n];
  int cntr, nx[Max_m], to[Max_m];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} G;
int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  n = read(), m = read(), K = read();
  for (int i = 1; i <= n; i++) vis[i] = read();
  int u, v;
  while (m--) {
    u = read(), v = read();
  }
}
