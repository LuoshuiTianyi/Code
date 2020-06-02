#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 2e5 + 5;
int n, m;
int sz[Max_n], son[Max_n], up[Max_n];
int cntd, top[Max_n], dfn[Max_n];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1], w[Max_n << 1];
  void addr(int u, int v, int W) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G;

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), m = read();
  for (int i = 1; i < n; i++) {
    int u = read(), v = read(), w = read();
    G.addr(u, v, w), G.addr(v, u, w);
  }
}
}  // namespace Input

namespace Init {
void dfs1(int x, int fa) {
  sz[x] = 1;
  go(G, x, i, v) if (v != fa) {
    dfs1(v, x), sz[x] += sz[v];
    if (sz[v] >= sz[son[x]]) son[x] = v;
  }
}
void dfs2(int x, int fa) {
}
void main() {
  dfs1(1, 0);
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("K.in", "r", stdin);
  freopen("K.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
