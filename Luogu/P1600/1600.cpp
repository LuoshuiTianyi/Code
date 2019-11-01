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

const int Max_n = 3e5 + 5, P = 3e5 + 5;
int n, m, Ans[Max_n];
int s[Max_n], t[Max_n], lca[Max_n], w[Max_n], fa[Max_n], buk[2][Max_n << 1];
int dep[Max_n];
vector<int> M[Max_n], add[2][Max_n], del[2][Max_n];
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
  go(G, x, i, v) if (v != f) build(v, x);
  for (int i = M[x].size() - 1; ~i; i--) {
    int j = M[x][i];
    if (find(s[j]) != s[j] || find(t[j]) != t[j]) 
      lca[j] = find(s[j]) != s[j] ? find(s[j]) : find(t[j]);
  }
}
void main() {
  build(1, 0);
  for (int i = 1; i <= m; i++) {
    int u = s[i], v = t[i], l = lca[i];
    int d1 = dep[u], d2 = dep[u] - (dep[l] << 1) + P;
    add[0][l].push_back(d1), del[0][u].push_back(d1);
    del[1][l].push_back(d2), add[1][v].push_back(d2);
    Ans[l] -= (dep[u] - dep[l] == w[l]);
  }
}
}  // namespace Init

namespace Solve {
void dfs(int x, int fa) {
  //int s0 = w[x] + dep[x], s1 = w[x] - dep[x] + P;
  //int t0 = buk[0][s0], t1 = buk[1][s1];
  //for (int l = 0; l < 2; l++)
  //  for (int i = add[l][x].size(); ~i; i--) buk[l][add[l][x][i]]++;
  //go(G, x, i, v) if (v != fa) dfs(v, x);
  //Ans[x] += buk[0][s0] + buk[1][s1] - t0 - t1;
  //for (int l = 0; l < 2; l++)
  //  for (int i = del[l][x].size(); ~i; i--) buk[l][del[l][x][i]]--;
}
void main() {
  dfs(1, 0);
  for (int i = 1; i <= n; i++) printf("%d ", Ans[i]);
}
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
