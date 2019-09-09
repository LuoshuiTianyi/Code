#include <cstdio>
#include <iostream>
using namespace std;
#define ls (o << 1)
#define rs ((o << 1) + 1)
int n, Q, w[30001], head[30001], nx[60001], to[60001];
int sum[120001], maxx[120001], L, R, ans, x;
int d[30001], top[30001], fa[30001], deep[30001], size[30001], son[30001], cnt;
char opt[10];
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
      if (size[to[i]] > size[son[x]])
        son[x] = to[i];
      size[x] += size[to[i]];
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
void pushup(int o) {
  sum[o] = sum[ls] + sum[rs];
  maxx[o] = max(maxx[ls], maxx[rs]);
}
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    sum[o] = x;
    maxx[o] = x;
    return;
  }
  int mid = (l + r) >> 1;
  if (mid >= L)
    add(ls, l, mid);
  if (mid < R)
    add(rs, mid + 1, r);
  pushup(o);
}
void query(int o, int l, int r, int opt) {
  if (l >= L && r <= R) {
    if (opt == 1)
      ans = max(ans, maxx[o]);
    else
      ans += sum[o];
    return;
  }
  int mid = (l + r) >> 1;
  if (mid >= L)
    query(ls, l, mid, opt);
  if (mid < R)
    query(rs, mid + 1, r, opt);
}
void Query(int u, int v, int opt) {
  while (top[u] != top[v]) {
    if (deep[top[u]] < deep[top[v]])
      swap(u, v);
    L = d[top[u]], R = d[u];
    query(1, 1, n, opt);
    u = fa[top[u]];
  }
  if (deep[u] > deep[v])
    swap(u, v);
  L = d[u], R = d[v];
  query(1, 1, n, opt);
}
int main() {
  freopen("2590.in", "r", stdin);
  freopen("2590.out", "w", stdout);
  cin >> n;
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    addroad(u, v, i);
    addroad(v, u, i + n);
  }
  for (int i = 1; i <= n; i++)
    scanf("%d", &w[i]);
  deep[1] = 1;
  build1(1);
  build2(1);
  for (int i = 1; i <= n; i++) {
    L = d[i], R = d[i], x = w[i];
    add(1, 1, n);
  }
  cin >> Q;
  while (Q--) {
    cin >> opt;
    scanf("%d%d", &u, &v);
    if (opt[0] == 'C') {
      L = d[u], R = d[u], x = v;
      add(1, 1, n);
    } else {
      ans = 0;
      if (opt[1] == 'M') {
        ans = -2e9;
        Query(u, v, 1);
      } else
        Query(u, v, 2);
      printf("%d\n", ans);
    }
  }
}
