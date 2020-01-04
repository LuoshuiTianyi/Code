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

const int Maxx = 1e6 + 5;
LL ans;
int n, siz;
int minn[Maxx], nu[Maxx];

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    int Min = 1e9, Max = -1e9, tot = read();
    bool fl = 0;
    for (int j = 1; j <= tot; j++) {
      int x = read();
      if 
      Max = max(Max, x), Min = min(Min, x);
    }
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
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
