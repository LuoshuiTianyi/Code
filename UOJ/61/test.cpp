#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define ll long long
#define MAX 300300
inline int read() {
  int x = 0;
  bool t = false;
  char ch = getchar();
  while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
  if (ch == '-') t = true, ch = getchar();
  while (ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
  return t ? -x : x;
}
int n, m, P, cnt;
ll ans;
struct Work {
  int u, v, w, t;
} p[MAX];
bool operator<(Work a, Work b) { return a.w < b.w; }
struct Limit {
  int a, b;
};
vector<Limit> A[MAX];
vector<int> E[MAX];
int dg[MAX];
struct DSU {
  int f[MAX];
  int getf(int x) { return x == f[x] ? x : f[x] = getf(f[x]); }
} B, C;
int fa[MAX], dep[MAX];
bool check(int u, int v, int k) {
  while (k--) {
    if (dep[u] < dep[v]) swap(u, v);
    u = fa[u];
    if (u == v) return false;
  }
  return true;
}
void Merge(int u, int v, int w) {
  if (cnt == 4358 && B.getf(u) != B.getf(v)) cout << u << " " << v << endl;
  u = B.getf(u);
  v = B.getf(v);
  if (u == v) return;
  B.f[u] = v;
  ans += w;
}
int S[MAX], len;
int U[MAX], su;
void GetLine(int u, int v) {
  len = 0;
  while (u ^ v) {
    if (dep[u] < dep[v]) swap(u, v);
    S[++len] = u;
    u = fa[u];
  }
  S[++len] = u;
}
bool vis[MAX];
int main() {
  freopen("61.in", "r", stdin);
  freopen("61.ans", "w", stdout);
  n = read();
  m = read();
  P = read();
  dep[1] = 1;
  for (int i = 2; i <= n; ++i) fa[i] = read(), dep[i] = dep[fa[i]] + 1;
  for (int i = 1; i <= m; ++i)
    p[i].u = read(), p[i].v = read(), p[i].w = read(), p[i].t = i;
  for (int i = 1; i <= P; ++i) {
    int t = read(), a = read(), b = read();
    A[t].push_back((Limit){a, b});
  }
  sort(&p[1], &p[m + 1]);
  for (int i = 1; i <= n; ++i) B.f[i] = C.f[i] = i;
  cnt = 1;
  for (int i = 1; i <= m; ++i, cnt++) {
    if (check(p[i].u, p[i].v, A[p[i].t].size())) {
      int u = C.getf(p[i].u), v = C.getf(p[i].v);
      while (u ^ v) {
        if (dep[u] < dep[v]) swap(u, v);
        Merge(u, fa[u], p[i].w);
        C.f[u] = fa[u], u = C.getf(u);
      }
    } else {
      for (auto u : A[p[i].t]) {
        dg[u.a]++;
        dg[u.b]++;
        E[u.a].push_back(u.b);
        E[u.b].push_back(u.a);
      }
      GetLine(p[i].u, p[i].v);
      int x, mn = 1e9;
      su = 0;
      for (int j = 1; j <= len; ++j)
        if (dg[S[j]] < mn) mn = dg[S[j]], x = S[j];
      if (i == 4358) cout << x << endl;
      if (i == 4358) {
        //for (int j = 1; j <= len; ++j)
        //  cout << S[j] << " ";
        cout << E[x][0];
        cout << endl;
      }
      for (int v : E[x]) vis[v] = true;
      for (int j = 1; j <= len; ++j)
        if (!vis[S[j]]) U[++su] = S[j], Merge(S[j], x, p[i].w);
      for (int v : E[x]) vis[v] = false;
      for (int y : E[x]) {
        for (int v : E[y]) vis[v] = true;
        for (int v : E[x])
          if (!vis[v]) Merge(y, v, p[i].w);
        for (int v : E[y]) vis[v] = false;
        if (E[y].size() < su)
          Merge(x, y, p[i].w);
        else {
          for (int v : E[y]) vis[v] = true;
          for (int j = 1; j <= su; ++j)
            if (!vis[U[j]]) Merge(U[j], y, p[i].w);
          for (int v : E[y]) vis[v] = false;
        }
      }
      for (auto u : A[p[i].t]) {
        --dg[u.a];
        --dg[u.b];
        E[u.a].clear();
        E[u.b].clear();
      }
    }
    if (i == 4358)
      cout << ans << endl;
  }
  printf("%lld\n", ans);
  return 0;
}
