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

const int Max_n = 6e5 + 5, mod = 998244353, G = 3;
int n;

int bit, len, rev[Max_n];
int ksm(int a, int b = mod - 2) {
}
struct poly {
  int f[Max_n];
  void init() {
    for (int i = 0; i < Max_n; i++) f[i] = 0;
  }
  void dft(int t) {
    
  }
};

namespace Input {
void main() {}
}  // namespace Input

namespace Init {
void main() {}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4726.in", "r", stdin);
  freopen("4726.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
