#include <cstdio>
#include <iostream>
using namespace std;
int n, m, S, T, w[300001], head[300001], nx[600001], to[600001];
int size[300001], deep[300001], son[300001], fa[300001], top[300001],
    cir = 100000;
int tag1[1000001], tag2[1000001], Ans[300001];
int hd1[300001], hd2[300001], nx1[600001], nx2[600001], to1[600001],
    to2[600001];
int cnt, sum1, sum2;
struct Pro {
  int t1, t2;
} k[600001];
void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch)) ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
void add(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void build1(int x) {
  size[x] = 1;
  top[x] = x;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x]) {
      fa[to[i]] = x;
      deep[to[i]] = deep[x] + 1;
      build1(to[i]);
      size[x] += size[to[i]];
      if (size[to[i]] > size[son[x]]) son[x] = to[i];
    }
}
void build2(int x) {
  if (son[x]) {
    top[son[x]] = top[x];
    build2(son[x]);
  }
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x] && to[i] != son[x]) build2(to[i]);
}
int LCA(int u, int v) {
  while (top[u] != top[v]) {
    if (deep[top[u]] < deep[top[v]]) swap(u, v);
    u = fa[top[u]];
  }
  if (deep[u] > deep[v]) swap(u, v);
  return u;
}
void Ad(int t1, int t2, int d) { k[d].t1 = t1, k[d].t2 = t2; }
void Ad1(int u, int d) {
  sum1++;
  to1[sum1] = d, nx1[sum1] = hd1[u], hd1[u] = sum1;
}
void Ad2(int u, int d) {
  sum2++;
  to2[sum2] = d, nx2[sum2] = hd2[u], hd2[u] = sum2;
}
void Count(int x) {
  int pos1 = deep[x] + w[x] + cir, pos2 = deep[x] - w[x] + cir;
  int now1 = tag1[pos1], now2 = tag2[pos2];
  for (int i = hd1[x]; i; i = nx1[i]) {
    tag1[k[to1[i]].t1]++;
    tag2[k[to1[i]].t2]++;
  }
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x]) Count(to[i]);
  Ans[x] += tag1[pos1] - now1 + tag2[pos2] - now2;
  for (int i = hd2[x]; i; i = nx2[i]) {
    tag1[k[to2[i]].t1]--;
    tag2[k[to2[i]].t2]--;
  }
}
int main() {
#ifdef Thyu
  freopen("1600.in", "r", stdin);
  freopen("1600.ans", "w", stdout);
#endif
  read(n), read(m);
  int u, v;
  for (int i = 1; i < n; i++) {
    read(u), read(v);
    add(u, v, i);
    add(v, u, i + n);
  }
  for (int i = 1; i <= n; i++) read(w[i]);
  deep[1] = 1;
  build1(1);
  build2(1);
  while (m--) {
    read(S), read(T);
    int lca = LCA(S, T);
    Ad(deep[S] + cir, 0, ++cnt);
    Ad1(S, cnt);
    Ad2(lca, cnt);
    Ad(0, deep[lca] * 2 - deep[S] + cir, ++cnt);
    Ad1(T, cnt);
    Ad2(lca, cnt);
    if (deep[lca] + w[lca] == deep[S]) Ans[lca]--;
  }
  Count(1);
  for (int i = 1; i <= n; i++) printf("%d ", Ans[i]);
}
