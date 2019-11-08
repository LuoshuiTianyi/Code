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
int n, K, t;
char S[Max_n];
namespace SAM {
}

namespace Input {
void main() {
  scanf("%s", S + 1);
  t = read(), K = read();
}
}  // namespace Input

namespace Init {
void main() {
  n = strlen(S + 1);
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3975.in", "r", stdin);
  freopen("3975.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
