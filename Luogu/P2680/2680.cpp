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

const int Max_n = 3e5 + 5;
int n, m;
int f[Max_n], c[Max_n];
int s[Max_n], t[Max_n];

struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1], w[Max_n << 1];
  void addr(int u, int v, int W = 0) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G, M;

namespace Input {
void main() {
  n = read(), m = read();
  int u, v, w;
  for (int i = 1; i < n; i++) {
    u = read(), v = read(), w = read();
    G.addr(u, v, w), G.addr(v, u, w);
  }
  for (int i = 1; i <= m; i++) s[i] = read(), t[i] = read();
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= m; i++) M.addr(s[i], i), M.addr(t[i], i);
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2680.in", "r", stdin);
  freopen("2680.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
