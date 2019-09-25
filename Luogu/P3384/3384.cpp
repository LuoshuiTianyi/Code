#include <cstdio>
#include <iostream>
using namespace std;
int n, m, opt, Root, mod, u, v;
int head[100001], to[200001], nx[200001], U, V, a[100001];
int son[100001], d[100001], fa[100001], top[100001], deep[100001], size[100001],
    cnt;
int L, R, x, sum[400001], adv[400001], ans;
void addroad(int u, int v, int d) {
  to[d] = v;
  nx[d] = head[u];
  head[u] = d;
}
void Mod(int &x) { x %= mod; }
void SWORK(int &u, int &v) {
  if (deep[top[u]] < deep[top[v]])
    swap(u, v);
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
    if (to[i] != son[x] && to[i] != fa[x])
      build2(to[i]);
}
void pushdown(int o, int l, int r) {
  int mid = (l + r) >> 1;
  Mod(adv[o * 2] += adv[o]);
  Mod(adv[o * 2 + 1] += adv[o]);
  Mod(sum[o * 2] += adv[o] * (mid - l + 1) % mod);
  Mod(sum[o * 2 + 1] += adv[o] * (r - mid) % mod);
  adv[o] = 0;
}
void pushup(int o) { sum[o] = sum[o * 2] + sum[o * 2 + 1]; }
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    Mod(sum[o] += (r - l + 1) * x % mod);
    Mod(adv[o] += x);
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (L <= mid)
    add(o * 2, l, mid);
  if (R > mid)
    add(o * 2 + 1, mid + 1, r);
  pushup(o);
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    Mod(ans += sum[o]);
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (L <= mid)
    query(o * 2, l, mid);
  if (R > mid)
    query(o * 2 + 1, mid + 1, r);
  pushup(o);
}
void And() {
  while (top[U] != top[V]) {
    SWORK(U, V);
    L = d[top[U]], R = d[U];
    add(1, 1, n);
    U = fa[top[U]];
  }
  if (deep[U] > deep[V])
    swap(U, V);
  L = d[U], R = d[V];
  add(1, 1, n);
}
void Query() {
  ans = 0;
  while (top[U] != top[V]) {
    SWORK(U, V);
    L = d[top[U]], R = d[U];
    query(1, 1, n);
    U = fa[top[U]];
  }
  if (deep[U] > deep[V])
    swap(U, V);
  L = d[U], R = d[V];
  query(1, 1, n);
}
int main() {
  freopen("3384.in", "r", stdin);
  freopen("3384.out", "w", stdout);
  cin >> n >> m >> Root >> mod;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    addroad(u, v, i);
    addroad(v, u, i + n);
  }
  deep[Root] = 1;
  build1(Root);
  build2(Root);
  for (int i = 1; i <= n; i++) {
    L = d[i], R = d[i], x = a[i];
    add(1, 1, n);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", &opt);
    if (opt == 1) {
      scanf("%d%d%d", &U, &V, &x);
      And();
    }
    if (opt == 2) {
      scanf("%d%d", &U, &V);
      Query();
      printf("%d\n", ans);
    }
    if (opt == 3) {
      scanf("%d%d", &U, &x);
      L = d[U], R = d[U] + size[U] - 1;
      add(1, 1, n);
    }
    if (opt == 4) {
      scanf("%d", &U);
      L = d[U], R = d[U] + size[U] - 1;
      ans = 0;
      query(1, 1, n);
      printf("%d\n", ans);
    }
  }
}
