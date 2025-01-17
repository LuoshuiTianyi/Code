#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define Fa(x) G.to[f[x]]
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
int n, m, T, Ans;
int a[Max_n], b[Max_n];
int u[Max_n], v[Max_n], v1[Max_n], v2[Max_n], s[Max_n];

int cntd, dfn[Max_n], sz[Max_n], f[Max_n], F[Max_n];
int cntt, rt[Max_n], bel[Max_n], up[Max_n], dn[Max_n], V1[Max_n], V2[Max_n],
    tot[Max_n], key[Max_n];
bool vis[Max_n], ty[Max_n], cir[Max_n];
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
    u[i] = (a[i] + b[i]) % m + 1, v[i] = (a[i] - b[i] + m) % m + 1;
    s[i] = s[i - 1] + 2 - (u[i] == v[i]);
    if (u[i] > v[i]) swap(u[i], v[i]);
  }
  for (int i = 1; i <= n; i++) {
    G.addr(v[i], u[i], read());
    G.addr(u[i], v[i], u[i] != v[i] ? read() : G.w[G.cntr]);
  }
}
}  // namespace Input

namespace SEG_Tree {
int Max[Max_n << 2], tag[Max_n << 2];
int L, R, X, ans;
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
  if (R < L) return;
  if (l >= L && r <= R) {
    Max[o] += X, tag[o] += X;
    return;
  }
  pushdown(o);
  if (mid >= L) add(ls, l, mid);
  if (mid < R) add(rs, mid + 1, r);
  pushup(o);
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    ans = max(ans, Max[o]);
    return;
  }
  pushdown(o);
  if (mid >= L) query(ls, l, mid);
  if (mid < R) query(rs, mid + 1, r);
  pushup(o);
}
}  // namespace SEG_Tree
using namespace SEG_Tree;

namespace Init {
int U, V;
void dfs(int x, int fa) {
  bel[x] = cntt, dfn[x] = ++cntd, f[x] = fa, vis[x] = 1;
  go(G, x, i, v) if (i != fa) {
    if (vis[v]) {
      if (!U) U = x, V = v, key[cntt] = i, ty[cntt] = 1;
      continue;
    }
    up[v] = G.w[i ^ 1], dn[v] = G.w[i];
    dfs(v, i ^ 1);
  }
}
void build1(int x, int fa) {
  tot[cntt] += dn[x], sz[x] = 1;
  go(G, x, i, v) if (v != fa) build1(v, x), sz[x] += sz[v];
}
void Count(int x, int fa, int sum1, int sum2) {
  L = dfn[x], R = dfn[x], X = tot[cntt] - sum2 + sum1, add(1, 1, m);
  go(G, x, i, v) if (v != fa) Count(v, x, sum1 + up[v], sum2 + dn[v]);
}
void build2(int x, int fa) {
  F[x] = fa;
  go(G, x, i, v) if (v != fa && !cir[v]) build2(v, x), sz[x] += sz[v], tot[cntt] += G.w[i];
}
void main() {
  for (int i = 1; i <= m; i++)
    if (!vis[i]) {
      rt[++cntt] = i, U = V = 0, dfs(i, 0);
      if (!U) {
        build1(i, 0);
        Count(i, 0, 0, 0);
      } else {
        int x = U;
        for (; x != V; x = Fa(x)) cir[x] = 1, V1[cntt] += up[x];
        cir[x] = 1, V1[cntt] += G.w[key[cntt] ^ 1];
        for (int x = U; x != V; x = Fa(x)) V2[cntt] += dn[x];
        V2[cntt] += G.w[key[cntt]];
        for (int x = U; x != V; x = Fa(x)) build2(x, 0);
        build2(V, 0);
      }
    }
}
}  // namespace Init

namespace Solve {
int Qry(int x) {
  if (ty[x]) {
    return tot[x] + max(V1[x], V2[x]);
  } else {
    L = dfn[rt[x]], R = dfn[rt[x]] + sz[rt[x]] - 1, ans = 0, query(1, 1, m);
    return ans;
  }
}
void main() {
  for (int i = 1; i <= cntt; i++) Ans += Qry(i);
  cout << Ans << endl;
  int Q = read();
  int x, V;
  while (Q--) {
    x = read(), V = read();
    x -= Ans * T, V -= Ans * T;
    int y = find(x), z = x - s[y - 1] + (y - 1) * 2 + 1;
    int a = u[y], b = v[y], c;
    int now = bel[a];
    if (G.to[z] == a) swap(a, b);
    if (ty[now]) {
      Ans -= Qry(now);
      if (cir[a] && cir[b]) {
        if (a == b) {
          V1[now] -= G.w[z], V1[now] += (G.w[z] = V);
          V2[now] -= G.w[z ^ 1], V2[now] += (G.w[z ^ 1] = V);
        } else {
          if (f[a] == z)
            c = 0;
          else if (f[b] == (z ^ 1))
            c = 1;
          else if (z == key[now])
            c = 1;
          else
            c = 0;
          if (!c)
            V1[now] -= G.w[z], V1[now] += (G.w[z] = V);
          else
            V2[now] -= G.w[z], V2[now] += (G.w[z] = V);
        }
      } else if (F[b] == a) {
        tot[now] -= G.w[z], tot[now] += (G.w[z] = V);
      }
      Ans += Qry(now);
    } else {
      Ans -= Qry(now), X = V - G.w[z];
      if (Fa(a) == b) {
        L = dfn[a], R = dfn[a] + sz[a] - 1, add(1, 1, m);
      } else {
        L = dfn[rt[now]], R = dfn[b] - 1, add(1, 1, m);
        L = dfn[b] + sz[b], R = dfn[rt[now]] + sz[rt[now]] - 1, add(1, 1, m);
      }
      G.w[z] = V;
      Ans += Qry(now);
    }
    printf("%d\n", Ans);
  }
}
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
