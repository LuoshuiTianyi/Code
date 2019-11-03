#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
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

const int Max_n = 3e5 + 5;
int n, m, Q;
int x[Max_n], y[Max_n];
LL q[Max_n << 1];
bool qt[Max_n << 1];
vector<int> que[Max_n], pad[Max_n];

struct Tree {
  int t1, t2, add[Max_n], del[Max_n];
  int c[Max_n];
  void Add(int k, int x) {
  }
  void init() {
    while (t1) Add(add[--t1], -1);
    while (t2) Add(del[--t1], 1);
  }
} s;

namespace Input {
void main() {
  n = read(), m = read(), Q = read();
  for (int i = 1; i <= n; i++) q[i] = 1ll * i * m;
  for (int i = 1; i <= Q; i++) {
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
#ifdef Thyu
  freopen("3960.in", "r", stdin);
  freopen("3960.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
