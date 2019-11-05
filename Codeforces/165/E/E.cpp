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

const int Max = 1 << 22;
int n, all;
int f[Max + 1];

namespace Input {
void main() {
  n = read(), all = Max - 1;
  for (int i = 1; i <= n; i++) f[read()] = read();
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 0; i < Max; i++) if (!f[i]) f[i] = -1;
}
}  // namespace Init

namespace Solve {
void main() {
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
