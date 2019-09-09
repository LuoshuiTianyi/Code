#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 3e5 + 5;
int n, m, p, nd;
int fa[Max_n], f[Max_n], fl[Max_n], dep[Max_n], jp[20][Max_n];
int cntr, hd[Max_n], nx[Max_n << 1], to[Max_n];
int top, t, stk[Max_n], b2[Max_n], s[Max_n], S[Max_n], du[Max_n];
bool bk[Max_n], rd[600][600];
long long ans;
vector<int> ul[Max_n], vl[Max_n];
struct day {
  int u, v, w, id;
} k[Max_n];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
bool cmp(day a, day b) { return a.w < b.w; }
void build(int x) {
  jp[0][x] = fa[x], f[x] = fl[x] = x, dep[x] = dep[fa[x]] + 1;
  for (int i = hd[x]; i; i = nx[i]) build(to[i]);
}
int find(int *f, int x) { return f[x] == x ? x : f[x] = find(f, f[x]); }
int get_lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int i = 19; ~i; i--)
    if (dep[jp[i][u]] >= dep[v]) u = jp[i][u];
  for (int i = 19; ~i; i--)
    if (jp[i][u] != jp[i][v]) u = jp[i][u], v = jp[i][v];
  return u == v ? u : jp[0][u];
}
void merge(int u, int v) {
  u = find(f, u), v = find(f, v);
  if (u == v) return;
  ans += k[nd].w;
  f[u] = v;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("61.in", "r", stdin);
  freopen("61.out", "w", stdout);
#endif
  n = read(), m = read(), p = read();
  for (int i = 2; i <= n; i++) addr(fa[i] = read(), i);
  for (int i = 1; i <= m; i++)
    k[i].u = read(), k[i].v = read(), k[i].w = read(), k[i].id = i;
  sort(k + 1, k + m + 1, cmp);
  while (p--) {
    int d = read();
    ul[d].push_back(read());
    vl[d].push_back(read());
  }
  du[0] = 1e9, build(1);
  for (int j = 1; j <= 19; j++)
    for (int i = 1; i <= n; i++) jp[j][i] = jp[j - 1][jp[j - 1][i]];
  for (nd = 1; nd <= m; nd++) {
    int x = k[nd].id, U = k[nd].u, V = k[nd].v;
    int lca = get_lca(U, V);
    if (dep[U] + dep[V] - 2 * dep[lca] > ul[x].size()) {
      for (int i = find(fl, U); dep[i] > dep[lca]; i = fa[i])
        fl[i] = fa[i], merge(fa[i], i);
      for (int i = find(fl, V); dep[i] > dep[lca]; i = find(fl, fa[i]))
        fl[i] = fa[i], merge(fa[i], i);
    } else {
      stk[top = 1] = lca, bk[lca] = 1;
      for (int i = U; i != lca; i = fa[i]) stk[++top] = i, bk[i] = 1;
      for (int i = V; i != lca; i = fa[i]) stk[++top] = i, bk[i] = 1;
      for (int i = ul[x].size() - 1; ~i; i--) {
        int u = ul[x][i], v = vl[x][i];
        if (bk[u] && bk[v]) du[u]++, du[v]++;
      }
      int Min = 0;
      for (int i = 1; i <= top; i++)
        if (du[Min] > du[stk[i]]) Min = stk[i];
      for (int i = ul[x].size() - 1; ~i; i--) {
        int u = ul[x][i], v = vl[x][i];
        if (bk[u] && bk[v]) du[u]--, du[v]--;
        if (u == Min) b2[v] = ++t, s[t] = v;
        if (v == Min) b2[u] = ++t, s[t] = u;
      }
      for (int i = 1; i <= top; i++)
        if (!b2[stk[i]]) merge(Min, stk[i]);
      for (int i = ul[x].size() - 1; ~i; i--) {
        int u = ul[x][i], v = vl[x][i];
        if (b2[u] && b2[v]) rd[b2[u]][b2[v]] = rd[b2[v]][b2[u]] = 1;
        if (b2[u] && !b2[v]) S[u]++;
        if (b2[v] && !b2[u]) S[v]++;
      }
      for (int i = 1; i < t; i++)
        for (int j = i + 1; j <= t; j++)
          if (!rd[i][j]) merge(s[i], s[j]);
      for (int i = 1; i <= t; i++)
        if (S[s[i]] < top - t) merge(s[i], Min);
      for (int i = ul[x].size() - 1; ~i; i--) {
        int u = ul[x][i], v = vl[x][i];
        if (b2[u] && b2[v]) rd[b2[u]][b2[v]] = rd[b2[v]][b2[u]] = 0;
        if (b2[u] && !b2[v]) S[u]--;
        if (b2[v] && !b2[u]) S[v]--;
      }
      while (t) b2[s[t--]] = 0;
      while (top) bk[stk[top--]] = 0;
    }
  }
  cout << ans << endl;
}
