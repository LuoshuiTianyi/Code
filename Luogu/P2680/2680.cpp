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

const int Max_n = 3e5 + 5;
int n, m, ans;
int f[Max_n], dep[Max_n], c[Max_n];

struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1], w[Max_n << 1];
  void addr(int u, int v, int W = 0) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G, M;
struct road {
  int s, t, lca, dist;
} k[Max_n];

namespace Input {
void main() {
  n = read(), m = read();
  int u, v, w;
  for (int i = 1; i < n; i++) {
    u = read(), v = read(), w = read();
    G.addr(u, v, w), G.addr(v, u, w);
  }
  for (int i = 1; i <= m; i++) k[i].lca = k[i].s = read(), k[i].t = read();
}
}  // namespace Input

namespace Init {
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
void Get(int x, int fa) {
  go(G, x, i, v) if (v != fa) {
    dep[v] = dep[x] + G.w[i], Get(v, x), f[find(v)] = find(x);
  }
  go(M, x, i, v) if (find(k[v].s) != k[v].s) k[v].lca = find(k[v].s);
  else if (find(k[v].t) != k[v].t) k[v].lca = find(k[v].t);
}
bool cmp(road a, road b) { return a.dist < b.dist; }
void main() {
  for (int i = 1; i <= m; i++) M.addr(s[i], i), M.addr(t[i], i);
  for (int i = 1; i <= n; i++) f[i] = i;
  Get(1, 0);
  for (int i = 1; i <= m; i++)
    k[i].dist = dep[k[i].s] + dep[k[i].t] - (dep[k[i].lca] << 1);
  sort(k + 1, k + m + 1, cmp);
}
}  // namespace Init

namespace Solve {
void main() {
  int l = 0, r = 3e8;
  while (l <= r) {
    int mid = l + r >> 1;
    if (check(mid)) ans = mid, r = mid - 1;
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2680.in", "r", stdin);
  freopen("2680.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
