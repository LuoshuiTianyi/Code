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

const int Max_n = 1e6 + 5, Max = 1 << 20, mod = 1e9 + 7;
int n, ans;
int a[Max_n], f[Max + 1], g[100];
int nx[20][Max_n];
void Mod(int &x) { x = x >= mod ? x - mod : x < 0 ? x + mod : x; }

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) f[read()]++;
}
}  // namespace Input

namespace Init {
void main() {
  for (int j = 0; j < 20; j++)
    for (int i = 0; i < Max; i++)
      if (!(i >> j & 1)) Mod(f[i] += f[i | (1 << j)]);
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 0; i < Max; i++) Mod(g[__builtin_popcount(i)] += f[i]);
  for (int i = 0; i <= 20; i++)
    if (i & 1)
      Mod(ans -= g[i]);
    else
      Mod(ans += g[i]);
  cout << ans;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
