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

const int Max_n = 12, inf = 1e8;
int n, m;
int r[Max_n][Max_n];
int f[Max_n + 1][1 << Max_n];
int Min[Max_n][1 << Max_n], G[1 << Max_n];

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (i != j) r[i][j] = inf;
  int u, v;
  for (int i = 1; i <= m; i++)
    u = read(), v = read(), r[u][v] = r[v][u] = min(r[u][v], read());
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++)
    for (int s = 0; s < (1 << n); s++) {
      int minn = inf;
      for (int j = 1; j <= n; j++)
        if (s >> j - 1 & 1) minn = min(minn, r[j][i]);
      Min[i][s] = minn;
    }
  for (int s = 1; s < (1 << n); s++) {
    int to = 0;
    for (int i = 1; i <= n; i++) {
      if (!(s >> i - 1 & 1)) continue;
      for (int j = 1; j <= n; j++)
        if (r[i][j] != inf && !(s >> j - 1 & 1))
          to |= 1 << j - 1;
    }
    G[s] = to;
  }
  for (int i = 1; i <= n; i++)
    for (int s = 0; s < (1 << n); s++) f[i][s] = inf;
  for (int i = 1; i <= n; i++) f[1][1 << i - 1] = 0;
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 2; i <= n; i++)
    for (int s = 1; s < (1 << n); s++)
      for (int son = s;; son = (son - 1) & s) {
        if ((G[son] | (s ^ son)) != G[son]) continue;
        f[i][s] = min(f[i][s], f[i - 1][son] + work(s ^ son, son)
      }
}
}  // namespace Solve

int main() {
#ifdef Thyu
  freopen("3959.in", "r", stdin);
  freopen("3959.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
