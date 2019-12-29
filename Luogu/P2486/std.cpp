#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[100001];
int head[100001], nx[200001], to[200001];
int fa[100001], deep[100001], top[100001], size[100001], son[100001], d[100001],
    cnt;
int sum[400001], L, R, x, adv[400001], ll[400001], rr[400001], ans, y, res;
char opt;
void addroad(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void build1(int x) {
  top[x] = x;
  size[x] = 1;
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
  d[x] = ++cnt;
  if (son[x]) {
    top[son[x]] = top[x];
    build2(son[x]);
  }
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x] && to[i] != son[x]) build2(to[i]);
}
void pushdown(int o, int l, int r) {
  if (adv[o]) {
    sum[o * 2] = sum[o * 2 + 1] = 1;
    adv[o * 2] = adv[o * 2 + 1] = ll[o * 2] = ll[o * 2 + 1] = rr[o * 2] =
        rr[o * 2 + 1] = adv[o];
    adv[o] = 0;
  }
}
void pushup(int o) {
  ll[o] = ll[o * 2], rr[o] = rr[o * 2 + 1],
  sum[o] = sum[o * 2] + sum[o * 2 + 1];
  if (rr[o * 2] == ll[o * 2 + 1]) sum[o]--;
}
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    sum[o] = 1;
    ll[o] = rr[o] = adv[o] = x;
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid < R) add(o * 2 + 1, mid + 1, r);
  if (mid >= L) add(o * 2, l, mid);
  pushup(o);
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    ans += sum[o];
    if (rr[o] == x) ans--;
    x = ll[o];
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid < R) query(o * 2 + 1, mid + 1, r);
  if (mid >= L) query(o * 2, l, mid);
  pushup(o);
}
void work(int u, int v) {
  while (top[u] != top[v]) {
    if (deep[top[u]] < deep[top[v]]) swap(u, v);
    L = d[top[u]], R = d[u];
    add(1, 1, n);
    u = fa[top[u]];
  }
  if (deep[u] > deep[v]) swap(u, v);
  L = d[u], R = d[v];
  add(1, 1, n);
}
void range(int o, int l, int r) {
  if (l == r) {
    res = ll[o];
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid >= L)
    range(o * 2, l, mid);
  else
    range(o * 2 + 1, mid + 1, r);
  pushup(o);
}
void Query(int u, int v) {
  while (top[u] != top[v]) {
    if (deep[top[u]] < deep[top[v]]) {
      swap(u, v);
      swap(x, y);
    }
    L = d[top[u]], R = d[u];
    query(1, 1, n);
    u = fa[top[u]];
  }
  if (deep[u] > deep[v])
    swap(u, v);
  else
    swap(x, y);
  L = d[u], R = d[v];
  query(1, 1, n);
  range(1, 1, n);
  if (res == y) ans--;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("2486.in", "r", stdin);
  freopen("2486.ans", "w", stdout);
#endif
  cin >> n >> m;
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    addroad(u, v, i);
    addroad(v, u, i + n);
  }
  build1(1);
  build2(1);
  for (int i = 1; i <= n; i++) {
    L = d[i], R = d[i], x = a[i];
    add(1, 1, n);
  }
  while (m--) {
    cin >> opt;
    scanf("%d%d", &u, &v);
    if (opt == 'C') {
      scanf("%d", &x);
      work(u, v);
    } else {
      ans = 0, x = 0, y = 0;
      Query(u, v);
      printf("%d\n", ans);
    }
  }
}
