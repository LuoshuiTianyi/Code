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

const int Max_n = 25;
int n, m, Q;
int siz, p1[Max_n * Max_n], p2[Max_n * Max_n];
char s1[Max_n][15], s2[Max_n][15];

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) scanf("%s", s1[i]);
  for (int i = 1; i <= m; i++) scanf("%s", s2[i]);
}
}  // namespace Input

namespace Init {
void main() {
  int pp = 1, qq = 1;
  do {
    siz++, p1[siz] = pp, p2[siz] = qq;
    pp = pp % n + 1;
    qq = qq % m + 1;
  } while (pp != 1 || qq != 1);
}
}  // namespace Init

namespace Solve {
void main() {
  Q = read();
  int x;
  while (Q--) {
    x = read();
    printf("%s%s\n", s1[p1[(x - 1) % siz + 1]], s2[p2[(x - 1) % siz + 1]]);
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
