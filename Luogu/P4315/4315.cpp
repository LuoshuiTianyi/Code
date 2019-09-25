#include <cstdio>
#include <iostream>
using namespace std;
#define ls (o << 1)
#define rs ((o << 1) + 1)
int n;
int head[100001], nx[200001], to[200001], u[100001], v[100001], w[100001],
    deep[100001], fa[100001];
int top[100001], d[100001], son[100001], size[100001], cnt;
int adv[400001], maxx[400001], tag[400001], L, R, x, ans, k;
char opt[10];
void addroad(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void Swap(int &u, int &v) {
  if (deep[u] < deep[v])
    swap(u, v);
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
void pushdown(int o, int l, int r) {
  if (tag[o] != 1) {
    tag[ls] *= tag[o];
    tag[rs] *= tag[o];
    adv[ls] *= tag[o];
    adv[rs] *= tag[o];
    maxx[ls] *= tag[o];
    maxx[rs] *= tag[o];
    tag[o] = 1;
  }
  if (adv[o] != 0) {
    maxx[ls] += adv[o];
    maxx[rs] += adv[o];
    adv[ls] += adv[o];
    adv[rs] += adv[o];
    adv[o] = 0;
  }
}
void pushup(int o) { maxx[o] = max(maxx[ls], maxx[rs]); }
void add(int o, int l, int r, int opt) {
  if (l >= L && r <= R) {
    if (opt == 1) {
      tag[o] = 0;
      adv[o] *= tag[o];
      maxx[o] *= tag[o];
    } else {
      maxx[o] += x;
      adv[o] += x;
    }
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid >= L)
    add(ls, l, mid, opt);
  if (mid < R)
    add(rs, mid + 1, r, opt);
  pushup(o);
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    ans = max(ans, maxx[o]);
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid >= L)
    query(ls, l, mid);
  if (mid < R)
    query(rs, mid + 1, r);
  pushup(o);
}
void Change(int u, int v, int opt) {
  while (top[u] != top[v]) {
    if (deep[top[u]] < deep[top[v]])
      swap(u, v);
    L = d[top[u]], R = d[u];
    add(1, 1, n, opt);
    if (opt == 1)
      add(1, 1, n, 2);
    u = fa[top[u]];
  }
  if (deep[u] > deep[v])
    swap(u, v);
  if (u != v) {
    L = d[son[u]], R = d[v];
    add(1, 1, n, opt);
    if (opt == 1)
      add(1, 1, n, 2);
  }
}
void Query(int u, int v) {
  ans = 0;
  while (top[u] != top[v]) {
    if (deep[top[u]] < deep[top[v]])
      swap(u, v);
    L = d[top[u]], R = d[u];
    query(1, 1, n);
    u = fa[top[u]];
  }
  if (deep[u] > deep[v])
    swap(u, v);
  if (u != v) {
    L = d[son[u]], R = d[v];
    query(1, 1, n);
  }
}
int main() {
  freopen("4315.in", "r", stdin);
  freopen("4315.out", "w", stdout);
  cin >> n;
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &u[i], &v[i], &w[i]);
    addroad(u[i], v[i], i);
    addroad(v[i], u[i], i + n);
  }
  deep[1] = 1;
  build1(1);
  build2(1);
  for (int i = 1; i <= 4 * n; i++)
    tag[i] = 1;
  for (int i = 1; i < n; i++) {
    Swap(u[i], v[i]);
    L = d[u[i]], R = d[u[i]], x = w[i];
    add(1, 1, n, 2);
  }
  int U, V;
  while (1) {
    cin >> opt;
    if (opt[0] == 'S')
      break;
    if (opt[0] == 'C') {
      if (opt[1] == 'h') {
        scanf("%d%d", &k, &x);
        L = d[u[k]], R = d[u[k]];
        add(1, 1, n, 1);
        add(1, 1, n, 2);
      } else {
        scanf("%d%d%d", &U, &V, &x);
        Change(U, V, 1);
      }
    }
    if (opt[0] == 'A') {
      scanf("%d%d%d", &U, &V, &x);
      Change(U, V, 2);
    }
    if (opt[0] == 'M') {
      scanf("%d%d", &U, &V);
      Query(U, V);
      printf("%d\n", ans);
    }
  }
}
