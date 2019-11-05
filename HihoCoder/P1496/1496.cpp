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
int n;
struct sum {
  int mx, cmx;
} f[Max + 1];

namespace Input {
void main() {
  n = read();
  for (int i = 0; i < Max; i++) f[i] = (sum){0, 0};
  
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
  freopen("1496.in", "r", stdin);
  freopen("1496.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Input::main();
    Init::main();
    Solve::main();
  }
}
