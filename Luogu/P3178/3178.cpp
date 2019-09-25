#include <cstdio>
#include <iostream>
using namespace std;
int n, m, head[100001], to[200001], nx[200001];
int a[100001], d[100001], opt, p;
int L, R, top[100001], fa[100001], deep[100001], size[100001], son[100001], cnt;
long long x, sum[400001], adv[400001], ans;
void addroad(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void pushdown(int o, int l, int r) {
  int mid = (l + r) >> 1;
  sum[o * 2] += adv[o] * (mid - l + 1);
  sum[o * 2 + 1] += adv[o] * (r - mid);
  adv[o * 2] += adv[o];
  adv[o * 2 + 1] += adv[o];
  adv[o] = 0;
}
void pushup(int o) { sum[o] = sum[o * 2] + sum[o * 2 + 1]; }
void build1(int x) {
  top[x] = x;
  size[x] = 1;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x]) {
      deep[to[i]] = deep[x] + 1;
      fa[to[i]] = x;
      build1(to[i]);
      size[x] += size[to[i]];
      if (size[to[i]] > size[son[x]])
        son[x] = to[i];
    }
}
void build2(int x) {
  d[x] = ++cnt;
  if (son[x]) {
    top[son[x]] = top[x];
    build2(son[x]);
  }
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x] && to[i] != son[x])
      build2(to[i]);
}
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    adv[o] += x;
    sum[o] += (r - l + 1) * x;
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid >= L)
    add(o * 2, l, mid);
  if (mid < R)
    add(o * 2 + 1, mid + 1, r);
  pushup(o);
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    ans += sum[o];
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid >= L)
    query(o * 2, l, mid);
  if (mid < R)
    query(o * 2 + 1, mid + 1, r);
  pushup(o);
}
void Query(int p) {
  ans = 0;
  while (p != 0) {
    L = d[top[p]], R = d[p];
    query(1, 1, n);
    p = fa[top[p]];
  }
}
int main() {
  freopen("3178.in", "r", stdin);
  freopen("3178.out", "w", stdout);
  cin >> n >> m;
  int u, v;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    addroad(u, v, i);
    addroad(v, u, i + n);
  }
  deep[1] = 1;
  build1(1);
  build2(1);
  for (int i = 1; i <= n; i++) {
    L = d[i], R = d[i], x = a[i];
    add(1, 1, n);
  }
  while (m--) {
    scanf("%d%d", &opt, &p);
    if (opt == 1) {
      scanf("%lld", &x);
      L = d[p], R = d[p];
      add(1, 1, n);
    }
    if (opt == 2) {
      scanf("%lld", &x);
      L = d[p], R = d[p] + size[p] - 1;
      add(1, 1, n);
    }
    if (opt == 3) {
      Query(p);
      printf("%lld\n", ans);
    }
  }
}
