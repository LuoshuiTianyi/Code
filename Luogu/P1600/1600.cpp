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

const int Max_n = 3e5 + 5, add = 3e5 + 5;
int n, m, Ans[Max_n];
int s[Max_n], t[Max_n], lca[Max_n], w[Max_n], fa[Max_n], buk[Max_n << 1];
int dep[Max_n];
vector<int> M[Max_n], a1[Max_n], b1[Max_n], a2[Max_n], b2[Max_n];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} G;

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i < n; i++) {
    int u = read(), v = read();
    G.addr(u, v), G.addr(v, u);
  }
  for (int i = 1; i <= n; i++) w[i] = read(), fa[i] = i;
  for (int i = 1; i <= m; i++) 
    M[s[i] = read()].push_back(i), M[t[i] = read()].push_back(i);
}
}  // namespace Input

namespace Init {
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void build(int x, int f) {
  dep[x] = dep[f] + 1;
  go(G, x, i, v) if (v != f) build(v, f);
  for (int i = M[x].size() - 1; ~i; i--) {
    int j = M[x][i];
    if (find(s[j]) != s[j] || find(t[j]) != t[j]) 
      lca[j] = find(s[j]) != s[j] ? find(s[j]) : find(t[j]);
  }
}
void main() {
  build(1, 0);
  for (int i = 1; i <= m; i++) {
  }
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifdef Thyu
  freopen("1600.in", "r", stdin);
  freopen("1600.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
