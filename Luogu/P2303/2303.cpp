#include <cmath>
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

const int Max_n = 1e3;
LL n;
LL top, stk[Max_n];
LL f[Max_n];

namespace Input {
void main() { n = read(); }
}  // namespace Input

namespace Solve {
void main() {
  for (int i = sqrt(n); i; i--) {
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2303.in", "r", stdin);
  freopen("2303.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
