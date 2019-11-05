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

const int Max = 1 << 15, mod = 1e9;
int T;
int n, all, ans;
int c[100];
int f[Max + 1], g[Max + 1];
void Mod(int &x) { x = x >= mod ? x - mod : x < 0 ? x + mod : x; }

namespace Input {
void main() {
  n = read(), all = (1 << read()) - 1;
  for (int i = 1; i <= n; i++) c[i] = read();
}
}  // namespace Input

namespace Init {
void main() {
  f[0] = 1;
  for (int i = 1; i <= all; i++) f[i] = 0;
}
}  // namespace Init

namespace Solve {
void init() {
  swap(g, f);
  for (int j = 0; j < 15; j++)
    for (int i = 0; i <= all; i++)
      if (i >> j & 1) Mod(g[i] += g[i ^ (1 << j)]);
}
void main() {
  for (int i = 1; i <= n; i++) {
    init();
    for (int j = 0; j <= all; j++) f[j] = j % c[i] != 0 ? g[j ^ all] : 0;
  }
  for (int i = 0; i <= all; i++) Mod(ans += f[i]);
  printf("%d\n", ans);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2829.in", "r", stdin);
  freopen("2829.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Input::main();
    Init::main();
    Solve::main();
  }
}
