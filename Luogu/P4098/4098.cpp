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

const int Max_n = 5e4 + 5;
int n;
int a[Max_n];
int top, stk[Max_n];

namespace Trie {
int rt[Max_n], ch[Max_n * 31][2];
void add(int now, int dep) {
  
}
}

namespace Input {
void main() { n = read(); }
}  // namespace Input

namespace Init {
void main() {}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4098.in", "r", stdin);
  freopen("4098.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
