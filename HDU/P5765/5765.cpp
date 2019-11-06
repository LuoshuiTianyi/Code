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

const int Max = 1 << 20;
int T;
int n, m, fa[21];
int u[Max + 1], v[Max + 1];
int f[Max + 1];
bool r[21][21];

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i <= m; i++) u[i] = read(), v[i] = read();
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
    for(int j = 1; j <= n; j++) r[i][j] = 0;
  }
  for (int i = 1; i <= m; i++) r[u[i]][v[i]] = r[v[i]][u[i]] = 1;
}
}  // namespace Init

namespace Solve {
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void main() {
  for (int s = 0; s < (1 << n); s++) {
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("5765.in", "r", stdin);
  freopen("5765.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Input::main();
    Init::main();
    Solve::main();
  }
}
