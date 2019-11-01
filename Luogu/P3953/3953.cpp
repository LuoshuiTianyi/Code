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

const int Max_n = 1e5 + 5;
int n, m, mod;
LL Dis;
struct node {
  int id, dis;
};
struct graph {
  int hd[Max_n], dis[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1], w[Max_n << 1];
  void addr(int u, int v, int W) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G, G2;

namespace Input {
void main() {
  n = read(), m = read();
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    u = read(), v = read(), w = read();
    G.addr(u, v, w), G2.addr(v, u, w);
  }
}
}  // namespace Input

namespace Init {
void main() {}
}  // namespace Init

namespace Solve {
void main() {}
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
