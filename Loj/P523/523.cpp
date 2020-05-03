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

const int Max_n = 5e5 + 5;
int n, m, T, ans;
int a[Max_n], b[Max_n];
int u[Max_n], v[Max_n], s[Max_n];
int cntd, dfn[Max_n], sz[Max_n];

namespace Input {
void main() {
  n = read(), m = read(), T = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  for (int i = 1; i <= n; i++) {
    b[i] = read();
    s[i] = s[i - 1] + 2 - ((u[i] = (a[i] + b[i]) % n + 1) == (v[i] = (a[i] - b[i] + n) % n + 1));
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
#ifndef ONLINE_JUDGE
  freopen("523.in", "r", stdin);
  freopen("523.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
