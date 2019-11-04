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

const int Max_n = 3e5 + 5, Max = 1 << 20;
int n;
int a[Max_n], f[Max + 1];

namespace Input {
void main() {
  n = read();
  for (int i = 0; i <= Max; i++) f[i] = 1e9;
  for (int i = 1; i <= n; i++)
    a[i] = read() ^ a[i - 1], f[a[i]] = min(f[a[i]], i);
}
}  // namespace Input

namespace Init {
void main() {
  for (int j = 0; j < 
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("5092.in", "r", stdin);
  freopen("5092.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
