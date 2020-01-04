#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
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

const int Max_n = 1e5 + 5;
int n;
int cnt, t[Max_n], c[Max_n * 10];
struct {
  int la, ra, lb, rb;
} k[Max_n];

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    k[i].la = read(), k[i].ra = read(), k[i].lb = read(), k[i].rb = read();
    t[++cnt] = k[i].la;
    t[++cnt] = k[i].ra;
    t[++cnt] = k[i].lb;
    t[++cnt] = k[i].rb;
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
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
