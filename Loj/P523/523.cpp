#include <algorithm>
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
int n, m, T, ans;
int a[Max_n], b[Max_n];
int u[Max_n], v[Max_n], v1[Max_n], v2[Max_n], s[Max_n];

int cntd, dfn[Max_n], sz[Max_n], f[Max_n];
int cntt, rt[Max_n], bel[Max_n], up[Max_n], dn[Max_n], V1[Max_n], V2[Max_n], tot[Max_n];
bool vis[Max_n], ty[Max_n];
struct graph {
  int hd[Max_n];
  int cntr = 1, nx[Max_n << 1], to[Max_n << 1], w[Max_n << 1];
  void addr(int u, int v, int W) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G;

int find(int x) { return lower_bound(s + 1, s + n + 1, x) - s; }

namespace Input {
void main() {
  n = read(), m = read(), T = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  for (int i = 1; i <= n; i++) {
    b[i] = read();
    u[i] = (a[i] + b[i]) % n + 1, v[i] = (a[i] - b[i] + n) % n + 1;
  }
  for (int i = 1; i <= n; i++) {
    G.addr(v[i], u[i], read());
    if (u[i] != v[i]) G.addr(u[i], v[i], read());
  }
}
}  // namespace Input

namespace SEG_Tree {
int Max[Max_n << 1], tag[Max_n << 1];
int L, R, x, ans;
#define ls (o << 1)
#define rs (o << 1 | 1)
#define mid (l + r >> 1)
void pushdown(int o) {
  tag[ls] += tag[o], tag[rs] += tag[o];
  Max[ls] += tag[o], Max[rs] += tag[o];
  tag[o] = 0;
}
void pushup(int o) { Max[o] = max(Max[ls], Max[rs]); }
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    Max[o] += x, tag[o] += x;
    return;
  }
  pushdown(o);
  if (mid >= L) add(ls, l, mid);
  if (mid < R) add(rs, mid + 1, r);
}
}  // namespace SEG_Tree

namespace Init {
int U, V, id;
void dfs(int x, int fa) {
  bel[x] = cntt, dfn[x] = ++cntd, f[x] = fa;
  go(G, x, i, v) if (i != fa) {
    if (vis[v]) {
      U = x, V = v, id = i;
      return;
    }
    up[v] = G.w[i ^ 1], dn[v] = G.w[i];
    dfs(v, i ^ 1);
  }
}
void build1(int x, int fa, int sum1, int sum2) {
  tot[cntt] += dn[x], sz[x] = 1;
  go(G, x, i, v) if (v != fa) build1(v, x, sum1 + up[v], sum2 + dn[v]), sz[x] += sz[v];
}
void build2(int x, int fa) {
  tot[cntt] += dn[x], sz[x] = 1;
  go(G, x, i, v) if (v != fa) build2(v, x), sz[x] += sz[v];
}
void main() {
  for (int i = 1; i <= n; i++)
    if (!vis[i]) {
      rt[++cntt] = i, U = V = 0, dfs(i, 0);
      if (!U) {
        build1(i, 0, 0, 0);
      } else {
        int x = U;
        for (; x != V; x = G.to[f[x]]) vis[x] = 0, V1[cntt] += ;
        vis[x] = 0;
      }
    }
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("523.in", "r", stdin);
  freopen("523.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
