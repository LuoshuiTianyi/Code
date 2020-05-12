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

const int Max_n = 2e6 + 5, M = 26;
int n, m, node[Max_n];
char s[Max_n];

namespace Trie {
int rt[200000], ch[Max_n << 1][M], cnt;
int cntd, dfn[Max_n], sz[Max_n], bel[Max_n];
void add(int x, int &o, int dep) {
}
void build(int x) {
  dfn[x] = ++cntd;
}
}  // namespace Trie
using namespace Trie;

namespace Input {
void main() { 
  n = read();
  for (int i = 1; i <= n; i++) {
    scanf("", );
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
  freopen("4212.in", "r", stdin);
  freopen("4212.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
