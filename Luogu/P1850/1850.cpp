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

const int Max_n = 2005;
int n, m, v, e;
int a[Max_n], b[Max_n];
double k[Max_n];
int dis[Max_n][Max_n];

namespace Input {
void main() {
  n = read(), m = read(), v = read(), e = read();
  for (int i = 1; i <= n; i++) a[i] = read();
}
}  // namespace Input

namespace Init {
void main() {}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("1850.in", "r", stdin);
  freopen("1850.out", "w", stdout);
#endif
  Input::main(), Init::main(), Solve::main();
}
