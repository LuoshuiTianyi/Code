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

const int Max_n = 2e5 + 5, mod = 998244353;
int n, m;
int deg[Max_n];
struct graph {
  int cntr;
  int hd[Max_n], nx[Max_n * 3], to[Max_n * 3];
  void addr(int u, int v) {
    cntr++;
    hd[u] = cntr, nx[cntr] = hd[u], to[cntr] = v;
  }
} G;

namespace Input {
void main() { fread(read_str, 1, 1 << 25, stdin); }
}  // namespace Input

namespace Init {
void main() {}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("J.in", "r", stdin);
  freopen("J.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
